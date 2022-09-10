/* 
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */
#ifndef CAMERA_H
#define CAMERA_H

#include <lwk/types.h>
#include <lwk/driver.h>
#include <lwk/pci/pci.h>
#include <lwk/interrupt.h>
#include <arch/fixmap.h>
#include <arch/io.h>
#include <lwk/blkdev.h>
#include <lwk/time.h>
#include <lwk/spinlock.h>
#include "../gpio/gpio.h"



struct csi {
	vaddr_t csi_virt_start;
	paddr_t csi_phys_start;
	paddr_t csi_phys_size;
};

struct ccu {
	vaddr_t ccu_virt_start;
	paddr_t ccu_phys_start;
	paddr_t ccu_phys_size;
};


struct dma_buffer {
	paddr_t fifo_phys_start;
	vaddr_t fifo_virt_start;
	paddr_t fifo_size;
};

#define __csi_read32(offset) *((uint32_t *)(csi.csi_virt_start + offset))
#define __csi_write32(offset, value) *((uint32_t *)(csi.csi_virt_start + offset)) = value

#define __ccu_read32(offset) *((uint32_t *)(ccu.ccu_virt_start + offset))
#define __ccu_write32(offset, value) *((uint32_t *)(ccu.ccu_virt_start + offset)) = value

// Image capture stuff
#define MAX_CSI 2
#define MAX_CH_NUM 3
#define TOTAL_CH_NUM 1 /* Total number of chanels for pine64 lts just use 1 channel */
#define CSI_CH_OFF (0x0100)
#define ADDR_BIT_R_SHIFT 2 /* Could also be zero */
#define HW_DMA_BEGIN  0x40000000
#define CSI_BUF_BEGIN 0x50000000

//define the voltage level of control signal
#define CSI_STBY_ON 0
#define CSI_STBY_OFF 1
#define CSI_RST_ON 0
#define CSI_RST_OFF 1
#define CSI_PWR_ON 1
#define CSI_PWR_OFF 0
#define CSI_AF_PWR_ON 0
#define CSI_AF_PWR_OFF 1

#define CSI_BASE_ADDRESS 0x01CB0000	   // Camera base address
#define CPU_DRAM_PADDR_ORG 0x40000000
#define CSI0_EN_REG 0x0000					   // CSI Enable register
#define CSI0_IF_CFG_REG 0x0004				   // CSI Interface Configuration Register
#define CSI0_CAP_REG 0x0008					   // CSI Capture Register
#define CSI0_SYNC_CNT_REG 0x000C			   // CSI Synchronization Counter Register
#define CSI0_FIFO_THRS_REG 0x0010			   // CSI FIFO Threshold Register
#define CSI0_PTN_LEN_REG 0x0030				   // CSI Pattern Generation Length register
#define CSI0_PTN_ADDR_REG 0x0034			   // CSI Pattern Generation Address register
#define CSI0_VER_REG 0x003C					   // CSI Version Register
#define CSI0_C0_CFG_REG 0x0044				   // CSI Channel_0 configuration register
#define CSI0_C0_SCALE_REG 0x004C			   // CSI Channel_0 scale register
#define CSI0_C0_F0_BUFA_REG 0x0050			   // CSI Channel_0 FIFO 0 output buffer-A address register
#define CSI0_C0_F1_BUFA_REG 0x0058			   // CSI Channel_0 FIFO 1 output buffer-A address register
#define CSI0_C0_F2_BUFA_REG 0x0060			   // CSI Channel_0 FIFO 2 output buffer-A address register
#define CSI0_C0_CAP_STA_REG 0x006C			   // CSI Channel_0 status register
#define CSI0_C0_INT_EN_REG 0x0070			   // CSI Channel_0 interrupt enable register
#define CSI0_C0_INT_STA_REG 0x0074			   // CSI Channel_0 interrupt status register
#define CSI0_C0_HSIZE_REG 0x0080			   // CSI Channel_0 horizontal size register
#define CSI0_C0_VSIZE_REG 0x0084			   // CSI Channel_0 vertical size register
#define CSI0_C0_BUF_LEN_REG 0x0088			   // CSI Channel_0 line buffer length register
#define CSI0_C0_FLIP_SIZE_REG 0x008C		   // CSI Channel_0 flip size register
#define CSI0_C0_FRM_CLK_CNT_REG 0x0090		   // CSI Channel_0 frame clock counter register
#define CSI0_C0_ACC_ITNL_CLK_CNT_REG 0x0094	   // CSI Channel_0 accumulated and internal clock counter register
#define CSI0_C0_FIFO_STAT_REG 0x0098		   // CSI Channel_0 FIFO Statistic Register
#define CSI0_C0_PCLK_STAT_REG 0x009C		   // CSI Channel_0 PCLK Statistic Register

#define CCI_CTRL 0x3000		   // CCI control register
#define CCI_CFG 0x3004		   // CCI transmission config register
#define CCI_FMT 0x3008		   // CCI packet format register
#define CCI_BUS_CTRL 0x300C	   // CCI bus control register
#define CCI_INT_CTRL 0x3014	   // CCI interrupt control register
#define CCI_LC_TRIG 0x3018	   // CCI line counter trigger register
#define CCI_FIFO_ACC 0x3100	   // CCI FIFO access register
#define CCI_RSV_REG 0x3200	   // CCI reserved register

