/*
 * CCI Driver to communicate with s5k4ec cameras
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */
#include "cci.h"

unsigned int fifo_last_pt;

void
csi_cci_enable()
{
        /* Keep other set values just turn on CCI */
        struct cci_ctrl_reg reg = __csi_read32(CCI_CTRL);
        reg.cci_en = 1;
        __csi_write32(CCI_CTRL, reg.val);
}

void
csi_cci_disable()
{
        /* Keep other set values just turn off CCI */
        struct cci_ctrl_reg reg = __csi_read32(CCI_CTRL);
        reg.cci_en = 0;
        __csi_write32(CCI_CTRL, reg.val);
}

void
csi_cci_reset()
{
        /* CCI soft reset */
        struct cci_ctrl_reg reg = __csi_read32(CCI_CTRL);
        reg.soft_reset = 1;
        __csi_write32(CCI_CTRL, reg.val);
	
        reg.soft_reset = 0;
        __csi_write32(CCI_CTRL, reg.val);
}

/* TODO: add div_coef clock type structure */
void
csi_cci_set_clk_div(unsigned char *div_coef)
{
        /* set clocks */
        struct cci_bus_reg reg = __csi_read32(CCI_BUS_CTRL);
        reg.clk_m = div_coef[0];
        reg.clk_n = div_coef[1];
        __csi_write32(CCI_BUS_CTRL, reg.val);
}

/* interval unit in 40 scl cycles */
void
csi_cci_set_pkt_interval(unsigned char interval)
{

        struct cci_cfg_reg reg = __csi_read32(CCI_CFG);
        reg.interval = interval;
        __csi_write32(CCI_CFG, reg.val);
}

/* timeout unit in scl cycle */
void 
csi_cci_set_ack_timeout(unsigned char to_val)
{
        struct cci_cfg_reg reg = __csi_read32(CCI_CFG);
        reg.timeout_n = to_val;
        __csi_write32(CCI_CFG, reg.val);
}

/* trig delay unit in scl cycle */
void
csi_cci_set_trig_dly(unsigned int dly)
{
	if(dly == 0) {
                struct cci_bus_reg reg = __csi_read32(CCI_BUF_CTRL);
                reg.dly_trig = 0;
                __csi_write32(reg.val);
	} else {
                struct cci_bus_reg reg = __csi_read32(CCI_BUF_CTRL);
                reg.dly_trig = 1;
                reg.dly_cyc = dly;
                __csi_write32(reg.val);
	}
}

void 
csi_cci_trans_start(enum cci_trans_mode trans_mode)
{
	fifo_last_pt[sel] = 0;
	switch(trans_mode)
	{
		case SINGLE:
                        struct cci_ctrl_reg reg = __csi_read32(CCI_CTRL);
                        reg.repeat_tran = 0;
                        reg.single_tran = 1;
                        __csi_write32(CCI_CTRL, reg.val);
			break;
		case REPEAT:
                        struct cci_ctrl_reg reg = __csi_read32(CCI_CTRL);
                        reg.repeat_tran = 1;
                        reg.single_tran = 0;
                        __csi_write32(CCI_CTRL, reg.val);
			break;
		default:
                        struct cci_ctrl_reg reg = __csi_read32(CCI_CTRL);
                        reg.repeat_tran = 0;
                        reg.single_tran = 0;
                        __csi_write32(CCI_CTRL, reg.val);
			break;
	}
}

unsigned int
csi_cci_get_trans_done()
{
        struct cci_ctrl_reg reg = __csi_read32(CCI_CTRL);
        return !(reg.single_tran == 0);
}

void
csi_cci_set_bus_fmt(struct cci_bus_fmt *bus_fmt)
{
        {
                struct cci_ctrl_reg reg = __csi_read32(CCI_CTRL);
	
                if(0 == bus_fmt->rs_mode){
                        reg.restart_mode = 0;
                }else{
                        reg.restart_mode = 1;
                }

                __csi_write32(CCI_CTRL, reg.val);
        }

        {
                struct cci_ctrl_reg reg = __csi_read32(CCI_CTRL);
	
                if(0 == bus_fmt->rs_start){
                        reg.read_tran_mode = 0;
                }else{
                        reg.read_tran_mode = 1;
                }

                __csi_write32(CCI_CTRL, reg.val);
        }

        struct cci_fmt_reg reg = __csi_read32(CCI_CTRL);
        reg.slv_id = bus_fmt->saddr_7bit;
        reg.cmd = bus_fmt->wr_flag;
        reg.addr_byte = bus_fmt->addr_len;
        reg.data_byte = bus_fmt->data_len;
        __csi_write32(CCI_CTRL, reg.val);
}

