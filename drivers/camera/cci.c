/*
 * CCI Driver to communicate with s5k4ec cameras
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */
#include "cci.h"

unsigned int fifo_last_pt;

extern struct csi csi;

void
csi_cci_enable()
{
	/* Keep other set values just turn on CCI */
	struct cci_ctrl_reg reg = {0};
	reg.val					= __csi_read32(CCI_CTRL);
	reg.cci_en				= 1;
	__csi_write32(CCI_CTRL, reg.val);
}

void
csi_cci_disable()
{
	/* Keep other set values just turn off CCI */
	struct cci_ctrl_reg reg = {0};
	reg.val					= __csi_read32(CCI_CTRL);
	reg.cci_en				= 0;
	__csi_write32(CCI_CTRL, reg.val);
}

void
csi_cci_reset()
{
	/* CCI soft reset */
	struct cci_ctrl_reg reg = {0};
	reg.val					= __csi_read32(CCI_CTRL);
	reg.soft_reset			= 1;
	__csi_write32(CCI_CTRL, reg.val);

	reg.soft_reset = 0;
	__csi_write32(CCI_CTRL, reg.val);
}

/* TODO: add div_coef clock type structure */
void
csi_cci_set_clk_div(unsigned char * div_coef)
{
	/* set clocks */
	struct cci_bus_ctrl_reg reg = {0};
	reg.val						= __csi_read32(CCI_BUS_CTRL);
	reg.clk_m					= div_coef[0];
	reg.clk_n					= div_coef[1];
	__csi_write32(CCI_BUS_CTRL, reg.val);
}

/* interval unit in 40 scl cycles */
void
csi_cci_set_pkt_interval(unsigned char interval)
{
	struct cci_cfg_reg reg = {0};
	reg.val				   = __csi_read32(CCI_CFG);
	reg.interval		   = interval;
	__csi_write32(CCI_CFG, reg.val);
}

/* timeout unit in scl cycle */
void
csi_cci_set_ack_timeout(unsigned char to_val)
{
	struct cci_cfg_reg reg = {0};
	reg.val				   = __csi_read32(CCI_CFG);
	reg.timeout_n		   = to_val;
	__csi_write32(CCI_CFG, reg.val);
}

/* trig delay unit in scl cycle */
void
csi_cci_set_trig_dly(unsigned int dly)
{
	if (dly == 0) {
		struct cci_bus_ctrl_reg reg = {0};
		reg.val						= __csi_read32(CCI_BUS_CTRL);
		reg.dly_trig				= 0;
		__csi_write32(CCI_BUS_CTRL, reg.val);
	} else {
		struct cci_bus_ctrl_reg reg = {0};
		reg.val						= __csi_read32(CCI_BUS_CTRL);
		reg.dly_trig				= 1;
		reg.dly_cyc					= dly;
		__csi_write32(CCI_BUS_CTRL, reg.val);
	}
}

void
csi_cci_trans_start(enum cci_trans_mode trans_mode)
{
	fifo_last_pt = 0;
	switch (trans_mode) {
		case SINGLE: {
			struct cci_ctrl_reg reg = {0};
			reg.val					= __csi_read32(CCI_CTRL);
			reg.repeat_tran			= 0;
			reg.single_tran			= 1;
			__csi_write32(CCI_CTRL, reg.val);
			break;
		}
		case REPEAT: {
			struct cci_ctrl_reg reg = {0};
			reg.val					= __csi_read32(CCI_CTRL);
			reg.repeat_tran			= 1;
			reg.single_tran			= 0;
			__csi_write32(CCI_CTRL, reg.val);
			break;
		}
		default: {
			struct cci_ctrl_reg reg = {0};
			reg.val					= __csi_read32(CCI_CTRL);
			reg.repeat_tran			= 0;
			reg.single_tran			= 0;
			__csi_write32(CCI_CTRL, reg.val);
			break;
		}
	}
}

unsigned int
csi_cci_get_trans_done()
{
	struct cci_ctrl_reg reg = {0};
	reg.val					= __csi_read32(CCI_CTRL);
	return !(reg.single_tran == 0);
}

