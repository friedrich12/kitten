/* 
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */

#include "camera.h"
#include "cam_def.h"
#include "cci.h"

static struct frame_arrange frm_arrange_gbl;
static unsigned int			line_stride_y_ch_gbl[MAX_CH_NUM];
static unsigned int			line_stride_c_ch_gbl[MAX_CH_NUM];
static unsigned int			buf_height_y_ch_gbl[MAX_CH_NUM];
static unsigned int			buf_height_cb_ch_gbl[MAX_CH_NUM];
static unsigned int			buf_height_cr_ch_gbl[MAX_CH_NUM];
static unsigned int			line_stride_y_row_gbl[MAX_CH_NUM];
static unsigned int			line_stride_c_row_gbl[MAX_CH_NUM];
static uint64_t				buf_addr_plane0[MAX_CH_NUM];
static uint64_t				buf_addr_plane1[MAX_CH_NUM];
static uint64_t				buf_addr_plane2[MAX_CH_NUM];

struct csi		  csi;
struct ccu		  ccu;
struct dma_buffer dma;

static inline uint32_t
__csiX_read32(uintptr_t offset)
{
	printk("reading from: vaddr=0x%016lx\n", csi.csi_virt_start + offset);
	return readl(csi.csi_virt_start + offset);
}

static inline void
__csiX_write32(uintptr_t offset,
			   uint32_t	 value)
{
	printk("Writing %x\n", value);
	printk("writing to: vaddr=0x%016lx\n", csi.csi_virt_start + offset);
	writel(value, csi.csi_virt_start + offset);
}

static inline void
__csi_reg_clr_set(uint32_t reg, uint32_t clr_bits, uint32_t set_bits)
{
	uint32_t v = __csi_read32(reg);
	__csi_write32(reg, (v & ~clr_bits) | (set_bits & clr_bits));
}


enum bus_pixeltype find_bus_type(enum bus_pixelcode code) {
  switch(code) {
    case BUS_FMT_BGR565_2X8_BE:
    case BUS_FMT_BGR565_2X8_LE:
    case BUS_FMT_RGB565_2X8_BE:
    case BUS_FMT_RGB565_2X8_LE:   
    case BUS_FMT_RGB565_16X1   :
      return BUS_FMT_RGB565;
    case BUS_FMT_UYVY8_2X8:
    case BUS_FMT_UYVY8_1X16:
    case BUS_FMT_UYVY8_16X1:
    case BUS_FMT_UYVY10_20X1:
      return BUS_FMT_UYVY;
    case BUS_FMT_VYUY8_2X8:
    case BUS_FMT_VYUY8_1X16:
      return BUS_FMT_VYUY;
    case BUS_FMT_YUYV8_2X8:
    case BUS_FMT_YUYV10_2X10: 
    case BUS_FMT_YUYV8_1X16:
    case BUS_FMT_YUYV10_1X20:
      return BUS_FMT_YUYV;      
    case BUS_FMT_YVYU8_2X8:
    case BUS_FMT_YVYU10_2X10:
    case BUS_FMT_YVYU8_1X16:
    case BUS_FMT_YVYU10_1X20: 
      return BUS_FMT_YVYU;
    case BUS_FMT_SBGGR8_1X8:
    case BUS_FMT_SBGGR10_DPCM8_1X8:
    case BUS_FMT_SBGGR10_1X10:
    case BUS_FMT_SBGGR12_1X12:
    case BUS_FMT_SBGGR8_8X1:
    case BUS_FMT_SBGGR10_10X1:
    case BUS_FMT_SBGGR12_12X1:
      return BUS_FMT_SBGGR;
    case BUS_FMT_SGBRG8_1X8:
    case BUS_FMT_SGBRG10_DPCM8_1X8:
    case BUS_FMT_SGBRG10_1X10:
    case BUS_FMT_SGBRG12_1X12:
    case BUS_FMT_SGBRG8_8X1:
    case BUS_FMT_SGBRG10_10X1:
    case BUS_FMT_SGBRG12_12X1:
      return BUS_FMT_SGBRG;
    case BUS_FMT_SGRBG8_1X8:
    case BUS_FMT_SGRBG10_DPCM8_1X8: 
    case BUS_FMT_SGRBG10_1X10:
    case BUS_FMT_SGRBG12_1X12:
    case BUS_FMT_SGRBG8_8X1:
    case BUS_FMT_SGRBG10_10X1:  
    case BUS_FMT_SGRBG12_12X1:
      return BUS_FMT_SGRBG;
    case BUS_FMT_SRGGB8_1X8:
    case BUS_FMT_SRGGB10_DPCM8_1X8:
    case BUS_FMT_SRGGB10_1X10:
    case BUS_FMT_SRGGB12_1X12:
    case BUS_FMT_SRGGB8_8X1:
    case BUS_FMT_SRGGB10_10X1:
    case BUS_FMT_SRGGB12_12X1:
      return BUS_FMT_SRGGB;
    case BUS_FMT_YUV8_1X24:
      return BUS_FMT_Y_U_V;
    case BUS_FMT_YY8_UYVY8_12X1:
    case BUS_FMT_YY10_UYVY10_15X1:
      return BUS_FMT_YY_UYVY;
    default:
      return BUS_FMT_UYVY;
  }
}

enum bit_width find_bus_width(enum bus_pixelcode code) {
  switch(code) {
    case BUS_FMT_RGB565_16X1:
    case BUS_FMT_UYVY8_16X1:
    case BUS_FMT_UYVY10_20X1:
    case BUS_FMT_SBGGR8_8X1:
    case BUS_FMT_SBGGR10_10X1:
    case BUS_FMT_SBGGR12_12X1:      
    case BUS_FMT_SGBRG8_8X1:
    case BUS_FMT_SGBRG10_10X1:
    case BUS_FMT_SGBRG12_12X1:      
    case BUS_FMT_SGRBG8_8X1:
    case BUS_FMT_SGRBG10_10X1:  
    case BUS_FMT_SGRBG12_12X1:
    case BUS_FMT_SRGGB8_8X1:
    case BUS_FMT_SRGGB10_10X1:
    case BUS_FMT_SRGGB12_12X1:
    case BUS_FMT_YY8_UYVY8_12X1:
    case BUS_FMT_YY10_UYVY10_15X1:
      return W_1BIT;
    case BUS_FMT_BGR565_2X8_BE:
    case BUS_FMT_BGR565_2X8_LE:
    case BUS_FMT_RGB565_2X8_BE:
    case BUS_FMT_RGB565_2X8_LE:   
    case BUS_FMT_UYVY8_2X8: 
    case BUS_FMT_VYUY8_2X8:     
    case BUS_FMT_YUYV8_2X8:
    case BUS_FMT_YVYU8_2X8:     
    case BUS_FMT_SBGGR8_1X8:
    case BUS_FMT_SBGGR10_DPCM8_1X8:     
    case BUS_FMT_SGBRG8_1X8:
    case BUS_FMT_SGBRG10_DPCM8_1X8:
    case BUS_FMT_SGRBG8_1X8:
    case BUS_FMT_SGRBG10_DPCM8_1X8: 
    case BUS_FMT_SRGGB8_1X8:
    case BUS_FMT_SRGGB10_DPCM8_1X8:
      return W_8BIT;  
    case BUS_FMT_YUYV10_2X10: 
    case BUS_FMT_YVYU10_2X10:
    case BUS_FMT_SBGGR10_1X10:
    case BUS_FMT_SGBRG10_1X10:
    case BUS_FMT_SGRBG10_1X10:      
    case BUS_FMT_SRGGB10_1X10:
      return W_10BIT;
    case BUS_FMT_SBGGR12_1X12:
    case BUS_FMT_SGBRG12_1X12:
    case BUS_FMT_SGRBG12_1X12:
    case BUS_FMT_SRGGB12_1X12:
      return W_12BIT; 
    case BUS_FMT_UYVY8_1X16:
    case BUS_FMT_VYUY8_1X16:
    case BUS_FMT_YUYV8_1X16:
    case BUS_FMT_YVYU8_1X16:
      return W_16BIT;           
    case BUS_FMT_YVYU10_1X20:
    case BUS_FMT_YUYV10_1X20:
      return W_20BIT;           
    case BUS_FMT_YUV8_1X24:
      return W_24BIT;         
    default:
      return W_8BIT;
  }
}

