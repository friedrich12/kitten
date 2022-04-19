/* 
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */

#include "camera.h"

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

struct csi csi;
struct ccu ccu;
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

int test_camera()
{
}

int read_image_from_camera()
{
}

uint32_t csi_get_buffer_address();
#define PWDN SUNXI_GPE(15)
#define RESET SUNXI_GPE(14)


int
camera_power_on()
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
	/* power on reset */
	sunxi_gpio_output(PWDN, CSI_STBY_OFF);
	int N = 12000;
	while (N--)
		;
	sunxi_gpio_output(RESET, CSI_RST_OFF);
	int B = 12000;
	while (B--)
		;

	printk("CAMERA POWER ON DONE\n");
}

int
camera_init()
{
	uint32_t reg = 0;

	csi.csi_phys_start = CSI_BASE_ADDRESS;
	csi.csi_phys_size  = 0x4000;

	ccu.ccu_phys_start = CCU_BASE_ADDRESS;
	ccu.ccu_phys_size  = 0x1000;

	ccu.ccu_virt_start = ioremap_nocache(ccu.ccu_phys_start, ccu.ccu_phys_size);
	csi.csi_virt_start = ioremap_nocache(csi.csi_phys_start, csi.csi_phys_size);

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


        /*struct cci_tx_mode tx_mode;
>       bsp_csi_cci_init(sel);
>       tx_mode.tx_buf_mode.buf_src = FIFO;
>       tx_mode.tx_buf_mode.pkt_mode = COMPACT;
>       tx_mode.tx_buf_mode.pkt_cnt = 1;
>       tx_mode.tx_trig_mode.trig_src = NO_TRIG;
>       tx_mode.tx_trig_mode.trig_con = TRIG_DEFAULT;
>       tx_mode.tx_trig_line_cnt = 0;
>       bsp_cci_set_tx_mode(sel, &tx_mode);
>       bsp_cci_int_clear_status(sel, CCI_INT_ALL);
>       bsp_cci_int_enable(sel, CCI_INT_ALL);
*/
	/* Enable The Camera Device */
        struct csi0_en_reg ceg = {0};
	ceg.csi_en			   = 1;
	ceg.ver_en			   = 1;
	__csi_write32(CSI0_EN_REG, ceg.val);
	printk("CSI EN: %x\n", __csi_read32(CSI0_EN_REG));


        /* struct cci_cfg_reg cci_reg = {0};
        cci_reg.timeout_h = 0x10;
        cci_reg.interval = 0;
        cci_reg.packet_mode = 0;
        cci_reg.trig_mode = 2;
        cci_reg.csi_trig = 0;
        __csi_write32(CCI_CFG, cci_reg.val);*/

        struct cci_ctrl_reg cci_reg2 = {0};
        cci_reg2.cci_en = 1;
        __csi_write32(CCI_CTRL, cci_reg2.val);
	
        printk("CCI_CTRL: %x\n", __csi_read32(CCI_CTRL));

        dump_all_registers();
        //csi_set_fmt();
        //csi_int_enable();
	csi_capture_start();

	for (;;) {
                csi_int_status();
	}

	return 0;
}


/* buffer only works for ch0 right now */
void
csi_set_buffer_addr(uint32_t buf_num, uint32_t addr)
{
	printk("GOT HERE\n");
        switch(buf_num){
                case 0:
                        __csi_write32(CSI0_C0_F0_BUFA_REG, addr >> ADDR_BIT_R_SHIFT);
                        break;
                case 1:
                        __csi_write32(CSI0_C0_F1_BUFA_REG, addr >> ADDR_BIT_R_SHIFT);
                        break;
                case 2:
                        __csi_write32(CSI0_C0_F2_BUFA_REG, addr >> ADDR_BIT_R_SHIFT);
                        break;
                default:
                        printk("INVALID BUFFER NUM\n");
                        break;
        }
}

uint32_t
csi_get_buffer_address(uint32_t buf_num)
{
        switch(buf_num){
                case 0:
                {
	                uint32_t reg_val = __csi_read32(CSI0_C0_F0_BUFA_REG);
	                return reg_val << ADDR_BIT_R_SHIFT;
                }
                case 1:
                {
	                uint32_t reg_val = __csi_read32(CSI0_C0_F1_BUFA_REG);
	                return reg_val << ADDR_BIT_R_SHIFT;
                }
                case 2:
                {
	                uint32_t reg_val = __csi_read32(CSI0_C0_F2_BUFA_REG);
	                return reg_val << ADDR_BIT_R_SHIFT;
                }
                default:
                        printk("INVALID BUFFER NUM\n");
                        break;
        }

        return NULL;
}