/* CCU Register */
#define CCU_BASE_ADDRESS 0x01C20000
#define CCU_LEN 0x324
#define PLL_PERIPH0_CTRL_REG 0x28
#define PLL_PERIPH1_CTRL_REG 0x2C
#define PLL_VIDEO0_CTRL_REG -0x10
#define BUS_CLK_GATING_REG1 0x64
#define CSI_MISC_CLK_REG 0x130
#define CSI_CLK_REG 0x134
#define BUS_SOFT_RST_REG1 0x2C4



#define CCI_CTRL_OFF                     			0x0000

#define CCI_CTRL_CCI_EN					0
#define CCI_CTRL_SOFT_RESET			1
#define CCI_CTRL_CCI_STA					16
#define CCI_CTRL_TRAN_RESULT			24
#define CCI_CTRL_READ_TRAN_MODE		28
#define CCI_CTRL_RESTART_MODE		29
#define CCI_CTRL_REPEAT_TRAN			30
#define CCI_CTRL_SINGLE_TRAN			31

#define CCI_CFG_OFF                      			0x0004
#define CCI_CFG_CSI_TRIG  				0
#define CCI_CFG_CSI_TRIG_MASK  			(0xf << CCI_CFG_CSI_TRIG)
#define CCI_CFG_TRIG_MODE 				4
#define CCI_CFG_TRIG_MODE_MASK  		(0x7 << CCI_CFG_TRIG_MODE)
#define CCI_CFG_SRC_SEL    				7
#define CCI_CFG_SRC_SEL_MASK  			(0x1 << CCI_CFG_SRC_SEL)
#define CCI_CFG_PACKET_MODE			15
#define CCI_CFG_PACKET_MODE_MASK  	(0x1 << CCI_CFG_PACKET_MODE)
#define CCI_CFG_INTERVAL  		 		16
#define CCI_CFG_INTERVAL_MASK   		(0xff << CCI_CFG_INTERVAL)

#define CCI_FMT_OFF                      			0x0008
#define CCI_CFG_TIMEOUT_N  				24
#define CCI_CFG_TIMEOUT_N_MASK		(0xff << CCI_CFG_TIMEOUT_N)
#define CCI_FMT_PACKET_CNT			0 
#define CCI_FMT_PACKET_CNT_MASK		(0xffff <<  CCI_FMT_PACKET_CNT)
#define CCI_FMT_DATA_BYTE 				16 
#define CCI_FMT_DATA_BYTE_MASK 		( 0xf<< CCI_FMT_DATA_BYTE) 
#define CCI_FMT_ADDR_BYTE				20
#define CCI_FMT_ADDR_BYTE_MASK 		( 0xf<< CCI_FMT_ADDR_BYTE) 
#define CCI_FMT_CMD      					24
#define CCI_FMT_CMD_MASK      			( 0x1<< CCI_FMT_CMD) 
#define CCI_FMT_SLV_ID    					25
#define CCI_FMT_SLV_ID_MASK      			( 0x7f<< CCI_FMT_SLV_ID) 

#define CCI_BUS_CTRL_OFF                 		0x000C
#define CCI_BUS_CTRL_SDA_MOE 			0 
#define CCI_BUS_CTRL_SCL_MOE 			1 
#define CCI_BUS_CTRL_SDA_MOV 			2 
#define CCI_BUS_CTRL_SCL_MOV 			3 
#define CCI_BUS_CTRL_SDA_PEN 			4
#define CCI_BUS_CTRL_SCL_PEN 			5
#define CCI_BUS_CTRL_SDA_STA 			6
#define CCI_BUS_CTRL_SCL_STA 			7
#define CCI_BUS_CTRL_CLK_M   			8
#define CCI_BUS_CTRL_CLK_M_MASK   		(0xF << CCI_BUS_CTRL_CLK_M)
#define CCI_BUS_CTRL_CLK_N   				12
#define CCI_BUS_CTRL_CLK_N_MASK   		(0x7 << CCI_BUS_CTRL_CLK_N)
#define CCI_BUS_CTRL_DLY_TRIG				15
#define CCI_BUS_CTRL_DLY_CYC 				16
#define CCI_BUS_CTRL_DLY_CYC_MASK 		(0xffff << CCI_BUS_CTRL_DLY_CYC)

#define CCI_INT_CTRL_OFF                 			0x0014
#define CCI_INT_CTRL_S_TRAN_COM_PD    	0 
#define CCI_INT_CTRL_S_TRAN_ERR_PD    		1 
#define CCI_INT_CTRL_RES0             			2
#define CCI_INT_CTRL_S_TRAN_COM_INT_EN	16
#define CCI_INT_CTRL_S_TRAN_ERR_INT_EN	17
#define CCI_INT_CTRL_RES1             			18

#define CCI_LC_TRIG_OFF                  			0x0018
#define CCI_LC_TRIG_LN_CNT					0
#define CCI_LC_TRIG_LN_CNT_MASK			 (0x1fff << CCI_LC_TRIG_LN_CNT)
#define CCI_LC_TRIG_RES0  				 	13

#define CCI_FIFO_ACC_OFF                 			0x0100
#define CCI_FIFO_ACC_DATA_FIFO  			0

#define CCI_RSV_REG_OFF                  			0x0200


#define u32 unsigned int
// 
// Detail information of registers
//
#define CSI_EN_REG_OFF                      	0X000
#define CSI_EN_REG_CSI_EN			0      
#define CSI_EN_REG_PTN_GEN_EN        	1 
#define CSI_EN_REG_CLK_CNT               	2 
#define CSI_EN_REG_CLK_CNT_SPL	3 
#define CSI_EN_REG_PTN_START           4 
#define CSI_EN_REG_RES0                     	5 
#define CSI_EN_REG_VER_EN			30 
#define CSI_EN_REG_RES1                     	31 