enum bit_width find_bus_precision(enum bus_pixelcode code) {
  switch(code) {
    case BUS_FMT_RGB565_16X1:
    case BUS_FMT_BGR565_2X8_BE:
    case BUS_FMT_BGR565_2X8_LE:
    case BUS_FMT_RGB565_2X8_BE:
    case BUS_FMT_RGB565_2X8_LE:       
    case BUS_FMT_SBGGR8_8X1:      
    case BUS_FMT_SGBRG8_8X1:      
    case BUS_FMT_SGRBG8_8X1:      
    case BUS_FMT_SRGGB8_8X1:  
    case BUS_FMT_SBGGR8_1X8:
    case BUS_FMT_SGBRG8_1X8:      
    case BUS_FMT_SGRBG8_1X8:      
    case BUS_FMT_SRGGB8_1X8:    
    case BUS_FMT_SBGGR10_DPCM8_1X8:     
    case BUS_FMT_SGBRG10_DPCM8_1X8:
    case BUS_FMT_SGRBG10_DPCM8_1X8: 
    case BUS_FMT_SRGGB10_DPCM8_1X8: 
    case BUS_FMT_UYVY8_16X1:
    case BUS_FMT_UYVY8_2X8: 
    case BUS_FMT_VYUY8_2X8:     
    case BUS_FMT_YUYV8_2X8:
    case BUS_FMT_YVYU8_2X8:       
    case BUS_FMT_UYVY8_1X16:
    case BUS_FMT_VYUY8_1X16:
    case BUS_FMT_YUYV8_1X16:
    case BUS_FMT_YVYU8_1X16:
    case BUS_FMT_YUV8_1X24:     
    case BUS_FMT_YY8_UYVY8_12X1:
      return W_8BIT;      
    case BUS_FMT_SBGGR10_10X1:
    case BUS_FMT_SGBRG10_10X1:      
    case BUS_FMT_SGRBG10_10X1:        
    case BUS_FMT_SRGGB10_10X1:          
    case BUS_FMT_SBGGR10_1X10:
    case BUS_FMT_SGBRG10_1X10:
    case BUS_FMT_SGRBG10_1X10:      
    case BUS_FMT_SRGGB10_1X10:      
    case BUS_FMT_YUYV10_2X10: 
    case BUS_FMT_YVYU10_2X10:
    case BUS_FMT_YVYU10_1X20:
    case BUS_FMT_YUYV10_1X20:                                         
    case BUS_FMT_UYVY10_20X1:
    case BUS_FMT_YY10_UYVY10_15X1:
      return W_10BIT;
    case BUS_FMT_SBGGR12_12X1:      
    case BUS_FMT_SGBRG12_12X1:      
    case BUS_FMT_SGRBG12_12X1:
    case BUS_FMT_SRGGB12_12X1:
    case BUS_FMT_SBGGR12_1X12:
    case BUS_FMT_SGBRG12_1X12:
    case BUS_FMT_SGRBG12_1X12:
    case BUS_FMT_SRGGB12_1X12:
      return W_12BIT;       
    default:
      return W_8BIT;
  }
}

enum pixel_fmt_type find_pixel_fmt_type(enum pixel_fmt code)
{
  switch(code) {
    case PIX_FMT_RGB565:
      return RGB565;
    case PIX_FMT_RGB888:
      return RGB888;
    case PIX_FMT_PRGB888:
      return PRGB888;
    case PIX_FMT_YUYV:
    case PIX_FMT_YVYU:
    case PIX_FMT_UYVY:
    case PIX_FMT_VYUY:
      return YUV422_INTLVD;
    case PIX_FMT_YUV422P_8:
    case PIX_FMT_YVU422P_8:
      return YUV422_PL;
    case PIX_FMT_YUV420P_8:
    case PIX_FMT_YVU420P_8:
      return YUV420_PL;
    case PIX_FMT_YUV420SP_8:
    case PIX_FMT_YVU420SP_8:
    case PIX_FMT_YUV420SP_10:
    case PIX_FMT_YVU420SP_10:
      return YUV420_SPL;
    case PIX_FMT_YUV422SP_8:
    case PIX_FMT_YVU422SP_8:
    case PIX_FMT_YUV422SP_10:
    case PIX_FMT_YVU422SP_10:
      return YUV422_SPL;
    case PIX_FMT_YUV420MB_8:
    case PIX_FMT_YVU420MB_8:
      return YUV420_MB;
    case PIX_FMT_YUV422MB_8:
    case PIX_FMT_YVU422MB_8:
      return YUV422_MB;
    case PIX_FMT_SBGGR_8:
    case PIX_FMT_SGBRG_8:
    case PIX_FMT_SGRBG_8:
    case PIX_FMT_SRGGB_8:
    case PIX_FMT_SBGGR_10:
    case PIX_FMT_SGBRG_10:
    case PIX_FMT_SGRBG_10:
    case PIX_FMT_SRGGB_10:
    case PIX_FMT_SBGGR_12:
    case PIX_FMT_SGBRG_12:
    case PIX_FMT_SGRBG_12:
    case PIX_FMT_SRGGB_12:
      return BAYER_RGB;
    default:
      return BAYER_RGB;
  }
}

int
test_camera()
{
}

int
read_image_from_camera()
{
}

#define PWDN SUNXI_GPE(15)
#define RESET SUNXI_GPE(14)


int
sensor_power_on()
{
	printk("CAMERA POWER ON\n");
	/* Set gpios to poewr on*/
	/* Power on reset */
	sunxi_gpio_set_cfgpin(PWDN, SUNXI_GPIO_OUTPUT);	 /* Set the gpio to output */
	sunxi_gpio_set_cfgpin(RESET, SUNXI_GPIO_OUTPUT); /* Set the gpio to output */
	/* power down io */
	sunxi_gpio_output(PWDN, CSI_STBY_ON);
	/* Reset on io */
	sunxi_gpio_output(RESET, CSI_RST_ON);
	
    int N = 12000;
	while (N--);
	
        /* power on reset */
	sunxi_gpio_output(PWDN, CSI_STBY_OFF);
	sunxi_gpio_output(RESET, CSI_RST_OFF);
	int B = 12000;
	while (B--)
		;

	printk("CAMERA POWER ON DONE\n");
}


