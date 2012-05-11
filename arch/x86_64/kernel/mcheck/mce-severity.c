/*
 * MCE grading rules.
 * Copyright 2008, 2009 Intel Corporation.
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; version 2
 * of the License.
 *
 * Author: Andi Kleen
 */
#include <arch/mce.h>
#include <arch/apic.h>

#include "mce-internal.h"

int panic_on_oops;

/*
 * Grade an mce by severity. In general the most severe ones are processed
 * first. Since there are quite a lot of combinations test the bits in a
 * table-driven way. The rules are simply processed in order, first
 * match wins.
 *
 * Note this is only used for machine check exceptions, the corrected
 * errors use much simpler rules. The exceptions still check for the corrected
 * errors, but only to leave them alone for the CMCI handler (except for
 * panic situations)
 */

enum context { IN_KERNEL = 1, IN_USER = 2 };
enum ser { SER_REQUIRED = 1, NO_SER = 2 };

static struct severity {
	u64 mask;
	u64 result;
	unsigned char sev;
	unsigned char mcgmask;
	unsigned char mcgres;
	unsigned char ser;
	unsigned char context;
	unsigned char covered;
	char *msg;
} severities[] = {
#define MCESEV(s, m, c...) { .sev = MCE_ ## s ## _SEVERITY, .msg = m, ## c }
#define  KERNEL		.context = IN_KERNEL
#define  USER		.context = IN_USER
#define  SER		.ser = SER_REQUIRED
#define  NOSER		.ser = NO_SER
#define  BITCLR(x)	.mask = x, .result = 0
#define  BITSET(x)	.mask = x, .result = x
#define  MCGMASK(x, y)	.mcgmask = x, .mcgres = y
#define  MASK(x, y)	.mask = x, .result = y
#define MCI_UC_S (MCI_STATUS_UC|MCI_STATUS_S)
#define MCI_UC_SAR (MCI_STATUS_UC|MCI_STATUS_S|MCI_STATUS_AR)
#define MCACOD 0xffff

	MCESEV(
		NO, "Invalid",
		BITCLR(MCI_STATUS_VAL)
		),
	MCESEV(
		NO, "Not enabled",
		BITCLR(MCI_STATUS_EN)
		),
	MCESEV(
		PANIC, "Processor context corrupt",
		BITSET(MCI_STATUS_PCC)
		),
	/* When MCIP is not set something is very confused */
	MCESEV(
		PANIC, "MCIP not set in MCA handler",
		MCGMASK(MCG_STATUS_MCIP, 0)
		),
	/* Neither return not error IP -- no chance to recover -> PANIC */
	MCESEV(
		PANIC, "Neither restart nor error IP",
		MCGMASK(MCG_STATUS_RIPV|MCG_STATUS_EIPV, 0)
		),
	MCESEV(
		PANIC, "In kernel and no restart IP",
		KERNEL, MCGMASK(MCG_STATUS_RIPV, 0)
		),
	MCESEV(
		KEEP, "Corrected error",
		NOSER, BITCLR(MCI_STATUS_UC)
		),

	/* ignore OVER for UCNA */
	MCESEV(
		KEEP, "Uncorrected no action required",
		SER, MASK(MCI_UC_SAR, MCI_STATUS_UC)
		),
	MCESEV(
		PANIC, "Illegal combination (UCNA with AR=1)",
		SER,
		MASK(MCI_STATUS_OVER|MCI_UC_SAR, MCI_STATUS_UC|MCI_STATUS_AR)
		),
	MCESEV(
		KEEP, "Non signalled machine check",
		SER, BITCLR(MCI_STATUS_S)
		),

	/* AR add known MCACODs here */
	MCESEV(
		PANIC, "Action required with lost events",
		SER, BITSET(MCI_STATUS_OVER|MCI_UC_SAR)
		),
	MCESEV(
		PANIC, "Action required: unknown MCACOD",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR, MCI_UC_SAR)
		),

	/* known AO MCACODs: */
	MCESEV(
		AO, "Action optional: memory scrubbing error",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR|0xfff0, MCI_UC_S|0x00c0)
		),
	MCESEV(
		AO, "Action optional: last level cache writeback error",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR|MCACOD, MCI_UC_S|0x017a)
		),
	MCESEV(
		SOME, "Action optional: unknown MCACOD",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR, MCI_UC_S)
		),
	MCESEV(
		SOME, "Action optional with lost events",
		SER, MASK(MCI_STATUS_OVER|MCI_UC_SAR, MCI_STATUS_OVER|MCI_UC_S)
		),

	MCESEV(
		PANIC, "Overflowed uncorrected",
		BITSET(MCI_STATUS_OVER|MCI_STATUS_UC)
		),
	MCESEV(
		UC, "Uncorrected",
		BITSET(MCI_STATUS_UC)
		),
	MCESEV(
		SOME, "No match",
		BITSET(0)
		)	/* always matches. keep at end */
};