void
csi_cci_set_bus_fmt(struct cci_bus_fmt * bus_fmt)
{
	{
		struct cci_ctrl_reg reg = {0};
		reg.val					= __csi_read32(CCI_CTRL);

		if (0 == bus_fmt->rs_mode) {
			reg.restart_mode = 0;
		} else {
			reg.restart_mode = 1;
		}

		__csi_write32(CCI_CTRL, reg.val);
	}

	{
		struct cci_ctrl_reg reg = {0};
		reg.val					= __csi_read32(CCI_CTRL);

		if (0 == bus_fmt->rs_start) {
			reg.read_tran_mode = 0;
		} else {
			reg.read_tran_mode = 1;
		}

		__csi_write32(CCI_CTRL, reg.val);
	}

	struct cci_fmt_reg reg = {0};
	reg.val				   = __csi_read32(CCI_CTRL);
	reg.slv_id			   = bus_fmt->saddr_7bit;
	reg.cmd				   = bus_fmt->wr_flag;
	reg.addr_byte		   = bus_fmt->addr_len;
	reg.data_byte		   = bus_fmt->data_len;
	__csi_write32(CCI_CTRL, reg.val);
}

void
csi_cci_set_tx_buf_mode(struct cci_tx_buf * tx_buf_mode)
{
	struct cci_cfg_reg reg = {0};
	reg.val				   = __csi_read32(CCI_CFG);
	reg.packet_mode		   = tx_buf_mode->pkt_mode;
	__csi_write32(CCI_CFG, reg.val);

	struct cci_fmt_reg fmt = {0};
	fmt.val				   = __csi_read32(CCI_FMT);
	fmt.packet_cnt		   = tx_buf_mode->pkt_cnt;
	__csi_write32(CCI_FMT, fmt.val);
}

void
csi_cci_fifo_pt_reset()
{
	fifo_last_pt = 0;
}

void
csi_cci_fifo_pt_add(unsigned int byte_cnt)
{
	fifo_last_pt += byte_cnt;
}

void
csi_cci_fifo_pt_sub(unsigned int byte_cnt)
{
	fifo_last_pt -= byte_cnt;
}

static void
cci_wr_tx_buf(unsigned int byte_index, unsigned char value)
{
	unsigned int index_remain, index_dw_align, tmp;
	index_remain   = (byte_index) % 4;
	index_dw_align = (byte_index) / 4;

	struct cci_fifo_acc_reg reg = {0};
	reg.val						= __csi_read32(CCI_FIFO_ACC + 4 * index_dw_align);

	reg.val &= ~(0xff << (index_remain << 3));
	reg.val |= value << (index_remain << 3);

	__csi_write32(CCI_FIFO_ACC + 4 * index_dw_align, reg.val);
}

static void
cci_rd_tx_buf(unsigned int byte_index, unsigned char * value)
{
	unsigned int index_remain, index_dw_align, tmp;
	index_remain   = (byte_index) % 4;
	index_dw_align = (byte_index) / 4;

	struct cci_fifo_acc_reg reg = {0};
	reg.val						= __csi_read32(CCI_FIFO_ACC + 4 * index_dw_align);
	*value						= (reg.val & (0xff << (index_remain << 3))) >> (index_remain << 3);
}

void
csi_cci_wr_tx_buf(unsigned char * buf, unsigned int byte_cnt)
{
	unsigned int i;
	//cci_print_info(sel);
	for (i = 0; i < byte_cnt; i++, fifo_last_pt++) {
		cci_wr_tx_buf(fifo_last_pt, buf[i]);
	}
}

void
csi_cci_rd_tx_buf(unsigned char * buf, unsigned int byte_cnt)
{
	unsigned int i;
	//cci_print_info(sel);
	for (i = 0; i < byte_cnt; i++, fifo_last_pt++) {
		cci_rd_tx_buf(fifo_last_pt, &buf[i]);
	}
}

void
csi_cci_set_trig_mode(struct cci_tx_trig * tx_trig_mode)
{
	struct cci_cfg_reg reg = {0};
	reg.val				   = __csi_read32(CCI_CFG);
	reg.trig_mode		   = tx_trig_mode->trig_src;
	reg.csi_trig		   = tx_trig_mode->trig_con;
	__csi_write32(CCI_CFG, reg.val);
}