void
csi_enable()
{
        struct csi0_en_reg ceg = {0};
	ceg.csi_en			   = 1;
        ceg.clk_cnt_en = 1;
        ceg.clk_cnt_spl = 0;
	__csi_write32(CSI0_EN_REG, ceg.val);
	printk("CSI EN: %x\n", __csi_read32(CSI0_EN_REG));
}

void
csi_disable()
{
        struct csi0_en_reg ceg = {0};
	ceg.csi_en			   = 0;
	__csi_write32(CSI0_EN_REG, ceg.val);
	printk("CSI EN: %x\n", __csi_read32(CSI0_EN_REG));
}


void
csi_set_fmt()
{
        struct csi0_c0_cfg_reg reg = {0};
        reg.output_fmt = 4; /* field-rgb565 */
        reg.input_fmt = 0; /* shoot raw */

        __csi_write32(CSI0_C0_CFG_REG, reg.val);
}

void
csi_int_enable()
{
        struct csi0_c0_int_en_reg reg = {0};
        reg.cd_int_en = 1;
        reg.fd_int_en = 1;
	reg.fifo0_of_int_en = 1;
        reg.fifo1_of_int_en = 1;
        reg.fifo2_of_int_en = 1;
        reg.mul_err_int_en = 1;
        reg.hb_of_int_en = 1;
        reg.vs_int_en = 1;
        __csi_write32(CSI0_C0_INT_EN_REG, reg.val);

        printk("Enabled CSI Interrupts\n");
}

void
csi_int_status()
{
        struct csi0_c0_frm_clk_cnt_reg reg6 = {0};
        reg6.val = __csi_read32(CSI0_C0_FRM_CLK_CNT_REG);
        printk("FRAME RATE %x\n", reg6.frm_clk_cnt);
        
        struct csi0_c0_acc_itnl_clk_cnt_reg reg5 = {0};
        reg5.val = __csi_read32(CSI0_C0_ACC_ITNL_CLK_CNT_REG);
        printk("ACC CLK CNT %x\n", reg5.acc_clk_cnt);
        printk("ITNL CLK CNT %x\n", reg5.itnl_clk_cnt);
        
        struct csi0_c0_pclk_stat_reg reg4 = {0};
        reg4.val = __csi_read32(CSI0_C0_PCLK_STAT_REG);
        printk("PCLK LINE MAX %x\n", reg4.pclk_cnt_line_max);
        printk("PCLK LINE MIN %x\n", reg4.pclk_cnt_line_min);
        
        struct csi0_c0_fifo_stat_reg reg3 = {0};
        reg3.val = __csi_read32(CSI0_C0_FIFO_STAT_REG);
        printk("FIFO MAX DEPTH %x\n", reg3.fifo_frm_max);

        struct csi0_c0_cap_sta_reg reg2 = {0};
        reg2.val = __csi_read32(CSI0_C0_CAP_STA_REG);
        printk("CAPTURE IN PROG %x\n", reg2.vcap_sta);
        printk("FIELD STATUS %x\n", reg2.field_sta);
        
        struct csi0_c0_int_sta_reg reg = {0};
        reg.val = __csi_read32(CSI0_C0_INT_STA_REG);
        printk("REG VAL: %x", reg.val);
      
        if(reg.cd_pd){
                printk("Capture Done %x\n", reg.cd_pd);
        }
        if(reg.fd_pd){
                printk("Frame Done %x\n", reg.fd_pd);
        }
        if(reg.fifo0_of_pd){
	        printk("FIFO 0 Overflow %x\n", reg.fifo0_of_pd);
        }
        if(reg.fifo1_of_pd){
	        printk("FIFO 1 Overflow %x\n", reg.fifo1_of_pd);
        }
        if(reg.fifo2_of_pd){
                printk("FIFO 2 Overflow %x\n", reg.fifo2_of_pd);
        }
        if(reg.mul_err_pd){
                printk("Multi Channel Writing Error %x\n", reg.mul_err_pd);
        }
        if(reg.hb_of_pd){
                printk("Hblank FIFI overflow %x\n", reg.hb_of_pd);
        }
        if(reg.vs_pd){
                printk("Vsync Error %x\n",reg.vs_pd);
        }
}