#define CSI_IF_CFG_REG_OFF                 				0X004
#define CSI_IF_CFG_REG_CSI_IF        				0
#define CSI_IF_CFG_REG_CSI_IF_MASK			(0X1F<<CSI_IF_CFG_REG_CSI_IF)
#define CSI_IF_CFG_REG_RES0               				5 
#define CSI_IF_CFG_REG_MIPI_IF					7 
#define CSI_IF_CFG_REG_MIPI_IF_MASK			(0X1 << CSI_IF_CFG_REG_MIPI_IF)
#define CSI_IF_CFG_REG_IF_DATA_WIDTH 		8
#define CSI_IF_CFG_REG_IF_DATA_WIDTH_MASK	(0X3<<CSI_IF_CFG_REG_IF_DATA_WIDTH)
#define CSI_IF_CFG_REG_IF_BUS_SEQ           		10 
#define CSI_IF_CFG_REG_RES1                 			12 
#define CSI_IF_CFG_REG_CLK_POL              			16
#define CSI_IF_CFG_REG_CLK_POL_MASK			(0X1<<CSI_IF_CFG_REG_CLK_POL)
#define CSI_IF_CFG_REG_HREF_POL             		17
#define CSI_IF_CFG_REG_HREF_POL_MASK		(0X1<<CSI_IF_CFG_REG_HREF_POL)
#define CSI_IF_CFG_REG_VREF_POL             		18
#define CSI_IF_CFG_REG_VREF_POL_MASK		(0X1<<CSI_IF_CFG_REG_VREF_POL)
#define CSI_IF_CFG_REG_FIELD                			19
#define CSI_IF_CFG_REG_FIELD_MASK				(0X1<<CSI_IF_CFG_REG_FIELD)
#define CSI_IF_CFG_REG_FPS_DS               			20 
#define CSI_IF_CFG_REG_SRC_TYPE             		21
#define CSI_IF_CFG_REG_SRC_TYPE_MASK		(0X1<<CSI_IF_CFG_REG_SRC_TYPE)
#define CSI_IF_CFG_REG_DST                  			22                 
#define CSI_IF_CFG_REG_RES2                 			23

#define CSI_CAP_REG_OFF                     			0X008
#define CSI_CAP_REG_CH0_SCAP_ON			0			
#define CSI_CAP_REG_CH0_VCAP_ON             	1           
#define CSI_CAP_REG_RES0                    			2           
#define CSI_CAP_REG_CH1_SCAP_ON             	8           
#define CSI_CAP_REG_CH1_VCAP_ON             	9           
#define CSI_CAP_REG_RES1                    			10          
#define CSI_CAP_REG_CH2_SCAP_ON             	16          
#define CSI_CAP_REG_CH2_VCAP_ON             	17          
#define CSI_CAP_REG_RES2                    			18          
#define CSI_CAP_REG_CH3_SCAP_ON             	24          
#define CSI_CAP_REG_CH3_VCAP_ON             	25          
#define CSI_CAP_REG_RES3                    			26          

#define CSI_SYNC_CNT_REG_OFF                		0X00C
#define CSI_SYNC_CNT_REG_SYNC_CNT           	0
#define CSI_SYNC_CNT_REG_RES0               		24

#define CSI_FIFO_THRS_REG_OFF               		0X010
#define CSI_FIFO_THRS_REG_FIFO_THRS         	0
#define CSI_FIFO_THRS_REG_RES0              		12

#define CSI_PTN_LEN_REG_OFF                 		0X030
#define CSI_PTN_LEN_REG_PTN_LEN			0

#define CSI_PTN_ADDR_REG_OFF                		0X034
#define CSI_PTN_ADDR_REG_PTN_ADDR		0

#define CSI_VER_REG_OFF                     			0X03C
#define CSI_VER_REG_VER						0

#define CSI_CH_CFG_REG_OFF                  		0X044
#define CSI_CH_CFG_REG_RES0                 		0
#define CSI_CH_CFG_REG_INPUT_SEQ            	8
#define CSI_CH_CFG_REG_INPUT_SEQ_MASK	(0X3<<CSI_CH_CFG_REG_INPUT_SEQ)
#define CSI_CH_CFG_REG_FIELD_SEL            	10
#define CSI_CH_CFG_REG_FIELD_SEL_MASK	(0X3<<CSI_CH_CFG_REG_FIELD_SEL)
#define CSI_CH_CFG_REG_HFLIP_EN             	12
#define CSI_CH_CFG_REG_VFLIP_EN             	13
#define CSI_CH_CFG_REG_RES1                 		14
#define CSI_CH_CFG_REG_OUTPUT_FMT           16
#define CSI_CH_CFG_REG_OUTPUT_FMT_MASK	(0XF<<CSI_CH_CFG_REG_OUTPUT_FMT)

#define CSI_CH_CFG_REG_INPUT_FMT            	20
#define CSI_CH_CFG_REG_INPUT_FMT_MASK		(0XF<<CSI_CH_CFG_REG_INPUT_FMT)

#define CSI_CH_CFG_REG_PAD_VAL              	24                  

#define CSI_CH_SCALE_REG_OFF                		0X04C
#define CSI_CH_SCALE_REG_QUART_EN		0
#define CSI_CH_SCALE_REG_RES0               		1

#define CSI_CH_F0_BUFA_REG_OFF              		0X050
#define CSI_CH_F0_BUFA_REG_C0F0_BUFA		0

#define CSI_CH_F1_BUFA_REG_OFF              		0X058
#define CSI_CH_F1_BUFA_REG_C0F1_BUFA		0   
                                                
