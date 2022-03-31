// Copyright (c) Friedrich 2022

#include "camera.h"

static vaddr_t SUNXI_PIO_BASE = 0;
spinlock_t lock;


int test_camera(){

}

int read_image_from_camera(){

}


// Configure Channel 0
int camera_init()
{

}

DRIVER_INIT("late", camera_init);
