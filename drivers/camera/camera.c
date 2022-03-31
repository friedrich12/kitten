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

}

DRIVER_INIT("late", camera_init);
