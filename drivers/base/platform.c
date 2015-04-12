/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#include <mico/device.h>
#include <mico/platform_device.h>

struct device platform_bus =  {
    .init_name = "platform",
};

static int platform_match(struct device *dev, struct device_driver *drv)
{
    struct platform_device *pdev = to_platform_device(dev);
    struct platform_driver *pdrv = to_platform_driver(drv);
    
    return (strcmp(pdev->name, drv->name));
}

struct bus_type platform_bus_type = {
    .name = "platform",
    .match = platform_match,
};