void
camera_sensor_init(){
	uint32_t reg = 0;


    dma.fifo_phys_start = CSI_BUF_BEGIN;
    dma.fifo_size = 0x4000;

    csi.csi_phys_start = CSI_BASE_ADDRESS;
	csi.csi_phys_size  = 0x4000;

	ccu.ccu_phys_start = CCU_BASE_ADDRESS;
	ccu.ccu_phys_size  = 0x1000;

    printk("MAPPING IN MEMORY...\n");
	ccu.ccu_virt_start = ioremap_nocache(ccu.ccu_phys_start, ccu.ccu_phys_size);
	csi.csi_virt_start = ioremap_nocache(csi.csi_phys_start, csi.csi_phys_size);
	dma.fifo_virt_start = ioremap_nocache(dma.fifo_phys_start, dma.fifo_size);

	printk("csi base: vaddr=%p\n", csi.csi_virt_start);
	printk("csi base: paddr=%p\n", virt_to_phys(csi.csi_virt_start));

	printk("ccu base: vaddr=%p\n", ccu.ccu_virt_start);
	printk("ccu base: paddr=%p\n", virt_to_phys(ccu.ccu_virt_start));
	
    /* Enable PLL and enable clock output */
	reg = __ccu_read32(PLL_PERIPH0_CTRL_REG);
	__ccu_write32(PLL_PERIPH0_CTRL_REG, reg | 1 << 18 | 1 << 24);
	printk("PLL PER0: %x\n", __ccu_read32(PLL_PERIPH0_CTRL_REG));

	/* Enable PLL and enable clock output */
	reg = __ccu_read32(PLL_PERIPH1_CTRL_REG);
	__ccu_write32(PLL_PERIPH1_CTRL_REG, reg | 1 << 18 | 1 << 24);
	printk("PLL PER1: %x\n", __ccu_read32(PLL_PERIPH1_CTRL_REG));

	/* CSI Gating */
	__ccu_write32(BUS_CLK_GATING_REG1, 1 << 8);
	printk("CSI BUS CTRL: %x\n", __ccu_read32(BUS_CLK_GATING_REG1));

	__ccu_write32(BUS_SOFT_RST_REG1, 0xffffffff);

	/* Turn on Gating Special Clock */
	__ccu_write32(CSI_MISC_CLK_REG, 1 << 31);
	printk("CSI MISC: %x\n", __ccu_read32(CSI_MISC_CLK_REG));

	/* Master Clock Set To PERIPH1 */
	/* Gating speical clock is on */
	/* Gating master clock is on*/
	__ccu_write32(CSI_CLK_REG, (1 << 31 | 1 << 15 | 1 << 9));
	printk("CSI CLK: %x\n", __ccu_read32(CSI_CLK_REG));

    /*TODO: Figure out how to turn on the sensor*/
    //sensor_power_on();

    sensor_power_on();
    
    bsp_csi_cci_init_helper();
   

    /*  SENSOR DETECT */
    printk("SENSOR DETECT\n");
    sensor_detect();
    while(true){

    }

    int size = sizeof(sensor_default_regs)/sizeof(sensor_default_regs[0]);
    sensor_write_array(sensor_default_regs, size);
	
    bsp_csi_enable();
    bsp_csi_disable();
    bsp_csi_enable();
    bsp_csi_set_addr(dma.fifo_phys_start);
    bsp_csi_cap_start(0,CSI_VCAP);
/*  csi_set_fmt();
	csi_int_enable();
	csi_capture_start();*/

	for (;;) {
        struct csi_int_status status;
		bsp_csi_int_get_status(0, &status);

	    printk("CAPTURE DONE = %d\n", status.capture_done);
	    printk("FRAME DONE = %d\n", status.frame_done);
	    printk("BUF 0 OVERFLOW = %d\n" , status.buf_0_overflow);	
	    printk("BUF 1 OVERFLOW = %d\n" , status.buf_1_overflow);	
	    printk("BUF 2 OVERFLOW = %d\n" , status.buf_2_overflow);	
	    printk("STATUS PROTECTION ERROR = %d\n", status.protection_error);
    	printk("HBLANK OVERFLOW = %d\n", status.hblank_overflow);
	    printk("STATUS VSYNC TRIG = %d\n", status.vsync_trig);
    }
}

#define ADDR_BIT_R_SHIFT 0
#define CLK_POL 0

/* open module */
void csi_enable()
{
	vfe_reg_set(CSI_EN_REG_OFF, 1 << CSI_EN_REG_CSI_EN);
}

void csi_disable()
{
	vfe_reg_clr( CSI_EN_REG_OFF, 1 << CSI_EN_REG_CSI_EN);
}

/* configure */
void csi_if_cfg(  struct csi_if_cfg *csi_if_cfg)
{
	vfe_reg_clr_set(CSI_IF_CFG_REG_OFF, CSI_IF_CFG_REG_SRC_TYPE_MASK,
				csi_if_cfg->src_type << CSI_IF_CFG_REG_SRC_TYPE);
  
	if(csi_if_cfg->interface < 0x80)
		vfe_reg_clr_set(CSI_IF_CFG_REG_OFF, CSI_IF_CFG_REG_CSI_IF_MASK,
					csi_if_cfg->interface << CSI_IF_CFG_REG_CSI_IF);
	else
		vfe_reg_clr_set(CSI_IF_CFG_REG_OFF, CSI_IF_CFG_REG_MIPI_IF_MASK,
					1 << CSI_IF_CFG_REG_MIPI_IF);
  	
	vfe_reg_clr_set(CSI_IF_CFG_REG_OFF, CSI_IF_CFG_REG_IF_DATA_WIDTH_MASK,
				csi_if_cfg->data_width << CSI_IF_CFG_REG_IF_DATA_WIDTH);	
}

void csi_timing_cfg(  struct csi_timing_cfg *csi_tmg_cfg)
{
	vfe_reg_clr_set(CSI_IF_CFG_REG_OFF, CSI_IF_CFG_REG_VREF_POL_MASK,
				csi_tmg_cfg->vref<< CSI_IF_CFG_REG_VREF_POL);	
	vfe_reg_clr_set(CSI_IF_CFG_REG_OFF, CSI_IF_CFG_REG_HREF_POL_MASK,
				csi_tmg_cfg->href<< CSI_IF_CFG_REG_HREF_POL);
	vfe_reg_clr_set(CSI_IF_CFG_REG_OFF, CSI_IF_CFG_REG_CLK_POL_MASK,
				((csi_tmg_cfg->sample==CLK_POL)?1:0)<< CSI_IF_CFG_REG_CLK_POL);
	vfe_reg_clr_set(CSI_IF_CFG_REG_OFF, CSI_IF_CFG_REG_FIELD_MASK,
				csi_tmg_cfg->field<< CSI_IF_CFG_REG_FIELD);
}

