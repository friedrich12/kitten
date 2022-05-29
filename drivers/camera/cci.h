/* 
 * CCI Driver to communicate with s5k4ec cameras
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */
#ifndef CCI_H
#define CCI_H

#define FIFO_DEPTH 64
#define CCI_HCLK 24 * 1000 * 1000
#define CCI_INLINE_FUNC inline
#define REG_DLY 0xffff

/* Contains offsets and bitfield for cci driver */
#include "camera.h"
#include "cam_def.h"

enum cci_io_vol {
	LOW,
	HIGH,
};

enum cci_trans_mode {
	SINGLE,
	REPEAT,
};

enum cci_rs_mode {
	RESTART	   = 0,
	STOP_START = 1,
};

enum cci_rd_start {
	START_WITH_ID_W	   = 0,
	START_WITHOUT_ID_W = 1,
};

enum cci_src {
	FIFO = 0,
	DRAM = 1,
};

enum cci_packet_mode {
	COMPACT	 = 0,
	COMPLETE = 1,
};

enum cci_trig_src {
	NO_TRIG	  = 0,
	CSI0_TRIG = 2,
	CSI1_TRIG = 3,
};

enum cci_trig_con {
	TRIG_DEFAULT	= 0,
	TRIG_HREF_FIRST = 0,
	TRIG_HREF_LAST	= 1,
	TRIG_LN_CNT		= 2,
};

struct cci_bus_fmt {
	enum cci_rs_mode  rs_mode;
	enum cci_rd_start rs_start;
	unsigned char	  saddr_7bit;
	unsigned char	  wr_flag;
	unsigned char	  addr_len;
	unsigned char	  data_len;
};

struct cci_tx_buf {
	enum cci_src		 buf_src;
	enum cci_packet_mode pkt_mode;
	unsigned int		 pkt_cnt;
};

struct cci_tx_trig {
	enum cci_trig_src trig_src;
	enum cci_trig_con trig_con;
};

struct cci_int_status {
	_Bool complete;
	_Bool error;
};

enum cci_int_sel {
	CCI_INT_FINISH = 0X1,
	CCI_INT_ERROR  = 0X2,
	CCI_INT_ALL	   = 0x3,
};

struct cci_line_status {
	enum cci_io_vol cci_sck;
	enum cci_io_vol cci_sda;
};

enum cci_bus_status {
	BUS_ERR			  = 0x00,
	START_TX		  = 0x08,
	RPT_START_TX	  = 0x10,
	ADDR_WR_TX_WI_ACK = 0x18,
	ADDR_WR_TX_WO_ACK = 0x20,
	DATA_TX_WI_ACK	  = 0x28,
	DATA_TX_WO_ACK	  = 0x30,
	ARBIT_LOST		  = 0x38,
	ADDR_RD_TX_WI_ACK = 0x40,
	ADDR_RD_TX_WO_ACK = 0x48,
	DATA_RX_WI_ACK	  = 0x50,
	DATA_RX_WO_ACK	  = 0x58,
	ACK_TIMEOUT		  = 0x01,
	NONE_DEFINED,
};

struct cci_tx_mode {
	struct cci_tx_buf  tx_buf_mode;
	struct cci_tx_trig tx_trig_mode;
	unsigned int	   tx_trig_line_cnt;
};

struct cci_msg {
	struct cci_bus_fmt bus_fmt;
	unsigned char *	   pkt_buf;
	unsigned char	   pkt_num;
};

#endif