void
csi_status()
{
        struct csi0_c0_cap_sta_reg reg = {0};
        reg.val = __csi_read32(CSI0_C0_CAP_STA_REG);

        printk("vcap_STA %x\n", reg.vcap_sta);
}

paddr_t
calculate_dma_addr(paddr_t addr){

        return addr - HW_DMA_BEGIN;
}


void
csi_bus_setup(){
        struct csi0_if_cfg_reg reg = {0};

        reg.val = __csi_read32(CSI0_IF_CFG_REG);

        reg.csi_if = 0;
	reg.if_data_width = 0;
	reg.seq_8plus2 = 0;
        reg.clk_pol = 0;
	reg.herf_pol = 0;
	reg.verf_pol = 1;
	reg.field = 0;
	reg.fps_ds = 1;
	reg.src_type = 0;

        __csi_write32(CSI0_IF_CFG_REG, reg.val);
}

/* capture */
void
csi_capture_start()
{
        /* Camera restart */
        csi_enable();
        csi_disable();
        csi_enable();

        
        /* TODO set DMA addr for all three buffers */
        dma.fifo_size = (PAGE_SIZE * 5);

        dma.fifo0_phys_start = CSI_BUF_BEGIN;
        dma.fifo1_phys_start = CSI_BUF_BEGIN + (PAGE_SIZE * 5); 
        dma.fifo2_phys_start = CSI_BUF_BEGIN + (PAGE_SIZE * 10); 
        
        dma.fifo0_dma_start = calculate_dma_addr(dma.fifo0_phys_start); 
        dma.fifo1_dma_start = calculate_dma_addr(dma.fifo1_phys_start);
        dma.fifo2_dma_start = calculate_dma_addr(dma.fifo2_phys_start);
        
        dma.fifo0_virt_start = ioremap_nocache(dma.fifo0_phys_start, dma.fifo_size);
        dma.fifo1_virt_start = ioremap_nocache(dma.fifo1_phys_start, dma.fifo_size);
        dma.fifo2_virt_start = ioremap_nocache(dma.fifo2_phys_start, dma.fifo_size);
       
        csi_set_buffer_addr(0, dma.fifo0_dma_start);
        csi_set_buffer_addr(1, dma.fifo1_dma_start);
        csi_set_buffer_addr(2, dma.fifo2_dma_start);
        
	printk("fifo0 base: vaddr=%p\n", dma.fifo0_virt_start);
	printk("fifo0 base: paddr=%p\n", virt_to_phys(dma.fifo0_virt_start));
	printk("fifo0 base: dma_addr=%p\n", calculate_dma_addr(dma.fifo0_phys_start));
        
	printk("fifo1 base: vaddr=%p\n", dma.fifo1_virt_start);
	printk("fifo1 base: paddr=%p\n", virt_to_phys(dma.fifo1_virt_start));
	printk("fifo1 base: dma_addr=%p\n", calculate_dma_addr(dma.fifo1_phys_start));
        
	printk("fifo2 base: vaddr=%p\n", dma.fifo2_virt_start);
	printk("fifo2 base: paddr=%p\n", virt_to_phys(dma.fifo2_virt_start));
	printk("fifo2 base: dma_addr=%p\n", calculate_dma_addr(dma.fifo2_phys_start));


	printk("fifo0 base: dma_addr=%p\n", csi_get_buffer_address(0));
	printk("fifo1 base: dma_addr=%p\n", csi_get_buffer_address(1));
	printk("fifo2 base: dma_addr=%p\n", csi_get_buffer_address(2));

        /* Setup Bus */
        csi_bus_setup();
        /* Setup format */
        csi_set_fmt();
        /* Enable interrupts */
        __csi_write32(CSI0_C0_INT_STA_REG, 0xFF);
        csi_int_enable();
        /* Starting Capture */
	printk("STARTING CAPTURE\n");
	struct csi0_cap_reg reg = {0};
	reg.ch0_vcap_on			= 1;
	__csi_write32(CSI0_CAP_REG, reg.val);
}

void
csi_capture_stop()
{
	struct csi0_cap_reg reg = {0};
	reg.ch0_vcap_on			= 0;
	__csi_write32(CSI0_CAP_REG, reg.val);
}


/* dump all register vals */
int
dump_all_registers()
{
	uint32_t reg;
	reg = __csi_read32(CSI0_VER_REG);
	printk("VERSION REGISTER %x\n", reg);
}

DRIVER_INIT("late", camera_init);