void csi_fmt_cfg(  unsigned int ch, struct csi_fmt_cfg *csi_fmt_cfg)
{
	vfe_reg_clr_set(CSI_CH_CFG_REG_OFF+ch*CSI_CH_OFF, CSI_CH_CFG_REG_INPUT_FMT_MASK,
				csi_fmt_cfg->input_fmt<< CSI_CH_CFG_REG_INPUT_FMT);
	vfe_reg_clr_set(CSI_CH_CFG_REG_OFF+ch*CSI_CH_OFF, CSI_CH_CFG_REG_OUTPUT_FMT_MASK,
				csi_fmt_cfg->output_fmt<< CSI_CH_CFG_REG_OUTPUT_FMT);
	vfe_reg_clr_set(CSI_CH_CFG_REG_OFF+ch*CSI_CH_OFF, CSI_CH_CFG_REG_FIELD_SEL_MASK,
				csi_fmt_cfg->field_sel<< CSI_CH_CFG_REG_FIELD_SEL);
	vfe_reg_clr_set(CSI_CH_CFG_REG_OFF+ch*CSI_CH_OFF, CSI_CH_CFG_REG_INPUT_SEQ_MASK,
				csi_fmt_cfg->input_seq<< CSI_CH_CFG_REG_INPUT_SEQ);
}

/* buffer */
void csi_set_buffer_address(  unsigned int ch, enum csi_buf_sel buf, u64 addr)
{
	vfe_reg_clr_set(CSI_CH_F0_BUFA_REG_OFF+ch*CSI_CH_OFF+ (buf<<2), 0xffffffff,
				addr >> ADDR_BIT_R_SHIFT);	
}

u64 csi_get_buffer_address(  unsigned int ch, enum csi_buf_sel buf)
{
	unsigned int reg_val = vfe_reg_readl(CSI_CH_F0_BUFA_REG_OFF + ch*CSI_CH_OFF + (buf<<2));
	return reg_val << ADDR_BIT_R_SHIFT;
}

/* capture */
void csi_capture_start(  unsigned int ch_total_num, enum csi_cap_mode csi_cap_mode)
{
	u32 reg_val =	(((ch_total_num == 4) ? csi_cap_mode:0)<<24) +
                       (((ch_total_num == 3) ? csi_cap_mode:0)<<16) + 
                       (((ch_total_num == 2) ? csi_cap_mode:0)<<8 )+
                       (((ch_total_num == 1) ? csi_cap_mode:0));
       	vfe_reg_writel(CSI_CAP_REG_OFF, reg_val);
}

void csi_capture_stop(  unsigned int ch_total_num, enum csi_cap_mode csi_cap_mode)
{
	vfe_reg_writel(CSI_CAP_REG_OFF, 0);
}


void csi_capture_get_status(  unsigned int ch, struct csi_capture_status *status)
{
	unsigned int reg_val = vfe_reg_readl(CSI_CH_STA_REG_OFF + ch*CSI_CH_OFF);
	status->picture_in_progress 	= (reg_val>>CSI_CH_STA_REG_SCAP_STA)&0x1;
	status->video_in_progress	 	= (reg_val>>CSI_CH_STA_REG_VCAP_STA)&0x1;	
//	status->field_status			= (reg_val>>CSI_CH_STA_REG_FIELD_STA)&0x1;	
}

/* size */
void csi_set_size(  unsigned int ch, unsigned int length_h, unsigned int length_v, unsigned int buf_length_y, unsigned int buf_length_c)
{
  	vfe_reg_clr_set(CSI_CH_HSIZE_REG_OFF + ch*CSI_CH_OFF, CSI_CH_HSIZE_REG_HOR_LEN_MASK,
				length_h<<CSI_CH_HSIZE_REG_HOR_LEN);
  	vfe_reg_clr_set(CSI_CH_VSIZE_REG_OFF + ch*CSI_CH_OFF, CSI_CH_VSIZE_REG_VER_LEN_MASK,
				length_v<<CSI_CH_VSIZE_REG_VER_LEN);
  	vfe_reg_clr_set(CSI_CH_BUF_LEN_REG_OFF + ch*CSI_CH_OFF, CSI_CH_BUF_LEN_REG_BUF_LEN_MASK,
				buf_length_y<<CSI_CH_BUF_LEN_REG_BUF_LEN);
  	vfe_reg_clr_set(CSI_CH_BUF_LEN_REG_OFF + ch*CSI_CH_OFF, CSI_CH_BUF_LEN_REG_BUF_LEN_C_MASK,
				buf_length_c<<CSI_CH_BUF_LEN_REG_BUF_LEN_C);  
}


/* offset */
void csi_set_offset(  unsigned int ch, unsigned int start_h, unsigned int start_v)
{
    	vfe_reg_clr_set(CSI_CH_HSIZE_REG_OFF + ch*CSI_CH_OFF, CSI_CH_HSIZE_REG_HOR_START_MASK,
				start_h<<CSI_CH_HSIZE_REG_HOR_START);
    	vfe_reg_clr_set(CSI_CH_VSIZE_REG_OFF + ch*CSI_CH_OFF, CSI_CH_VSIZE_REG_VER_START_MASK,
				start_v<<CSI_CH_VSIZE_REG_VER_START);		
}


/* interrupt */
void csi_int_enable(  unsigned int ch, enum csi_int_sel interrupt)
{
      	vfe_reg_set(CSI_CH_INT_EN_REG_OFF + ch*CSI_CH_OFF, interrupt);
}

void csi_int_disable(  unsigned int ch, enum csi_int_sel interrupt)
{
	vfe_reg_clr(CSI_CH_INT_EN_REG_OFF + ch*CSI_CH_OFF, interrupt);
}

void csi_int_get_status(  unsigned int ch,struct csi_int_status *status)
{
	unsigned int reg_val =	vfe_reg_readl(CSI_CH_INT_STA_REG_OFF + ch*CSI_CH_OFF);
	status->capture_done		= (reg_val >> CSI_CH_INT_STA_REG_CD_PD)&0x1;
	status->frame_done		= (reg_val >> CSI_CH_INT_STA_REG_FD_PD)&0x1;
	status->buf_0_overflow	= (reg_val >> CSI_CH_INT_STA_REG_FIFO0_OF_PD)&0x1;
	status->buf_1_overflow	= (reg_val >> CSI_CH_INT_STA_REG_FIFO1_OF_PD)&0x1;
	status->buf_2_overflow 	= (reg_val >> CSI_CH_INT_STA_REG_FIFO2_OF_PD)&0x1;
	status->protection_error 	= (reg_val >> CSI_CH_INT_STA_REG_PRTC_ERR_PD)&0x1;
	status->hblank_overflow  	= (reg_val >> CSI_CH_INT_STA_REG_HB_OF_PD)&0x1;
	status->vsync_trig		= (reg_val >> CSI_CH_INT_STA_REG_VS_PD)&0x1;
}

void csi_int_clear_status(  unsigned int ch, enum csi_int_sel interrupt)
{
	//vfe_reg_clr_set(csi_base_addr[sel] + CSI_CH_INT_STA_REG_OFF + ch*CSI_CH_OFF, 0xffffffff,interrupt);  
       	vfe_reg_writel(CSI_CH_INT_STA_REG_OFF, interrupt);
	//vfe_reg_set(csi_base_addr[sel] + CSI_CH_INT_STA_REG_OFF + ch*CSI_CH_OFF, interrupt);
}

void bsp_csi_enable()
{
  csi_enable();
}

void bsp_csi_disable()
{
  csi_disable();
}

void bsp_csi_reset()
{
  csi_disable();
  csi_enable();
}