#define CSI_CH_F2_BUFA_REG_OFF              		0X060
#define CSI_CH_F2_BUFA_REG_C0F2_BUFA		0   
                                                
#define CSI_CH_STA_REG_OFF                  		0X06C
#define CSI_CH_STA_REG_SCAP_STA			0
#define CSI_CH_STA_REG_VCAP_STA             	1
#define CSI_CH_STA_REG_FIELD_STA            	2
#define CSI_CH_STA_REG_RES0                 		3

#define CSI_CH_INT_EN_REG_OFF               			0X070
#define CSI_CH_INT_EN_REG_CD_INT_EN         		0 
#define CSI_CH_INT_EN_REG_FD_INT_EN         		1 
#define CSI_CH_INT_EN_REG_FIFO0_OF_INT_EN   	2 
#define CSI_CH_INT_EN_REG_FIFO1_OF_INT_EN   	3 
#define CSI_CH_INT_EN_REG_FIFO2_OF_INT_EN   	4 
#define CSI_CH_INT_EN_REG_PRTC_ERR_INT_EN  5 
#define CSI_CH_INT_EN_REG_HB_OF_INT_EN      	6 
#define CSI_CH_INT_EN_REG_VS_INT_EN         		7 
#define CSI_CH_INT_EN_REG_RES0              			8 

#define CSI_CH_INT_STA_REG_OFF              			0X074
#define CSI_CH_INT_STA_REG_CD_PD            		0 
#define CSI_CH_INT_STA_REG_FD_PD            		1 
#define CSI_CH_INT_STA_REG_FIFO0_OF_PD      	2 
#define CSI_CH_INT_STA_REG_FIFO1_OF_PD      	3 
#define CSI_CH_INT_STA_REG_FIFO2_OF_PD      	4 
#define CSI_CH_INT_STA_REG_PRTC_ERR_PD      	5 
#define CSI_CH_INT_STA_REG_HB_OF_PD         		6 
#define CSI_CH_INT_STA_REG_VS_PD            		7 
#define CSI_CH_INT_STA_REG_RES0             		8 

#define CSI_CH_HSIZE_REG_OFF                			0X080
#define CSI_CH_HSIZE_REG_HOR_START          		0
#define CSI_CH_HSIZE_REG_HOR_START_MASK	(0X1FFF<<CSI_CH_HSIZE_REG_HOR_START)
#define CSI_CH_HSIZE_REG_RES0               			13
#define CSI_CH_HSIZE_REG_HOR_LEN            		16
#define CSI_CH_HSIZE_REG_HOR_LEN_MASK		(0X1FFF<<CSI_CH_HSIZE_REG_HOR_LEN)
#define CSI_CH_HSIZE_REG_RES1               			29

#define CSI_CH_VSIZE_REG_OFF                			0X084
#define CSI_CH_VSIZE_REG_VER_START          		0
#define CSI_CH_VSIZE_REG_VER_START_MASK		(0X1FFF<<CSI_CH_VSIZE_REG_VER_START)
#define CSI_CH_VSIZE_REG_RES0               			13 
#define CSI_CH_VSIZE_REG_VER_LEN            		16
#define CSI_CH_VSIZE_REG_VER_LEN_MASK		(0X1FFF<<CSI_CH_VSIZE_REG_VER_LEN)

#define CSI_CH_VSIZE_REG_RES1               			29

#define CSI_CH_BUF_LEN_REG_OFF              			0X088
#define CSI_CH_BUF_LEN_REG_BUF_LEN          			0
#define CSI_CH_BUF_LEN_REG_BUF_LEN_MASK		(0X1FFF<<CSI_CH_BUF_LEN_REG_BUF_LEN)
#define CSI_CH_BUF_LEN_REG_RES0             			13 
#define CSI_CH_BUF_LEN_REG_BUF_LEN_C        		16
#define CSI_CH_BUF_LEN_REG_BUF_LEN_C_MASK		(0X1FFF<<CSI_CH_BUF_LEN_REG_BUF_LEN_C)


#define CSI_CH_BUF_LEN_REG_RES1             		29 

#define CSI_CH_FLIP_SIZE_REG_OFF            		0X08C
#define CSI_CH_FLIP_SIZE_REG_VALID_LEN		0 
#define CSI_CH_FLIP_SIZE_REG_RES0           		13
#define CSI_CH_FLIP_SIZE_REG_VER_LEN        		16
#define CSI_CH_FLIP_SIZE_REG_RES1           		29

#define CSI_CH_FRM_CLK_CNT_REG_OFF          		0X090
#define CSI_CH_FRM_CLK_CNT_REG_FRM_CLK_CNT	0
#define CSI_CH_FRM_CLK_CNT_REG_RES0				24

#define CSI_CH_ACC_ITNL_CLK_CNT_REG_OFF     				0X094
#define CSI_CH_ACC_ITNL_CLK_CNT_REG_ITNL_CLK_CNT 	0
#define CSI_CH_ACC_ITNL_CLK_CNT_REG_ACC_CLK_CNT   	24

#define CSI_CH_OFF                          (0x0100)


#define MAX_CSI 2
/*
 * if format
 */
enum csi_if
{
  CSI_IF_INTLV                =0x00,     /* 1SEG DATA in one channel  */ 
  CSI_IF_SPL                  =0x01,     /* 2SEG: 1SEG Y in one channel , 1SEG UV in second channel */
  CSI_IF_PL                   =0x02,     /* 3SEG YUV444 */
  CSI_IF_PL_SPL               =0x03,     /* 3SEG YUV444 to 2SEG YUV422  */
  
