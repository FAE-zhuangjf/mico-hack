/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#include <mico/sdt/sdt.h>
#include <mico/init.h>
#include <mico/device.h>

#include <types.h>

__root const sdt_node_t g_sdt_node[] __sdt =
{
	{SDT_NODE_TYPE_SERIAL, "usart1", 0, 0, 0},
    {SDT_NODE_TYPE_SERIAL, "usart6", 0, 0, 0},
    {SDT_NODE_TYPE_SERIAL, "spi1", 0, 0, 0},
    {SDT_NODE_TYPE_SERIAL, "GPIOA", 0, 0, 0},
};

extern struct bus_type platform_bus_type;

void sdt_platform_bus_create(struct device_node *dev)
{
    struct device *device;

    device = (struct device*)malloc(sizeof(struct device));

    memset(device, 0, sizeof(struct device));

    device->bus = &platform_bus_type;

    strcpy(device->init_name, dev->name);
    
    device_add(device);
}

/* we create device by virtual-platform-bus, as all ARM SoC devices are memory-maped IOs 
 * we assume that the SDT is size limited and end with NULL !
 */
void sdt_platform_populate(struct device_node *root)
{
    struct device_node *child;
    
    for(child = root; child != NULL; child++) {
        sdt_platform_bus_create(child);
    }
}

struct machine_desc * sdt_match_machine(uint32_t dt_addr)
{
    return NULL;
}

