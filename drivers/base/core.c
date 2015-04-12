/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#include <mico/device.h>

int device_add(struct device *dev)
{
#ifdef SYSFS
	device_create_file(dev, &dev_attr_uevent);
#endif

	bus_add_device(dev);
	
	bus_probe_device(dev);
}