/* bsp_csi_set_fmt
 * function:
 * set csi timing/format/size, return 0(ok) or -1(error)
 *
 * struct bus_info
 * {
 *  enum   bus_if       bus_if;
 *  struct  bus_timing      bus_tmg;
 *  enum   bus_pixelcode    bus_ch_fmt[MAX_CH_NUM];
 *  unsigned int        ch_total_num;
 * };
 *
 * struct frame_info
 * {
 *   struct frame_arrange  arrange;
 *   struct frame_size     ch_size[MAX_CH_NUM];
 *   struct frame_offset   ch_offset[MAX_CH_NUM];
 *   enum pixel_fmt    pix_ch_fmt[MAX_CH_NUM];
 *   enum field      ch_field[MAX_CH_NUM];
 *   unsigned int      frm_byte_size;
 * };
 *
 * input parameters: 
 * bus_if,
 * bus_tmg,
 * bus_ch_fmt,
 * ch_total_num,
 * pix_ch_fmt,
 * ch_field,
 *
 * output parameters:
 * none
 */
 

int bsp_csi_set_fmt(struct bus_info *bus_info, struct frame_info *frame_info)
{
  struct csi_if_cfg if_cfg;
  struct csi_timing_cfg tmg_cfg;
  struct csi_fmt_cfg fmt_cfg[MAX_CH_NUM];
  unsigned int is_buf_itl[MAX_CH_NUM];
  enum bus_pixeltype bus_pix_type[MAX_CH_NUM];
  enum bit_width bus_width[MAX_CH_NUM];
  enum bit_width bus_precision[MAX_CH_NUM];

  unsigned int ch;

  //csi_disable(sel);//add for csi change fmt@20130111
//set csi interface
//depends on bus interface
  switch(bus_info->bus_if)  {
    case PARALLEL:
      if_cfg.interface = CSI_IF_INTLV;
      break;
    case BT656:
      if_cfg.interface = CSI_IF_CCIR656_1CH;
      break;
    case CSI2:
      if_cfg.interface = CSI_IF_MIPI;
      break;
    default:
      return -1;
  }

  for(ch=0;ch<bus_info->ch_total_num;ch++) {
  //get bus pixel type, bus width and bus data precision
  //depends on bus format
    bus_pix_type[ch] = find_bus_type(bus_info->bus_ch_fmt[ch]);
    bus_width[ch] = find_bus_width(bus_info->bus_ch_fmt[ch]);
    bus_precision[ch] = find_bus_precision(bus_info->bus_ch_fmt[ch]);

    if(if_cfg.interface != CSI_IF_MIPI)
      if_cfg.data_width = bus_width[ch];

  //set csi field info
  //depends on field format
    switch(frame_info->ch_field[ch]) {
      case FIELD_ANY:
      case FIELD_NONE:
        if_cfg.src_type = CSI_PROGRESSIVE;
        fmt_cfg[ch].field_sel = CSI_EITHER;
        break;
      case FIELD_TOP:
        if_cfg.src_type = CSI_INTERLACE;
        fmt_cfg[ch].field_sel = CSI_ODD;
        break;
      case FIELD_BOTTOM:
        if_cfg.src_type = CSI_INTERLACE;
        fmt_cfg[ch].field_sel = CSI_EVEN;
        break;
      case FIELD_INTERLACED:
      case FIELD_INTERLACED_TB:
        if_cfg.src_type = CSI_INTERLACE;
        tmg_cfg.field = CSI_FIELD_TF;
        fmt_cfg[ch].field_sel = CSI_EITHER;       
        break;
      case FIELD_INTERLACED_BT:
        if_cfg.src_type = CSI_INTERLACE;
        tmg_cfg.field = CSI_FIELD_BF;
        fmt_cfg[ch].field_sel = CSI_EITHER;       
        break;
      default:
        return -1;
    }

  //if the target frame buffer is interlaced
  //depends on field format
    if(frame_info->ch_field[ch] == FIELD_INTERLACED || \
           frame_info->ch_field[ch] == FIELD_INTERLACED_TB || \
           frame_info->ch_field[ch] == FIELD_INTERLACED_BT)
      is_buf_itl[ch] = 1;
    else
      is_buf_itl[ch] = 0;
    
  //set input/output format and size/line stride/offset
  //depends on bus format,bus precision,target frame format, field format

    switch(frame_info->pix_ch_fmt[ch]) {
      case PIX_FMT_RGB565:
        if(bus_pix_type[ch] == BUS_FMT_RGB565) {
          fmt_cfg[ch].input_fmt = CSI_RAW;
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RGB565:CSI_FIELD_RGB565;
        } else {
          return -1;
        }
        break;
      case PIX_FMT_RGB888:
        if(bus_pix_type[ch] == BUS_FMT_RGB888) {
          fmt_cfg[ch].input_fmt = CSI_RAW;
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RGB888:CSI_FIELD_RGB888;
        } else {
          return -1;
        }
        break;
      case PIX_FMT_PRGB888:
        if(bus_pix_type[ch] == BUS_FMT_RGB888) {
          fmt_cfg[ch].input_fmt = CSI_RAW;
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_PRGB888:CSI_FIELD_PRGB888;
        } else {
          return -1;
        }
        break;
      case PIX_FMT_YUYV:
        if(bus_pix_type[ch] == BUS_FMT_YUYV) {
          fmt_cfg[ch].input_fmt = CSI_RAW;
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_8:CSI_FIELD_RAW_8;
        } else {
          return -1;
        }
        break;
      case PIX_FMT_YVYU:
        if(bus_pix_type[ch] == BUS_FMT_YVYU) {
          fmt_cfg[ch].input_fmt = CSI_RAW;
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_8:CSI_FIELD_RAW_8;
        } else {
          return -1;
        }         
        break;
      case PIX_FMT_UYVY:
        if(bus_pix_type[ch] == BUS_FMT_UYVY) {
          fmt_cfg[ch].input_fmt = CSI_RAW;
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_8:CSI_FIELD_RAW_8;
        } else {
          return -1;
        }         
        break;
      case PIX_FMT_VYUY:
        if(bus_pix_type[ch] == BUS_FMT_VYUY) {
          fmt_cfg[ch].input_fmt = CSI_RAW;
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_8:CSI_FIELD_RAW_8;
        } else {
          return -1;
        }         
        break;
      case PIX_FMT_YUV420P_8:
      case PIX_FMT_YVU420P_8:
      case PIX_FMT_YUV420SP_8:
      case PIX_FMT_YVU420SP_8:
      case PIX_FMT_YUV420MB_8:
      case PIX_FMT_YVU420MB_8:
        if(bus_pix_type[ch] == BUS_FMT_YUYV || \
           bus_pix_type[ch] == BUS_FMT_YVYU || \
           bus_pix_type[ch] == BUS_FMT_UYVY || \
           bus_pix_type[ch] == BUS_FMT_VYUY)
          fmt_cfg[ch].input_fmt = CSI_YUV422;
        else if(bus_pix_type[ch] == BUS_FMT_YY_YUYV || \
              bus_pix_type[ch] == BUS_FMT_YY_YVYU || \
              bus_pix_type[ch] == BUS_FMT_YY_UYVY || \
              bus_pix_type[ch] == BUS_FMT_YY_VYUY)
          fmt_cfg[ch].input_fmt = CSI_YUV420;
        else if(bus_pix_type[ch] == BUS_FMT_SBGGR || \
              bus_pix_type[ch] == BUS_FMT_SGBRG || \
              bus_pix_type[ch] == BUS_FMT_SRGGB || \
              bus_pix_type[ch] == BUS_FMT_SGRBG)
          fmt_cfg[ch].input_fmt = CSI_RAW;  //parse to isp
          
        if(fmt_cfg[ch].input_fmt == CSI_YUV422 || \
           fmt_cfg[ch].input_fmt == CSI_YUV420) {
          if(     frame_info->pix_ch_fmt[ch] == PIX_FMT_YUV420P_8  || frame_info->pix_ch_fmt[ch] == PIX_FMT_YVU420P_8)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_PLANAR_YUV420:CSI_FIELD_PLANAR_YUV420;
          else if(frame_info->pix_ch_fmt[ch] == PIX_FMT_YUV420SP_8 || frame_info->pix_ch_fmt[ch] == PIX_FMT_YVU420SP_8)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_UV_CB_YUV420:CSI_FIELD_UV_CB_YUV420;
          else if(frame_info->pix_ch_fmt[ch] == PIX_FMT_YUV420MB_8 || frame_info->pix_ch_fmt[ch] == PIX_FMT_YVU420MB_8)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_MB_YUV420:CSI_FIELD_MB_YUV420;
        } else {
          if(bus_precision[ch] == W_8BIT)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_8:CSI_FIELD_RAW_8;
          else if(bus_precision[ch] == W_10BIT)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_10:CSI_FIELD_RAW_10;
          else if(bus_precision[ch] == W_12BIT)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_12:CSI_FIELD_RAW_12;
        }
        break;
      case PIX_FMT_YUV422P_8:
      case PIX_FMT_YVU422P_8:     
      case PIX_FMT_YUV422SP_8:
      case PIX_FMT_YVU422SP_8:
      case PIX_FMT_YUV422MB_8:
      case PIX_FMT_YVU422MB_8:
        if(bus_pix_type[ch] == BUS_FMT_YUYV || \
           bus_pix_type[ch] == BUS_FMT_YVYU || \
           bus_pix_type[ch] == BUS_FMT_UYVY || \
           bus_pix_type[ch] == BUS_FMT_VYUY)
          fmt_cfg[ch].input_fmt = CSI_YUV422;
        else if(bus_pix_type[ch] == BUS_FMT_SBGGR || \
              bus_pix_type[ch] == BUS_FMT_SGBRG || \
              bus_pix_type[ch] == BUS_FMT_SRGGB || \
              bus_pix_type[ch] == BUS_FMT_SGRBG)
          fmt_cfg[ch].input_fmt = CSI_RAW;  //parse to isp

        if(fmt_cfg[ch].input_fmt == CSI_YUV422) {
          if(frame_info->pix_ch_fmt[ch] == PIX_FMT_YUV422P_8 || frame_info->pix_ch_fmt[ch] == PIX_FMT_YVU422P_8)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_PLANAR_YUV422:CSI_FIELD_PLANAR_YUV422;
          else if(frame_info->pix_ch_fmt[ch] == PIX_FMT_YUV422SP_8 || frame_info->pix_ch_fmt[ch] == PIX_FMT_YVU422SP_8)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_UV_CB_YUV422:CSI_FIELD_UV_CB_YUV422;
          else if(frame_info->pix_ch_fmt[ch] == PIX_FMT_YUV422MB_8 || frame_info->pix_ch_fmt[ch] == PIX_FMT_YVU422MB_8)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_MB_YUV422:CSI_FIELD_MB_YUV422;
        } else {
          if(bus_precision[ch] == W_8BIT)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_8:CSI_FIELD_RAW_8;
          else if(bus_precision[ch] == W_10BIT)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_10:CSI_FIELD_RAW_10;
          else if(bus_precision[ch] == W_12BIT)
            fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_12:CSI_FIELD_RAW_12;
        }
        break;
      case PIX_FMT_YUV420SP_10://for debug
      case PIX_FMT_YVU420SP_10:
        fmt_cfg[ch].input_fmt = CSI_YUV420;
        fmt_cfg[ch].output_fmt = CSI_FIELD_UV_CB_YUV420_10;
        break;
      case PIX_FMT_YUV422SP_10://for debug
      case PIX_FMT_YVU422SP_10:
        fmt_cfg[ch].input_fmt = CSI_YUV422;
        fmt_cfg[ch].output_fmt = CSI_FIELD_UV_CB_YUV422_10;
        break;
      case PIX_FMT_SBGGR_8://all below are for debug
      case PIX_FMT_SGBRG_8:
      case PIX_FMT_SGRBG_8:
      case PIX_FMT_SRGGB_8:
      case PIX_FMT_SBGGR_10:
      case PIX_FMT_SGBRG_10:
      case PIX_FMT_SGRBG_10:
      case PIX_FMT_SRGGB_10:
      case PIX_FMT_SBGGR_12:
      case PIX_FMT_SGBRG_12:
      case PIX_FMT_SGRBG_12:
      case PIX_FMT_SRGGB_12:
        fmt_cfg[ch].input_fmt = CSI_RAW;
        if(bus_precision[ch] == W_8BIT)
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_8:CSI_FIELD_RAW_8;
        else if(bus_precision[ch] == W_10BIT)
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_10:CSI_FIELD_RAW_10;
        else if(bus_precision[ch] == W_12BIT)
          fmt_cfg[ch].output_fmt = (is_buf_itl[ch] == 1)? CSI_FRAME_RAW_12:CSI_FIELD_RAW_12;
        break;
      default:
        return -1;    
    }

  //change input sequence
  //depends on bus format and target frame format
    switch(frame_info->pix_ch_fmt[ch]) {
      case PIX_FMT_YUV420P_8:
      case PIX_FMT_YUV420SP_8:
      case PIX_FMT_YUV420MB_8:
      case PIX_FMT_YUV422P_8:
      case PIX_FMT_YUV422SP_8:
      case PIX_FMT_YUV422MB_8:
      case PIX_FMT_YUV420SP_10:
      case PIX_FMT_YUV422SP_10:
        if(bus_pix_type[ch] == BUS_FMT_YUYV)
          fmt_cfg[ch].input_seq = CSI_YUYV;
        else if(bus_pix_type[ch] == BUS_FMT_YVYU)
          fmt_cfg[ch].input_seq = CSI_YVYU;     
        else if(bus_pix_type[ch] == BUS_FMT_UYVY)
          fmt_cfg[ch].input_seq = CSI_UYVY; 
        else if(bus_pix_type[ch] == BUS_FMT_VYUY)
          fmt_cfg[ch].input_seq = CSI_VYUY; 
        break;
      case PIX_FMT_YVU420P_8:     
      case PIX_FMT_YVU420SP_8:
      case PIX_FMT_YVU420MB_8:
      case PIX_FMT_YVU422P_8:     
      case PIX_FMT_YVU422SP_8:
      case PIX_FMT_YVU422MB_8:
      case PIX_FMT_YVU420SP_10:
      case PIX_FMT_YVU422SP_10:
        if(bus_pix_type[ch] == BUS_FMT_YUYV)
          fmt_cfg[ch].input_seq = CSI_YVYU;
        else if(bus_pix_type[ch] == BUS_FMT_YVYU)
          fmt_cfg[ch].input_seq = CSI_YUYV;     
        else if(bus_pix_type[ch] == BUS_FMT_UYVY)
          fmt_cfg[ch].input_seq = CSI_VYUY; 
        else if(bus_pix_type[ch] == BUS_FMT_VYUY)
          fmt_cfg[ch].input_seq = CSI_UYVY; 
        break;
      default:
        fmt_cfg[ch].input_seq = CSI_UYVY;
        break;
    }
    
    csi_fmt_cfg(ch, &fmt_cfg[ch]);
    
  }

  csi_if_cfg(&if_cfg);

//set csi timing parameter
	tmg_cfg.href = bus_info->bus_tmg.href_pol;
	tmg_cfg.vref = bus_info->bus_tmg.vref_pol;
	tmg_cfg.sample = bus_info->bus_tmg.pclk_sample; 
	tmg_cfg.field = 0; //todo for 16bits.

  csi_timing_cfg(&tmg_cfg);
  //csi_enable(sel);//add for csi change fmt@20130111
  return 0; 
}


