/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#include <mico/device.h>

#include <types.h>

static void driver_bound(struct device *dev)
{
    if(klist_node_attached(&dev->p->knode_driver)) {
        return;
    }

    klist_add_tail(&dev->p->knode_driver, &dev->driver->p->klist_devices);
}

int device_bind_driver(struct device *dev)
{
#if 0
	int ret;

	ret = driver_sysfs_add(dev);
	if (!ret)
		driver_bound(dev);
	return ret;
#else
    driver_bound(dev);

    return 0;
#endif
}

static int really_probe(struct device *dev, struct device_driver *drv)
{
    int ret = 0;

    dev->driver = drv;

    if(dev->bus->probe) {
        ret = dev->bus->probe(dev);
        if(ret) {
            goto probe_failed;
        }
    } else if(drv->probe) {
        ret = drv->probe(dev);
        if(ret) {
            goto probe_failed;
        }
    } else {
        /* none */
    }

    driver_bound(dev);

    ret = 1;

    goto done;

probe_failed:
    dev->driver = NULL;

done:

    return ret;
}

static int __device_attach(struct device_driver *drv, void *data)
{
    struct device *dev = data;

    if(!driver_match_device(drv, dev)) {
        return 0;
    }

    return driver_probe_device(drv, dev);
}

int driver_probe_device(struct device_driver *drv, struct device *dev)
{
    int ret = 0;

    ret = really_probe(dev, drv);

    return ret;
}

/**
 * device_attach - try to attach device to a driver.
 * @dev: device.
 *
 * Walk the list of drivers that the bus has and call
 * driver_probe_device() for each pair. If a compatible
 * pair is found, break out and return.
 *
 * Returns 1 if the device was bound to a driver;
 * 0 if no matching driver was found;
 * -ENODEV if the device is not registered.
 *
 * When called for a USB interface, @dev->parent lock must be held.
 */

int device_attach(struct device *dev)
{
    int ret;

#ifdef OS_SUPPORT
    device_lock(dev);
#endif

    /* hot-plugin devices enter this logic */
    if(dev->driver) {
        if(klist_node_attached(&dev->p->knode_driver)) {
            ret = 1;
            goto out_unlock;
        }
        ret = device_bind_driver(dev);
        if(0 == ret) {
            ret = 1;
        } else {
            dev->driver = NULL;
            ret = 0;
        }
    } else {    /* common way to add device in initial process */
        ret = bus_for_each_drv(dev->bus, NULL, dev, __device_attach);
    }

out_unlock:

#ifdef OS_SUPPORT
    device_unlock(dev);
#endif

    return ret;
}

