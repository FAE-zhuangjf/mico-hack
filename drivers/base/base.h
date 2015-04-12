/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#ifndef _MICO_BASE_H_
#define _MICO_BASE_H_

#include <mico/device.h>
#include <mico/klist.h>

struct subsys_private
{
    struct klist klist_devices;
    struct klist klist_drivers;
    struct bus_type *bus;
};

struct device_private
{
    struct klist klist_children;
    struct klist_node knode_parent;
    struct klist_node knode_driver;
    struct klist_node knode_bus;
    void *driver_data;
    struct device *device;
};

struct driver_private
{
    struct klist klist_devices;
    struct klist_node knode_bus;
    struct device_driver *driver;
};

static inline int driver_match_device(struct device_driver *drv,
				      struct device *dev)
{
	//return (drv->bus->match) ? (drv->bus->match(dev, drv)) : 1;
}

#endif