  CSI_IF_CCIR656_1CH          =0x04,   /* 1SEG ccir656  1ch   */
  CSI_IF_CCIR656_1CH_SPL      =0x05,   /* 2SEG  ccir656 1ch   */
  CSI_IF_CCIR656_1CH_PL       =0x06,   /* 3SEG ccir656  1ch   */
  CSI_IF_CCIR656_1CH_PL_SPL   =0x07,   /* 3SEG to 2SEG ccir656  1ch   */
  
  CSI_IF_CCIR656_2CH          =0x0c,   /* D7~D0:ccir656  2ch   */
  CSI_IF_CCIR656_4CH          =0x0d,   /* D7~D0:ccir656  4ch   */
  
  CSI_IF_MIPI                 =0x80,   /* MIPI CSI */   
};

/*
 *  data width
 */
enum csi_data_width
{
  CSI_8BIT      =0, 
  CSI_10BIT     =1,   
  CSI_12BIT     =2,
};

/*
 * input data format
 */
enum csi_input_fmt
{
  CSI_RAW=0,       /* raw stream  */
  //CSI_BAYER=1,
  CSI_YUV422=3,    /* yuv422      */
  CSI_YUV420=4,    /* yuv420      */
};

/*
 * output data format
 */
enum csi_output_fmt
{
  /* only when input is raw */
  CSI_FIELD_RAW_8    = 0,
  CSI_FIELD_RAW_10   = 1,
  CSI_FIELD_RAW_12   = 2,
  CSI_FIELD_RGB565   = 4,
  CSI_FIELD_RGB888   = 5,
  CSI_FIELD_PRGB888  = 6,
  CSI_FRAME_RAW_8    = 8,
  CSI_FRAME_RAW_10   = 9,
  CSI_FRAME_RAW_12   = 10,
  CSI_FRAME_RGB565   = 12,
  CSI_FRAME_RGB888   = 13,
  CSI_FRAME_PRGB888  = 14,
  
  /* only when input is bayer */
  //CSI_PLANAR_RGB242 = 0,               /* planar rgb242 */
  
  /* only when input is yuv422/yuv420 */
  CSI_FIELD_PLANAR_YUV422 = 0,         /* parse a field(odd or even) into planar yuv420 */
  CSI_FIELD_PLANAR_YUV420 = 1,         /* parse a field(odd or even) into planar yuv420 */
  CSI_FRAME_PLANAR_YUV420 = 2,         /* parse and reconstruct every 2 fields(odd and even) into a frame, format is planar yuv420 */
  CSI_FRAME_PLANAR_YUV422 = 3,
  CSI_FIELD_UV_CB_YUV422  = 4,         
  CSI_FIELD_UV_CB_YUV420  = 5,
  CSI_FRAME_UV_CB_YUV420  = 6,
  CSI_FRAME_UV_CB_YUV422  = 7,
  CSI_FIELD_MB_YUV422     = 8,
  CSI_FIELD_MB_YUV420     = 9,
  CSI_FRAME_MB_YUV420     = 10,
  CSI_FRAME_MB_YUV422     = 11,
  CSI_FIELD_UV_CB_YUV422_10  = 12,
  CSI_FIELD_UV_CB_YUV420_10  = 13,
  //CSI_INTLC_INTLV_YUV422  = 15,
};

/*
 * field sequenc or polarity
 */

enum csi_field
{
  /* For Embedded Sync timing*/
  CSI_FIELD_TF    = 0,    /* top filed first */
  CSI_FIELD_BF    = 1,    /* bottom field first */
  
  /* For External Sync timing */
  CSI_FIELD_NEG = 0,      /* field negtive indicates odd field */
  CSI_FIELD_POS = 1,      /* field postive indicates odd field */
};

/*
 * input field selection, only when input is ccir656
 */
enum csi_field_sel
{
  CSI_ODD,    /* odd field */
  CSI_EVEN,   /* even field */
  CSI_EITHER, /* either field */
};


/*
 * input source type
 */
enum csi_src_type
{
  CSI_PROGRESSIVE=0,    /* progressive */
  CSI_INTERLACE=1,      /* interlace */
};

/*
 * input data sequence
 */
enum csi_input_seq
{
  /* only when input is yuv422 */
  CSI_YUYV=0,
  CSI_YVYU,
  CSI_UYVY,
  CSI_VYUY,
  
  /* only when input is byer */
  CSI_RGRG=0,               /* first line sequence is RGRG... */
  CSI_GRGR,                 /* first line sequence is GRGR... */
  CSI_BGBG,                 /* first line sequence is BGBG... */
  CSI_GBGB,                 /* first line sequence is GBGB... */
};

/*
 * input reference signal polarity
 */
enum csi_ref_pol
{
  CSI_LOW,    /* active low */
  CSI_HIGH,   /* active high */
};

/*
 * input data valid of the input clock edge type
 */
enum csi_edge_pol
{
  CSI_FALLING,    /* active falling */
  CSI_RISING,     /* active rising */
};

/*
 * csi interface configuration
 */
struct csi_if_cfg
{
  enum csi_src_type   src_type;     /* interlaced or progressive */
  enum csi_data_width data_width;   /* csi data width */
  enum csi_if         interface;    /* csi interface */
};

/*
 * csi timing configuration
 */
struct csi_timing_cfg
{
  enum csi_field      field;    /* top or bottom field first / field polarity */
  enum csi_ref_pol    vref;     /* input vref signal polarity */
  enum csi_ref_pol    href;     /* input href signal polarity */
  enum csi_edge_pol   sample;   /* input data valid of the input clock edge type */
};

