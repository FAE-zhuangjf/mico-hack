/*
 * arch/arm/include/asm/mach/arch.h
 *
 * Copyright (C) 2000 Russell King
 * Copyright (C) 2015 Jinfeng Zhuang
 *
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License version 2 as
 * published by the Free Software Foundation.
 */

#ifndef ASM_ARCH_H
#define ASM_ARCH_H

struct machine_desc {
	const char *name;

	void (*init_early)(void);
	void (*init_irq)(void);
	void (*init_time)(void);
	void (*init_machine)(void);
	void (*init_late)(void);
};

/*
 * Current machine - only accessible during boot.
 */
extern const struct machine_desc *machine_desc;

/*
 * Machine type table - also only accessible during boot
 */
extern const struct machine_desc __arch_info_begin[], __arch_info_end[];
#define for_each_machine_desc(p)			\
	for (p = __arch_info_begin; p < __arch_info_end; p++)

#define DT_MACHINE_START(_name)		\
__root static const struct machine_desc __mach_desc_##_name	\
__section__(.machine_desc) = {	\
	.name		= #_name,

#define MACHINE_END				\
};

#endif