/* bsp_csi_set_size
 * function:
 * set csi timing/format/size, return 0(ok) or -1(error)
 *
 * struct bus_info
 * {
 *  enum   bus_if           bus_if;
 *  struct  bus_timing      bus_tmg;
 *  enum   bus_pixelcode    bus_ch_fmt[MAX_CH_NUM];
 *  unsigned int            ch_total_num;
 * };
 *
 * struct frame_info
 * {
 *   struct frame_arrange  arrange;
 *   struct frame_size     ch_size[MAX_CH_NUM];
 *   struct frame_offset   ch_offset[MAX_CH_NUM];
 *   enum pixel_fmt        pix_ch_fmt[MAX_CH_NUM];
 *   enum field            ch_field[MAX_CH_NUM];
 *   unsigned int          frm_byte_size;
 * };
 *
 * input parameters: 
 * bus_ch_fmt,
 * ch_total_num,
 * arrange,
 * ch_size,
 * ch_offset,
 * pix_ch_fmt,
 * ch_field,
 *
 * output parameters:
 * frm_byte_size;
 */


int bsp_csi_set_size(struct bus_info *bus_info, struct frame_info *frame_info)
{
  enum bit_width bus_width[MAX_CH_NUM];
  enum bit_width bus_precision[MAX_CH_NUM];
  unsigned int is_buf_itl[MAX_CH_NUM];
  unsigned int input_len_h[MAX_CH_NUM],input_len_v[MAX_CH_NUM];
  unsigned int start_h[MAX_CH_NUM],start_v[MAX_CH_NUM];
  unsigned int buf_height_y_ch[MAX_CH_NUM],buf_height_cb_ch[MAX_CH_NUM],buf_height_cr_ch[MAX_CH_NUM]; 
  unsigned int line_stride_y_ch[MAX_CH_NUM],line_stride_c_ch[MAX_CH_NUM];
  unsigned int line_stride_y_row[MAX_CH_NUM],line_stride_c_row[MAX_CH_NUM];
  unsigned int ch,i,j,row,column;

  row = frame_info->arrange.row;
  column = frame_info->arrange.column;
  frm_arrange_gbl.row = row;
  frm_arrange_gbl.column = column;
  
  for(ch=0;ch<bus_info->ch_total_num;ch++) {

  //if the target frame buffer is interlaced
  //depends on field format
    if(frame_info->ch_field[ch] == FIELD_INTERLACED || \
           frame_info->ch_field[ch] == FIELD_INTERLACED_TB || \
           frame_info->ch_field[ch] == FIELD_INTERLACED_BT)
      is_buf_itl[ch] = 1;
    else
      is_buf_itl[ch] = 0;

    bus_width[ch] = find_bus_width(bus_info->bus_ch_fmt[ch]);
    bus_precision[ch] = find_bus_precision(bus_info->bus_ch_fmt[ch]);

    //common initial value
    buf_height_cb_ch[ch] = 0;
    buf_height_cr_ch[ch] = 0;
    input_len_h[ch] = frame_info->ch_size[ch].width;
    input_len_v[ch] = frame_info->ch_size[ch].height >> ((is_buf_itl[ch] == 1)?1:0);    
    start_h[ch] = frame_info->ch_offset[ch].hoff;
    start_v[ch] = frame_info->ch_offset[ch].voff;
    
    switch(frame_info->pix_ch_fmt[ch]) {
      case PIX_FMT_RGB565:
        line_stride_y_ch[ch] = frame_info->ch_size[ch].width <<1;
        line_stride_y_ch[ch] = frame_info->ch_size[ch].width <<1;
        line_stride_c_ch[ch] = 0;
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        break;
      case PIX_FMT_RGB888:
        line_stride_y_ch[ch] = frame_info->ch_size[ch].width * 3;
        line_stride_c_ch[ch] = 0;
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        break;
      case PIX_FMT_PRGB888:
        line_stride_y_ch[ch] = frame_info->ch_size[ch].width <<2;
        line_stride_c_ch[ch] = 0;
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        break;
      case PIX_FMT_YUYV:
      case PIX_FMT_YVYU:
      case PIX_FMT_UYVY:
      case PIX_FMT_VYUY:
        input_len_h[ch] = frame_info->ch_size[ch].width <<1;
        start_h[ch] = frame_info->ch_offset[ch].hoff >>1<<3;
        start_v[ch] = frame_info->ch_offset[ch].voff >>1<<3;
        line_stride_y_ch[ch] = frame_info->ch_size[ch].width <<1;
        line_stride_c_ch[ch] = 0;
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        break;
      case PIX_FMT_YUV420P_8:
      case PIX_FMT_YVU420P_8:
        line_stride_y_ch[ch] = CSI_ALIGN_16B(frame_info->ch_size[ch].width);
        line_stride_c_ch[ch] = CSI_ALIGN_16B(line_stride_y_ch[ch]>>1);
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        buf_height_cb_ch[ch] = buf_height_y_ch[ch] >>1;
        buf_height_cr_ch[ch] = buf_height_y_ch[ch] >>1;
        break;
      case PIX_FMT_YUV422P_8:
      case PIX_FMT_YVU422P_8: 
        line_stride_y_ch[ch] = CSI_ALIGN_16B(frame_info->ch_size[ch].width);
        line_stride_c_ch[ch] = CSI_ALIGN_16B(line_stride_y_ch[ch]>>1);
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        buf_height_cb_ch[ch] = buf_height_y_ch[ch];
        buf_height_cr_ch[ch] = buf_height_y_ch[ch];
        break;
      case PIX_FMT_YUV420SP_8:
      case PIX_FMT_YVU420SP_8:
      case PIX_FMT_YUV420MB_8:
      case PIX_FMT_YVU420MB_8:
        line_stride_y_ch[ch] = CSI_ALIGN_16B(frame_info->ch_size[ch].width);
        line_stride_c_ch[ch] = line_stride_y_ch[ch];
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        buf_height_cb_ch[ch] = buf_height_y_ch[ch] >>1;
        break;
      case PIX_FMT_YUV422SP_8:
      case PIX_FMT_YVU422SP_8:
      case PIX_FMT_YUV422MB_8:
      case PIX_FMT_YVU422MB_8:
        line_stride_y_ch[ch] = CSI_ALIGN_16B(frame_info->ch_size[ch].width);
        line_stride_c_ch[ch] = line_stride_y_ch[ch];
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        buf_height_cb_ch[ch] = buf_height_y_ch[ch];
        break;
      case PIX_FMT_YUV420SP_10://for debug
      case PIX_FMT_YVU420SP_10:
        line_stride_y_ch[ch] = frame_info->ch_size[ch].width <<1;
        line_stride_c_ch[ch] = line_stride_y_ch[ch];
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        buf_height_cb_ch[ch] = buf_height_y_ch[ch] >>1;
        break;
      case PIX_FMT_YUV422SP_10://for debug
      case PIX_FMT_YVU422SP_10:
        line_stride_y_ch[ch] = frame_info->ch_size[ch].width <<1;
        line_stride_c_ch[ch] = line_stride_y_ch[ch];
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        buf_height_cb_ch[ch] = buf_height_y_ch[ch];
        break;
      case PIX_FMT_SBGGR_8://all below are for debug
      case PIX_FMT_SGBRG_8:
      case PIX_FMT_SGRBG_8:
      case PIX_FMT_SRGGB_8:
      case PIX_FMT_SBGGR_10:
      case PIX_FMT_SGBRG_10:
      case PIX_FMT_SGRBG_10:
      case PIX_FMT_SRGGB_10:
      case PIX_FMT_SBGGR_12:
      case PIX_FMT_SGBRG_12:
      case PIX_FMT_SGRBG_12:
      case PIX_FMT_SRGGB_12:
        line_stride_y_ch[ch] = frame_info->ch_size[ch].width <<((bus_precision[ch] == W_8BIT)?0:1);
        buf_height_y_ch[ch] = frame_info->ch_size[ch].height;
        break;
      default:
        break;    
    }
    line_stride_y_ch_gbl[ch] = line_stride_y_ch[ch];
    line_stride_c_ch_gbl[ch] = line_stride_c_ch[ch];
    buf_height_y_ch_gbl[ch]  = buf_height_y_ch[ch];
    buf_height_cb_ch_gbl[ch] = buf_height_cb_ch[ch];
    buf_height_cr_ch_gbl[ch] = buf_height_cr_ch[ch];
    csi_set_offset(ch, start_h[ch], start_v[ch]);
  }


  //assume channels at the same row has the same height
  //assume channels at the same column has the same width
  for(i=0;i<row;i++) {
      line_stride_y_row[i] = 0;
      line_stride_c_row[i] = 0;     
    for(j=0;j<column;j++) {
      ch = i*column + j;  //ch=i when column==1
      line_stride_y_row[i] += line_stride_y_ch[ch];
      line_stride_c_row[i] += line_stride_c_ch[ch];
      line_stride_y_row_gbl[i] = line_stride_y_row[i];
      line_stride_c_row_gbl[i] = line_stride_c_row[i];
      csi_set_size(ch, input_len_h[ch], input_len_v[ch], line_stride_y_row[i], line_stride_c_row[i]);
    }
  }
  frame_info->frm_byte_size = 0;
  for(ch=0;ch<row*column;ch++) {
    frame_info->frm_byte_size += line_stride_y_ch[ch] * buf_height_y_ch[ch] + \
                   line_stride_c_ch[ch] * buf_height_cb_ch[ch] + \
                   line_stride_c_ch[ch] * buf_height_cr_ch[ch];
  }
  
  return 0;
}

