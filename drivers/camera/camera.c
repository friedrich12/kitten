/* 
 * 2022, Friedrich Doku <frd20@pitt.edu>
 */

#include "camera.h"

static inline uint32_t 
__csi_read32(uintptr_t offset)
{
        return readl(CSI_BASE_ADDRESS + offset);
}

static inline void
__csi_write32(uintptr_t offset, 
               uint32_t  value)
{
        writel(value, CSI_BASE_ADDRESS + offset);
}


int test_camera(){

}

int read_image_from_camera(){

}


// Configure Channel 0
int camera_init()
{
        /* Print version number */
        
        struct csi0_en_reg enable_register = {0};
        enable_register.val = __csi_read32(CSI0_EN_REG);

        printk("READING VERSION READ ENABLE REGISTER %d\n", enable_register.ver_en);

        enable_register.ver_en = 1;
        printk("WRITING VERSION READ ENABLE REGISTER\n");

        __csi_write32(CSI0_EN_REG, enable_register.val);



        struct csi0_ver_reg ver_reg = {0};
        ver_reg.val = __csi_read32(CSI0_VER_REG);
        printk("VERSION NUMBER %d", ver_reg.ver);

}

DRIVER_INIT("late", camera_init);
