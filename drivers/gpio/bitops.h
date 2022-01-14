// SPDX-License-Identifier: GPL-2.0-or-later
/* bit search implementation
 *
 * Copyright (C) 2004 Red Hat, Inc. All Rights Reserved.
 * Written by David Howells (dhowells@redhat.com)
 *
 * Copyright (C) 2008 IBM Corporation
 * 'find_last_bit' is written by Rusty Russell <rusty@rustcorp.com.au>
 * (Inspired by David Howell's find_next_bit implementation)
 *
 * Rewritten by Yury Norov <yury.norov@gmail.com> to decrease
 * size and improve performance, 2015.
 */

#ifndef BITOPS_H
#define BITOPS_H

#include <arch/ffs.h>
#include <arch/memory.h>
#include <lwk/byteorder/swab.h>
#include <lwk/macros.h>

/*
 * small_const_nbits(n) is true precisely when it is known at compile-time
 * that BITMAP_SIZE(n) is 1, i.e. 1 <= n <= BITS_PER_LONG. This allows
 * various bit/bitmap APIs to provide a fast inline implementation. Bitmaps
 * of size 0 are very rare, and a compile-time-known-size 0 is most likely
 * a sign of error. They will be handled correctly by the bit/bitmap APIs,
 * but using the out-of-line functions, so that the inline implementations
 * can unconditionally dereference the pointer(s).
 */
#define small_const_nbits(nbits) \
	(__builtin_constant_p(nbits) && (nbits) <= BITS_PER_LONG && (nbits) > 0)


#define BITMAP_FIRST_WORD_MASK(start) (~0UL << ((start) & (BITS_PER_LONG - 1)))
//#define BITS_PER_LONG 64
#define NULL 0
#define UL(x) (_UL(x))
#define BIT(nr) (UL(1) << (nr))

/*
 * This is a common helper function for find_next_bit, find_next_zero_bit, and
 * find_next_and_bit. The differences are:
 *  - The "invert" argument, which is XORed with each fetched word before
 *    searching it for one bits.
 *  - The optional "addr2", which is anded with "addr1" if present.
 */
inline unsigned long _find_next_bit(const unsigned long * addr1,
									const unsigned long * addr2,
									unsigned long		  nbits,
									unsigned long		  start,
									unsigned long		  invert,
									unsigned long		  le)
{
	unsigned long tmp, mask;

	/* Don't worry about compiler optimizations right now */
	if (start >= nbits) {
		return nbits;
	}

	tmp = addr1[start / BITS_PER_LONG];
	if (addr2) {
		tmp &= addr2[start / BITS_PER_LONG];
	}
	tmp ^= invert;

	/* Handle 1st word. */
	mask = BITMAP_FIRST_WORD_MASK(start);
	if (le) {
		mask = __swab64(mask);
	}

	tmp &= mask;

	start = round_down(start, BITS_PER_LONG);

	while (!tmp) {
		start += BITS_PER_LONG;
		if (start >= nbits) {
			return nbits;
		}

		tmp = addr1[start / BITS_PER_LONG];
		if (addr2) {
			tmp &= addr2[start / BITS_PER_LONG];
		}
		tmp ^= invert;
	}

	if (le) {
		tmp = __swab64(tmp);
	}

	return min(start + __ffs(tmp), nbits);
}

/*
 * Find the first set bit in a memory region.
 */
inline unsigned long _find_first_bit(const unsigned long * addr, unsigned long size)
{
	unsigned long idx;

	for (idx = 0; idx * BITS_PER_LONG < size; idx++) {
		if (addr[idx])
			return min(idx * BITS_PER_LONG + __ffs(addr[idx]), size);
	}

	return size;
}

/**
 * find_next_bit - find the next set bit in a memory region
 * @addr: The address to base the search on
 * @offset: The bitnumber to start searching at
 * @size: The bitmap size in bits
 *
 * Returns the bit number for the next set bit
 * If no bits are set, returns @size.
 */
static inline unsigned long find_next_bit(const unsigned long * addr, unsigned long size, unsigned long offset)
{
	if (small_const_nbits(size)) {
		unsigned long val;

		if (offset >= size) {
			return size;
		}

		val = *addr & GENMASK(size - 1, offset);
		return val ? __ffs(val) : size;
	}

	return _find_next_bit(addr, NULL, size, offset, 0UL, 0);
}

/**
 * find_first_bit - find the first set bit in a memory region
 * @addr: The address to start the search at
 * @size: The maximum number of bits to search
 *
 * Returns the bit number of the first set bit.
 * If no bits are set, returns @size.
 */
static inline unsigned long find_first_bit(const unsigned long * addr, unsigned long size)
{
	if (small_const_nbits(size)) {
		unsigned long val = *addr & GENMASK(size - 1, 0);

		return val ? __ffs(val) : size;
	}

	return _find_first_bit(addr, size);
}


#define for_each_set_bit(bit, addr, size)        \
	for ((bit) = find_first_bit((addr), (size)); \
		 (bit) < (size);                         \
		 (bit) = find_next_bit((addr), (size), (bit) + 1))

#endif