/* bsp_csi_set_addr
 * function:
 * set csi output address, no return
 * must be called after bsp_csi_set_size
 *
 * input parameters: 
 * buffer base address
 *
 */

void bsp_csi_set_addr(u64 buf_base_addr)
{
  u64 buf_addr_plane0[MAX_CH_NUM];
  u64 buf_addr_plane1[MAX_CH_NUM];
  u64 buf_addr_plane2[MAX_CH_NUM];
  unsigned int ch,i,j,k,l,row,column;

  row = frm_arrange_gbl.row;
  column = frm_arrange_gbl.column;

  for(i=0;i<row;i++)
    for(j=0;j<column;j++) {
      ch = i*column+j;
      buf_addr_plane0[ch] = buf_base_addr;
      buf_addr_plane1[ch] = buf_addr_plane0[ch] \
                  + line_stride_y_row_gbl[i] * buf_height_y_ch_gbl[ch];
      buf_addr_plane2[ch] = buf_addr_plane1[ch] \
                  + line_stride_c_row_gbl[i] * buf_height_cb_ch_gbl[ch];
      for(k=0;k<j;k++) {
        buf_addr_plane0[ch] += line_stride_y_ch_gbl[i*column+k-1];
        buf_addr_plane1[ch] += line_stride_c_ch_gbl[i*column+k-1];
        buf_addr_plane2[ch] += line_stride_c_ch_gbl[i*column+k-1];
      }

      for(l=1;l<i;l++) {
        buf_addr_plane0[ch] += ((line_stride_y_row_gbl[l-1] * buf_height_y_ch_gbl[l*column+j-1]) \
                    + (line_stride_c_row_gbl[l-1] * buf_height_cb_ch_gbl[l*column+j-1]) \
                    + (line_stride_c_row_gbl[l-1] * buf_height_cr_ch_gbl[l*column+j-1]));
        buf_addr_plane1[ch] += ((line_stride_c_row_gbl[l-1] * buf_height_cb_ch_gbl[l*column+j-1]) \
                    + (line_stride_c_row_gbl[l-1] * buf_height_cr_ch_gbl[l*column+j-1]) \
                    + (line_stride_y_row_gbl[l]   * buf_height_y_ch_gbl[l*column+j]));
        buf_addr_plane2[ch] += ((line_stride_c_row_gbl[l-1] * buf_height_cr_ch_gbl[l*column+j-1]) \
                    + (line_stride_y_row_gbl[l]   * buf_height_y_ch_gbl[l*column+j]) \
                    + (line_stride_c_row_gbl[l]   * buf_height_cb_ch_gbl[l*column+j]));
      }     
      csi_set_buffer_address(ch,CSI_BUF_0_A, buf_addr_plane0[ch]);
      csi_set_buffer_address(ch,CSI_BUF_1_A, buf_addr_plane1[ch]);
      csi_set_buffer_address(ch,CSI_BUF_2_A, buf_addr_plane2[ch]);
    }
}


void bsp_csi_cap_start( unsigned int ch_total_num, enum csi_cap_mode csi_cap_mode)
{
  csi_capture_start(ch_total_num, csi_cap_mode);
}

void bsp_csi_cap_stop( unsigned int ch_total_num, enum csi_cap_mode csi_cap_mode)
{
  csi_capture_stop(ch_total_num, csi_cap_mode);
}

void bsp_csi_int_enable( unsigned int ch, enum csi_int_sel interrupt)
{
  csi_int_enable(ch, interrupt);
}

void bsp_csi_int_disable( unsigned int ch, enum csi_int_sel interrupt)
{
  csi_int_disable(ch, interrupt);
}

void bsp_csi_int_get_status( unsigned int ch,struct csi_int_status *status)
{
  csi_int_get_status(ch, status);
}

void bsp_csi_int_clear_status( unsigned int ch, enum csi_int_sel interrupt)
{
  csi_int_clear_status(ch, interrupt);
}


DRIVER_INIT("late", camera_sensor_init);