void
csi_cci_set_trig_line_cnt(unsigned int line_cnt)
{
	struct cci_lc_reg reg = {0};
	reg.val				  = __csi_read32(CCI_LC_TRIG);
	reg.ln_cnt			  = line_cnt;
	__csi_write32(CCI_LC_TRIG, reg.val);
}

void
cci_int_enable(enum cci_int_sel interrupt)
{
	struct cci_int_ctrl_reg reg = {0};
	reg.val						= __csi_read32(CCI_INT_CTRL);
	reg.val						= ((interrupt << 16) & 0xffff0000);
	__csi_write32(CCI_INT_CTRL, reg.val);
}

void
cci_int_disable(enum cci_int_sel interrupt)
{
	struct cci_int_ctrl_reg reg = {0};
	__csi_write32(CCI_INT_CTRL, reg.val);
}

void
	CCI_INLINE_FUNC
	cci_int_get_status(struct cci_int_status * status)
{
	struct cci_int_ctrl_reg reg = {0};
	reg.val						= __csi_read32(CCI_INT_CTRL);

	status->complete = reg.s_tran_com_pd;
	status->error	 = reg.s_tran_err_pd;
}

void
	CCI_INLINE_FUNC
	cci_int_clear_status(enum cci_int_sel interrupt)
{
	struct cci_int_ctrl_reg reg = {0};
	reg.val						= __csi_read32(CCI_INT_CTRL);
	reg.s_tran_com_pd			= 0;
	reg.s_tran_err_pd			= 0;
	__csi_write32(CCI_INT_CTRL, reg.val);
}

enum cci_bus_status
	CCI_INLINE_FUNC
	cci_get_bus_status()
{
	struct cci_ctrl_reg reg = {0};
	reg.val					= __csi_read32(CCI_CTRL);
	return reg.cci_sta;
}

void
cci_get_line_status(struct cci_line_status * status)
{
	struct cci_bus_ctrl_reg reg = {0};
	reg.val						= __csi_read32(CCI_BUS_CTRL);
	status->cci_sck				= reg.scl_sta;
	status->cci_sda				= reg.sda_sta;
}

void
cci_pad_en()
{
	struct cci_bus_ctrl_reg reg = {0};
	reg.val						= __csi_read32(CCI_BUS_CTRL);
	reg.sda_pen					= 1;
	reg.scl_pen					= 1;
	__csi_write32(CCI_BUS_CTRL, reg.val);
}

void
cci_stop()
{
	struct cci_bus_ctrl_reg reg = {0};
	reg.val						= __csi_read32(CCI_BUS_CTRL);
	reg.scl_moe					= 1;
	reg.sda_moe					= 1;
	reg.scl_mov					= 1;
	__csi_write32(CCI_BUS_CTRL, reg.val);
	udelay(5);

	reg.sda_mov = 0;
	__csi_write32(CCI_BUS_CTRL, reg.val);

	udelay(5);

	reg.scl_moe = 0;
	reg.sda_moe = 0;
	__csi_write32(CCI_BUS_CTRL, reg.val);
}

/* NOTE: We may need to do multiple reads if the CCI writes to the reg 
 * during loop */
void
cci_sck_cycles(unsigned int cycle_times)
{
	struct cci_bus_ctrl_reg reg = {0};
	reg.val						= __csi_read32(CCI_BUS_CTRL);
	reg.scl_moe					= 1;
	reg.sda_moe					= 1;
	__csi_write32(CCI_BUS_CTRL, reg.val);

	while (cycle_times) {
		reg.scl_mov = 1;
		__csi_write32(CCI_BUS_CTRL, reg.val);
		udelay(5);
		reg.scl_mov = 0;
		__csi_write32(CCI_BUS_CTRL, reg.val);
		udelay(5);
		cycle_times--;
	}

	reg.scl_moe = 0;
	reg.sda_moe = 0;
	__csi_write32(CCI_BUS_CTRL, reg.val);
}

/*
void
cci_print_info()
{
	unsigned int reg_val = 0, i;
	printk("Print cci regs: \n");
	for(i=0; i<32; i+=4)
	{
		reg_val = __csi_read32(CSI_BASE_ADDRESS + i);
		printk("0x%x = 0x%x\n",i, reg_val);
	}
}*/