void
csi_cci_set_tx_buf_mode(struct cci_tx_buf *tx_buf_mode)
{
        struct cci_cfg_reg reg = __csi_read32(CCI_CFG);
        reg.packet_mode = tx_buf_mode->pkt_mode;
        __csi_write32(CCI_CFG, reg.val);

        struct cci_fmt_reg fmt = __csi_read32(CCI_FMT);
        fmt.packet_cnt = tx_buf_mode->pkt_cnt;
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
cci_wr_tx_buf(unsigned int sel, unsigned int byte_index, unsigned char value)
{
	unsigned int index_remain,index_dw_align,tmp;
	index_remain = (byte_index)%4;
	index_dw_align = (byte_index)/4;

	tmp = vfe_reg_readl(csi_cci_base_addr[sel] + CCI_FIFO_ACC_OFF + 4*index_dw_align);
	tmp &= ~(0xff << (index_remain<<3));
	tmp |= value << (index_remain<<3);
	vfe_reg_writel(csi_cci_base_addr[sel] + CCI_FIFO_ACC_OFF + 4*index_dw_align, tmp);
}

static void
cci_rd_tx_buf(unsigned int sel, unsigned int byte_index, unsigned char *value)
{
	unsigned int index_remain,index_dw_align,tmp;
	index_remain = (byte_index)%4;
	index_dw_align = (byte_index)/4;
	tmp = vfe_reg_readl(csi_cci_base_addr[sel] + CCI_FIFO_ACC_OFF + 4*index_dw_align);
	*value = (tmp & ( 0xff << (index_remain<<3) )) >> (index_remain<<3);
}

void
csi_cci_wr_tx_buf(unsigned int sel, unsigned char *buf, unsigned int byte_cnt)
{
	unsigned int i;
	//cci_print_info(sel);
	for(i = 0; i < byte_cnt; i++,fifo_last_pt[sel]++)
	{
		cci_wr_tx_buf(sel, fifo_last_pt[sel], buf[i]);
	}
}

void
csi_cci_rd_tx_buf(unsigned int sel, unsigned char *buf, unsigned int byte_cnt)
{
	unsigned int i;
	//cci_print_info(sel);
	for(i = 0; i < byte_cnt; i++,fifo_last_pt[sel]++)
	{
		cci_rd_tx_buf(sel, fifo_last_pt[sel], &buf[i]);
	}
}

void
csi_cci_set_trig_mode(unsigned int sel, struct cci_tx_trig *tx_trig_mode)
{
	vfe_reg_clr_set(csi_cci_base_addr[sel] + CCI_CFG_OFF , CCI_CFG_TRIG_MODE_MASK, 
				tx_trig_mode->trig_src << CCI_CFG_TRIG_MODE);
	vfe_reg_clr_set(csi_cci_base_addr[sel] + CCI_CFG_OFF , CCI_CFG_CSI_TRIG_MASK, 
				tx_trig_mode->trig_con << CCI_CFG_CSI_TRIG);
}

void
csi_cci_set_trig_line_cnt(unsigned int sel, unsigned int line_cnt)
{
	vfe_reg_clr_set(csi_cci_base_addr[sel] + CCI_LC_TRIG_OFF , CCI_LC_TRIG_LN_CNT_MASK, 
			line_cnt << CCI_LC_TRIG_LN_CNT);
}

void
cci_int_enable(unsigned int sel, enum cci_int_sel interrupt)
{
	vfe_reg_set(csi_cci_base_addr[sel] + CCI_INT_CTRL_OFF, ((interrupt<<16)&0xffff0000));
}

void
cci_int_disable(unsigned int sel, enum cci_int_sel interrupt)
{
	vfe_reg_clr(csi_cci_base_addr[sel] + CCI_INT_CTRL_OFF, ((interrupt<<16)&0xffff0000));
}

void
CCI_INLINE_FUNC cci_int_get_status(unsigned int sel, struct cci_int_status *status)
{
	unsigned int reg_val = vfe_reg_readl(csi_cci_base_addr[sel] + CCI_INT_CTRL_OFF);
	status->complete = (reg_val >> CCI_INT_CTRL_S_TRAN_COM_PD) & 0x1;
	status->error	 =  (reg_val >> CCI_INT_CTRL_S_TRAN_ERR_PD) & 0x1;
}

void
CCI_INLINE_FUNC cci_int_clear_status(unsigned int sel, enum cci_int_sel interrupt)
{
	vfe_reg_clr(csi_cci_base_addr[sel] + CCI_INT_CTRL_OFF, 0xffff << 0);
	vfe_reg_set(csi_cci_base_addr[sel] + CCI_INT_CTRL_OFF , interrupt << 0);
}

enum cci_bus_status
CCI_INLINE_FUNC cci_get_bus_status(unsigned int sel)
{
	unsigned int reg_val = vfe_reg_readl(csi_cci_base_addr[sel] + CCI_CTRL_OFF);
	return (reg_val >> CCI_CTRL_CCI_STA)&0xff;
}

void
cci_get_line_status(unsigned int sel, struct cci_line_status *status)
{
	unsigned int reg_val = vfe_reg_readl(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF);
	status->cci_sck = (reg_val >> CCI_BUS_CTRL_SCL_STA)&0x1;
	status->cci_sda = (reg_val >> CCI_BUS_CTRL_SDA_STA)&0x1;
}

void
cci_pad_en(unsigned int sel)
{
	vfe_reg_set(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SDA_PEN);
	vfe_reg_set(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SCL_PEN);
}

void
cci_stop(unsigned int sel)
{
	vfe_reg_set(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SCL_MOE);
	vfe_reg_set(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SDA_MOE);
	vfe_reg_set(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SCL_MOV);
	csi_cci_udelay(5);
	vfe_reg_clr(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SDA_MOV);
	csi_cci_udelay(5);
	vfe_reg_clr(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SCL_MOE);
	vfe_reg_clr(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SDA_MOE);
}

void
cci_sck_cycles(unsigned int sel, unsigned int cycle_times)
{
	vfe_reg_set(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SCL_MOE);
	vfe_reg_set(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SDA_MOE);
	while(cycle_times)
	{
		vfe_reg_set(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SCL_MOV);
		csi_cci_udelay(5);
		vfe_reg_clr(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SCL_MOV);
		csi_cci_udelay(5);
		cycle_times--;
	}
	vfe_reg_clr(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SCL_MOE);
	vfe_reg_clr(csi_cci_base_addr[sel] + CCI_BUS_CTRL_OFF , 1 << CCI_BUS_CTRL_SDA_MOE);
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

