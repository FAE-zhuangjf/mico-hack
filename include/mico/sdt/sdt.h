/*
 * Created by zhuangjf, 2015/4/4
 * All Rights Reserved
 */

#ifndef _MICO_SDT_H_
#define _MICO_SDT_H_

#include <mico/sdt/sdt.h>

#include <types.h>

enum
{
	SDT_NODE_TYPE_CPU = 0,
	SDT_NODE_TYPE_SERIAL,
	SDT_NODE_TYPE_GPIO,
	SDT_NODE_TYPE_SPI,
	SDT_NODE_TYPE_I2C,
};

typedef struct
{
	uint8_t type;
	char compatible[16];
	uint32_t reg_start;
	uint16_t reg_size;
	uint16_t interrupt;
} sdt_node_t;

struct device_node
{
    const char *name;
};

void sdt_platform_populate(struct device_node *root);

#endif