/*
 * If the EIPV bit is set, it means the saved IP is the
 * instruction which caused the MCE.
 */
static int error_context(struct mce *m)
{
	if (m->mcgstatus & MCG_STATUS_EIPV)
		return (m->ip && (m->cs & 3) == 3) ? IN_USER : IN_KERNEL;
	/* Unknown, assume kernel */
	return IN_KERNEL;
}

int mce_severity(struct mce *m, int tolerant, char **msg)
{
	enum context ctx = error_context(m);
	struct severity *s;

	for (s = severities;; s++) {
		if ((m->status & s->mask) != s->result)
			continue;
		if ((m->mcgstatus & s->mcgmask) != s->mcgres)
			continue;
		if (s->ser == SER_REQUIRED && !mce_ser)
			continue;
		if (s->ser == NO_SER && mce_ser)
			continue;
		if (s->context && ctx != s->context)
			continue;
		if (msg)
			*msg = s->msg;
		s->covered = 1;
		if (s->sev >= MCE_UC_SEVERITY && ctx == IN_KERNEL) {
			if (panic_on_oops || tolerant < 1)
				return MCE_PANIC_SEVERITY;
		}
		return s->sev;
	}
}

#ifdef CONFIG_DEBUG_FS
static void *s_start(struct seq_file *f, loff_t *pos)
{
	if (*pos >= ARRAY_SIZE(severities))
		return NULL;
	return &severities[*pos];
}

static void *s_next(struct seq_file *f, void *data, loff_t *pos)
{
	if (++(*pos) >= ARRAY_SIZE(severities))
		return NULL;
	return &severities[*pos];
}

static void s_stop(struct seq_file *f, void *data)
{
}

static int s_show(struct seq_file *f, void *data)
{
	struct severity *ser = data;
	seq_printf(f, "%d\t%s\n", ser->covered, ser->msg);
	return 0;
}

static const struct seq_operations severities_seq_ops = {
	.start	= s_start,
	.next	= s_next,
	.stop	= s_stop,
	.show	= s_show,
};

static int severities_coverage_open(struct inode *inode, struct file *file)
{
	return seq_open(file, &severities_seq_ops);
}

static ssize_t severities_coverage_write(struct file *file,
					 const char __user *ubuf,
					 size_t count, loff_t *ppos)
{
	int i;
	for (i = 0; i < ARRAY_SIZE(severities); i++)
		severities[i].covered = 0;
	return count;
}

static const struct file_operations severities_coverage_fops = {
	.open		= severities_coverage_open,
	.release	= seq_release,
	.read		= seq_read,
	.write		= severities_coverage_write,
	.llseek		= seq_lseek,
};

static int __init severities_debugfs_init(void)
{
	struct dentry *dmce, *fsev;

	dmce = mce_get_debugfs_dir();
	if (!dmce)
		goto err_out;

	fsev = debugfs_create_file("severities-coverage", 0444, dmce, NULL,
				   &severities_coverage_fops);
	if (!fsev)
		goto err_out;

	return 0;

err_out:
	return -ENOMEM;
}
late_initcall(severities_debugfs_init);
#endif /* CONFIG_DEBUG_FS */