/*
 * csi mode configuration
 */
struct csi_fmt_cfg
{
  enum csi_input_fmt      input_fmt;   /* input data format */
  enum csi_output_fmt     output_fmt;  /* output data format */
  enum csi_field_sel      field_sel;   /* input field selection */
  enum csi_input_seq      input_seq;   /* input data sequence */
  enum csi_data_width     data_width;   /* csi data width */
};

/*
 * csi buffer
 */

enum csi_buf_sel
{
  CSI_BUF_0_A = 0,    /* FIFO for Y address A */  
  CSI_BUF_0_B,        /* FIFO for Y address B */
  CSI_BUF_1_A,        /* FIFO for Cb address A */
  CSI_BUF_1_B,        /* FIFO for Cb address B */
  CSI_BUF_2_A,        /* FIFO for Cr address A */
  CSI_BUF_2_B,        /* FIFO for Cr address B */
};


/*
 * csi capture status
 */
struct csi_capture_status
{
  _Bool               picture_in_progress;  
  _Bool               video_in_progress;    
};

enum csi_cap_mode
{
  CSI_SCAP = 1,
  CSI_VCAP    ,
};

/*
 * csi interrupt
 */
enum csi_int_sel
{
  CSI_INT_CAPTURE_DONE     = 0X1,
  CSI_INT_FRAME_DONE       = 0X2,
  CSI_INT_BUF_0_OVERFLOW   = 0X4,
  CSI_INT_BUF_1_OVERFLOW   = 0X8,
  CSI_INT_BUF_2_OVERFLOW   = 0X10,
  CSI_INT_PROTECTION_ERROR = 0X20,
  CSI_INT_HBLANK_OVERFLOW  = 0X40,
  CSI_INT_VSYNC_TRIG       = 0X80,
  CSI_INT_ALL              = 0XFF,
};

/*
 * csi interrupt status
 */
struct csi_int_status
{
  int capture_done;
  int frame_done;
  int buf_0_overflow;
  int buf_1_overflow;
  int buf_2_overflow;
  int  protection_error;
  int hblank_overflow;
  int vsync_trig;
};


#define MAX_CH_NUM 4

#define CSI_ALIGN_4K(x) (((x) + (4095)) & ~(4095))
#define CSI_ALIGN_32B(x) (((x) + (31)) & ~(31))
#define CSI_ALIGN_16B(x) (((x) + (15)) & ~(15))
#define CSI_ALIGN_8B(x) (((x) + (7)) & ~(7))


enum bus_if
{
  PARALLEL = 0,
  BT656,
  CSI2,
};

enum ref_pol
{
  ACTIVE_LOW,    /* active low */
  ACTIVE_HIGH,   /* active high */
};

enum edge_pol
{
  FALLING,    /* active falling */
  RISING,     /* active rising */
};

/*
 * the same define as enum csi_input_seq
 */
enum bus_fmt_seq
{
  /* only when input is yuv422 */
  YUYV=0,
  YVYU,
  UYVY,
  VYUY,
  
  /* only when input is byer */
  RGRG=0,               /* first line sequence is RGRG... */
  GRGR,                 /* first line sequence is GRGR... */
  BGBG,                 /* first line sequence is BGBG... */
  GBGB,                 /* first line sequence is GBGB... */
};

//enum bus_fmt
//{
//  RAW=0,     /* raw stream  */
//  YUV444,    /* yuv444    */
//  YUV422,    /* yuv422      */
//  YUV420,    /* yuv420      */
//  RGB565,    /* RGB565      */
//  RGB888,    /* RGB888      */
//};



enum field {
  FIELD_ANY           = 0, /* driver can choose from none,
           top, bottom, interlaced
           depending on whatever it thinks
           is approximate ... */
  FIELD_NONE          = 1, /* this device has no fields ... */
  FIELD_TOP           = 2, /* top field only */
  FIELD_BOTTOM        = 3, /* bottom field only */
  FIELD_INTERLACED    = 4, /* both fields interlaced */
  FIELD_SEQ_TB        = 5, /* both fields sequential into one
           buffer, top-bottom order */
  FIELD_SEQ_BT        = 6, /* same as above + bottom-top order */
  FIELD_ALTERNATE     = 7, /* both fields alternating into
           separate buffers */
  FIELD_INTERLACED_TB = 8, /* both fields interlaced, top field
           first and the top field is
           transmitted first */
  FIELD_INTERLACED_BT = 9, /* both fields interlaced, top field
           first and the bottom field is
           transmitted first */
};

enum bus_pixelcode {
  BUS_FMT_FIXED = 0x0001,

  /* RGB - next is 0x1009 */
  BUS_FMT_RGB444_2X8_PADHI_BE = 0x1001,
  BUS_FMT_RGB444_2X8_PADHI_LE = 0x1002,
  BUS_FMT_RGB555_2X8_PADHI_BE = 0x1003,
  BUS_FMT_RGB555_2X8_PADHI_LE = 0x1004,
  BUS_FMT_BGR565_2X8_BE = 0x1005,
  BUS_FMT_BGR565_2X8_LE = 0x1006,
  BUS_FMT_RGB565_2X8_BE = 0x1007,
  BUS_FMT_RGB565_2X8_LE = 0x1008,

  BUS_FMT_RGB565_16X1 = 0x1009,
  BUS_FMT_RGB888_24X1 = 0x100a,

