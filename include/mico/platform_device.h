/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#ifndef _MICO_PLATFORM_DRIVER_H_
#define _MICO_PLATFORM_DRIVER_H_

#include <mico/device.h>
#include <mico/kernel.h>

typedef int (*test_func_type)(struct platform_device *dev);

struct platform_driver
{
    //int (*probe)(struct platform_device *);
    test_func_type probe;
    int (*remove)(struct platform_device *);
    void (*shutdown)(struct platform_device *);

    struct device_driver driver;
};

struct platform_device
{
    const char *name;
    struct device dev;
};

#define to_platform_device(x)   container_of((x), struct platform_device, dev)
#define to_platform_driver(x)   container_of((x), struct platform_driver, driver)

void platform_device_register(struct platform_device *device);
void platform_driver_register(struct platform_driver *driver);

#endif
