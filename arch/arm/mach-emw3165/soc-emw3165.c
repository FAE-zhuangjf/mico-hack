/*
 *  Setup code for EMW3162 SoC with Device Tree support
 *
 *  Copyright (C) 2015 Jinfeng Zhuang <zhuangjf@mxchip.com>
 *
 *  All Rights Reserved
 */

#include <mico/init.h>
#include <mico/sdt/sdt.h>

#include <asm/mach/arch.h>

#include <types.h>

static void emw3165_mach_init(void)
{
	sdt_platform_populate(NULL);
}

DT_MACHINE_START(EMW3165)
	.init_machine = emw3165_mach_init,
MACHINE_END