  /* YUV (including grey) - next is 0x2014 */
  BUS_FMT_Y8_1X8 = 0x2001,
  BUS_FMT_UYVY8_1_5X8 = 0x2002,
  BUS_FMT_VYUY8_1_5X8 = 0x2003,
  BUS_FMT_YUYV8_1_5X8 = 0x2004,
  BUS_FMT_YVYU8_1_5X8 = 0x2005,
  BUS_FMT_UYVY8_2X8 = 0x2006,
  BUS_FMT_VYUY8_2X8 = 0x2007,
  BUS_FMT_YUYV8_2X8 = 0x2008,
  BUS_FMT_YVYU8_2X8 = 0x2009,
  BUS_FMT_Y10_1X10 = 0x200a,
  BUS_FMT_YUYV10_2X10 = 0x200b,
  BUS_FMT_YVYU10_2X10 = 0x200c,
  BUS_FMT_Y12_1X12 = 0x2013,
  BUS_FMT_UYVY8_1X16 = 0x200f,
  BUS_FMT_VYUY8_1X16 = 0x2010,
  BUS_FMT_YUYV8_1X16 = 0x2011,
  BUS_FMT_YVYU8_1X16 = 0x2012,
  BUS_FMT_YUYV10_1X20 = 0x200d,
  BUS_FMT_YVYU10_1X20 = 0x200e,

  BUS_FMT_YUV8_1X24 = 0x2014,
  BUS_FMT_UYVY8_16X1 = 0x2015,
  BUS_FMT_UYVY10_20X1 = 0x2016,
  BUS_FMT_YY8_UYVY8_12X1 = 0x2018,
  BUS_FMT_YY10_UYVY10_15X1 = 0x2019,

  /* Bayer - next is 0x3015 */
  BUS_FMT_SBGGR8_1X8 = 0x3001,
  BUS_FMT_SGBRG8_1X8 = 0x3013,
  BUS_FMT_SGRBG8_1X8 = 0x3002,
  BUS_FMT_SRGGB8_1X8 = 0x3014,
  BUS_FMT_SBGGR10_DPCM8_1X8 = 0x300b,
  BUS_FMT_SGBRG10_DPCM8_1X8 = 0x300c,
  BUS_FMT_SGRBG10_DPCM8_1X8 = 0x3009,
  BUS_FMT_SRGGB10_DPCM8_1X8 = 0x300d,
  BUS_FMT_SBGGR10_2X8_PADHI_BE = 0x3003,
  BUS_FMT_SBGGR10_2X8_PADHI_LE = 0x3004,
  BUS_FMT_SBGGR10_2X8_PADLO_BE = 0x3005,
  BUS_FMT_SBGGR10_2X8_PADLO_LE = 0x3006,
  BUS_FMT_SBGGR10_1X10 = 0x3007,
  BUS_FMT_SGBRG10_1X10 = 0x300e,
  BUS_FMT_SGRBG10_1X10 = 0x300a,
  BUS_FMT_SRGGB10_1X10 = 0x300f,
  BUS_FMT_SBGGR12_1X12 = 0x3008,
  BUS_FMT_SGBRG12_1X12 = 0x3010,
  BUS_FMT_SGRBG12_1X12 = 0x3011,
  BUS_FMT_SRGGB12_1X12 = 0x3012,

  BUS_FMT_SBGGR8_8X1 = 0x3015,
  BUS_FMT_SGBRG8_8X1 = 0x3016,
  BUS_FMT_SGRBG8_8X1 = 0x3017,
  BUS_FMT_SRGGB8_8X1 = 0x3018,
  BUS_FMT_SBGGR10_10X1 = 0x3019,
  BUS_FMT_SGBRG10_10X1 = 0x301a,
  BUS_FMT_SGRBG10_10X1 = 0x301b,
  BUS_FMT_SRGGB10_10X1 = 0x301c,
  BUS_FMT_SBGGR12_12X1 = 0x301d,
  BUS_FMT_SGBRG12_12X1 = 0x301e,
  BUS_FMT_SGRBG12_12X1 = 0x301f,
  BUS_FMT_SRGGB12_12X1 = 0x3020,

  /* JPEG compressed formats - next is 0x4002 */
  BUS_FMT_JPEG_1X8 = 0x4001,
};

enum bus_pixeltype
{
  BUS_FMT_RGB565,
  BUS_FMT_RGB888,
  BUS_FMT_Y_U_V,
  BUS_FMT_YY_YUYV,
  BUS_FMT_YY_YVYU,
  BUS_FMT_YY_UYVY,
  BUS_FMT_YY_VYUY,
  BUS_FMT_YUYV,
  BUS_FMT_YVYU,
  BUS_FMT_UYVY,
  BUS_FMT_VYUY,
  BUS_FMT_SBGGR,
  BUS_FMT_SGBRG,
  BUS_FMT_SGRBG,
  BUS_FMT_SRGGB,
};

