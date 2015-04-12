/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#ifndef _MICO_DEVICE_H
#define _MICO_DEVICE_H

#include <base/base.h>

struct device;
struct device_driver;

struct bus_type
{
    const char *name;
    struct device *dev_root;

    int (*match)(struct device *dev, struct device_driver *drv);
    int (*probe)(struct device *dev);
    int (*remove)(struct device *dev);
    int (*shutdown)(struct device *dev);

    struct subsys_private *p;
};

struct device_driver
{
    const char *name;
    struct bus_type *bus;

    int (*probe)(struct device *dev);
    int (*remove)(struct device *dev);
    int (*shutdown)(struct device *dev);
    int (*suspend)(struct device *dev);

    struct driver_private *p;
};

struct device
{
    struct device *parent;

    struct device_private *p;

    const char *init_name;
    
	struct bus_type *bus;
    struct device_driver *driver;
};

#endif
