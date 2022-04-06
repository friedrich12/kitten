/* 
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */

#include "camera.h"


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

static struct csi csi;
static struct ccu ccu;

static inline uint32_t 
__csiX_read32(uintptr_t offset)
{
	printk("reading from: vaddr=0x%016lx\n", csi.csi_virt_start + offset);
        return readl(csi.csi_virt_start + offset);
}

static inline void
__csiX_write32(uintptr_t offset, 
               uint32_t  value)
{
        printk("Writing %x\n", value);
	printk("writing to: vaddr=0x%016lx\n", csi.csi_virt_start + offset);
        writel(value, csi.csi_virt_start + offset);
}

#define __csi_read32(offset)         *((uint32_t *) (csi.csi_virt_start + offset))
#define __csi_write32(offset, value) *((uint32_t *) (csi.csi_virt_start + offset)) = value 

#define __ccu_read32(offset)         *((uint32_t *) (ccu.ccu_virt_start + offset))
#define __ccu_write32(offset, value) *((uint32_t *) (ccu.ccu_virt_start + offset)) = value 

int test_camera(){

}

int read_image_from_camera(){

}

#define PWDN SUNXI_GPE(15)
#define RESET SUNXI_GPE(14)

int camera_power_on(){

        printk("CAMERA POWER ON\n");
        /* Set gpios to poewr on*/
        /* Power on reset */
        sunxi_gpio_set_cfgpin(PWDN, SUNXI_GPIO_OUTPUT);  /* Set the gpio to output */
        sunxi_gpio_set_cfgpin(RESET, SUNXI_GPIO_OUTPUT); /* Set the gpio to output */
        /* power down io */
        sunxi_gpio_output(PWDN, CSI_STBY_ON);
        /* Reset on io */
        sunxi_gpio_output(RESET, CSI_RST_ON);
        /* power on reset */
        sunxi_gpio_output(PWDN, CSI_STBY_OFF);
        int N = 12000; while(N--);
        sunxi_gpio_output(RESET, CSI_RST_OFF);
        int B = 12000; while(B--);

        printk("CAMERA POWER ON DONE\n");
}

int camera_init()
{
	uint32_t reg=0;

	csi.csi_phys_start = CSI_BASE_ADDRESS;
        csi.csi_phys_size = 0x4000;

        ccu.ccu_phys_start = CCU_BASE_ADDRESS;
        ccu.ccu_phys_size = 0x1000;
	
        ccu.ccu_virt_start = ioremap_nocache(ccu.ccu_phys_start, ccu.ccu_phys_size);
	csi.csi_virt_start = ioremap_nocache(csi.csi_phys_start, csi.csi_phys_size);

	printk("csi base: vaddr=%p\n", csi.csi_virt_start);
	printk("csi base: paddr=%p\n", virt_to_phys(csi.csi_virt_start));
	
        printk("ccu base: vaddr=%p\n", ccu.ccu_virt_start);
	printk("ccu base: paddr=%p\n", virt_to_phys(ccu.ccu_virt_start));
	
        reg = __ccu_read32(PLL_PERIPH0_CTRL_REG);
	__ccu_write32(PLL_PERIPH0_CTRL_REG, reg| 1<<18|1<<24);
	printk("PLL PER0: %x\n", __ccu_read32(PLL_PERIPH0_CTRL_REG));

	reg = __ccu_read32(PLL_PERIPH1_CTRL_REG);
	__ccu_write32(PLL_PERIPH1_CTRL_REG, reg| 1<<18|1<<24);
	printk("PLL PER1: %x\n", __ccu_read32(PLL_PERIPH1_CTRL_REG));

	__ccu_write32(BUS_CLK_GATING_REG1, 1<<8);
	printk("CSI BUS CTRL: %x\n", __ccu_read32(BUS_CLK_GATING_REG1));

	__ccu_write32(BUS_SOFT_RST_REG1, 0xffffffff);
	__ccu_write32(CSI_MISC_CLK_REG, 1<<31);
	printk("CSI MISC: %x\n", __ccu_read32(CSI_MISC_CLK_REG));

	__ccu_write32(CSI_CLK_REG, (1<<31|1<<15 | 1<<9));
        printk("CSI CLK: %x\n", __ccu_read32(CSI_CLK_REG));

        /* Enable The Camera Device */
        struct csi0_en_reg ceg = {0};
        ceg.csi_en = 1;
        ceg.ver_en = 1;
	__csi_write32(CSI0_EN_REG, ceg.val);
	printk("CSI EN: %x\n", __csi_read32(CSI0_EN_REG));

	__csi_write32(CCI_CTRL, 0x01);
	printk("CCI_CTRL: %x\n", __csi_read32(CCI_CTRL));

        dump_all_registers();

	return 0;
}



int dump_all_registers(){
        uint32_t reg;
        reg = __csi_read32(CSI0_VER_REG);
        printk("VERSION REGISTER %x\n", reg); 

}
DRIVER_INIT("late", camera_init);