enum pixel_fmt
{
  PIX_FMT_RGB565 = 0x0000,
  PIX_FMT_RGB888,
  PIX_FMT_PRGB888,
  PIX_FMT_YUYV = 0x1000,
  PIX_FMT_YVYU,
  PIX_FMT_UYVY,
  PIX_FMT_VYUY,
  PIX_FMT_YUV422P_8 = 0x2000,
  PIX_FMT_YVU422P_8,
  PIX_FMT_YUV420P_8,
  PIX_FMT_YVU420P_8,
  PIX_FMT_YUV420SP_8 = 0x3000,
  PIX_FMT_YVU420SP_8,
  PIX_FMT_YUV422SP_8,
  PIX_FMT_YVU422SP_8,
  PIX_FMT_YUV420SP_10,
  PIX_FMT_YVU420SP_10,
  PIX_FMT_YUV422SP_10,
  PIX_FMT_YVU422SP_10,
  PIX_FMT_YUV420MB_8 = 0x4000,
  PIX_FMT_YVU420MB_8,
  PIX_FMT_YUV422MB_8,
  PIX_FMT_YVU422MB_8,
  PIX_FMT_SBGGR_8 = 0x5000,
  PIX_FMT_SGBRG_8,
  PIX_FMT_SGRBG_8,
  PIX_FMT_SRGGB_8,
  PIX_FMT_SBGGR_10,
  PIX_FMT_SGBRG_10,
  PIX_FMT_SGRBG_10,
  PIX_FMT_SRGGB_10,
  PIX_FMT_SBGGR_12,
  PIX_FMT_SGBRG_12,
  PIX_FMT_SGRBG_12,
  PIX_FMT_SRGGB_12,
  PIX_FMT_NONE = 0xffff,
};

enum pixel_fmt_type {
  RGB565,
  RGB888,
  PRGB888,
  YUV422_INTLVD,
  YUV422_PL,
  YUV422_SPL,
  YUV422_MB,
  YUV420_PL,
  YUV420_SPL,
  YUV420_MB,
  BAYER_RGB,
};

enum bit_width
{
  W_1BIT,
  W_2BIT,
  W_4BIT,
  W_6BIT,
  W_8BIT,
  W_10BIT,
  W_12BIT,
  W_14BIT,
  W_16BIT,
  W_20BIT,
  W_24BIT,
  W_32BIT,
};


struct bus_timing
{
  enum ref_pol  href_pol;
  enum ref_pol  vref_pol;
  enum edge_pol pclk_sample;
  enum ref_pol  field_even_pol; //field 0/1 0:odd 1:even
};

struct bus_info
{
  enum   bus_if           bus_if;
  struct  bus_timing      bus_tmg;
//  enum   bit_width      bus_width;
//  enum   bit_width      bus_precision;
  enum   bus_pixelcode    bus_ch_fmt[MAX_CH_NUM]; /* define the same as V4L2 */
  unsigned int            ch_total_num;
};

struct frame_size
{
  unsigned int width;   /* in pixel unit */
  unsigned int height;  /* in pixel unit */
};

struct frame_offset
{
  unsigned int hoff;    /* in pixel unit */
  unsigned int voff;    /* in pixel unit */
};

/* 
 * frame arrangement
 * Indicate that how the channel images are put together into one buffer
 */
  
struct frame_arrange
{
  unsigned char column;
  unsigned char row;
};

struct frame_info
{
  struct frame_arrange  arrange;
  struct frame_size     ch_size[MAX_CH_NUM];
  struct frame_offset   ch_offset[MAX_CH_NUM];
  enum   pixel_fmt    pix_ch_fmt[MAX_CH_NUM];
  enum   field      ch_field[MAX_CH_NUM];   /* define the same as V4L2 */
  unsigned int      frm_byte_size;
};


extern int  bsp_csi_set_base_addr(  unsigned int addr);
extern void bsp_csi_enable( );
extern void bsp_csi_disable( );
extern void bsp_csi_reset( );
extern int  bsp_csi_set_fmt(  struct bus_info *bus_info, struct frame_info *frame_info);
extern int  bsp_csi_set_size(  struct bus_info *bus_info, struct frame_info *frame_info);
extern void bsp_csi_set_addr(  u64 buf_base_addr);
extern void bsp_csi_cap_start(  unsigned int ch_total_num, enum csi_cap_mode csi_cap_mode);
extern void bsp_csi_cap_stop(  unsigned int ch_total_num, enum csi_cap_mode csi_cap_mode);
extern void bsp_csi_int_enable(  unsigned int ch, enum csi_int_sel interrupt);
extern void bsp_csi_int_disable(  unsigned int ch, enum csi_int_sel interrupt);
extern void bsp_csi_int_get_status(  unsigned int ch,struct csi_int_status *status);
extern void bsp_csi_int_clear_status(  unsigned int ch, enum csi_int_sel interrupt);

int csi_set_base_addr(  unsigned int addr);
void csi_enable( );
void csi_disable( );
void csi_if_cfg(  struct csi_if_cfg *csi_if_cfg);
void csi_timing_cfg(  struct csi_timing_cfg *csi_tmg_cfg);
void csi_fmt_cfg(  unsigned int ch, struct csi_fmt_cfg *csi_fmt_cfg);
void csi_set_buffer_address(  unsigned int ch, enum csi_buf_sel buf, u64 addr);
u64 csi_get_buffer_address(  unsigned int ch, enum csi_buf_sel buf);
void csi_capture_start(  unsigned int ch_total_num, enum csi_cap_mode csi_cap_mode);
void csi_capture_stop(  unsigned int ch_total_num, enum csi_cap_mode csi_cap_mode);
void csi_capture_get_status(  unsigned int ch, struct csi_capture_status *status);
void csi_set_size(  unsigned int ch, unsigned int length_h, unsigned int length_v, unsigned int buf_length_y, unsigned int buf_length_c);
void csi_set_offset(  unsigned int ch, unsigned int start_h, unsigned int start_v);
void csi_int_enable(  unsigned int ch, enum csi_int_sel interrupt);
void csi_int_disable(  unsigned int ch, enum csi_int_sel interrupt);
void csi_int_get_status(  unsigned int ch,struct csi_int_status *status);
void csi_int_clear_status(  unsigned int ch, enum csi_int_sel interrupt);
#endif
