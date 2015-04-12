/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#ifndef _MICO_KERNEL_H_
#define _MICO_KERNEL_H_

#include <mico/compiler.h>

/**
 * container_of - cast a member of a structure out to the containing structure
 * @ptr:	the pointer to the member.
 * @type:	the type of the container struct this is embedded in.
 * @member:	the name of the member within the struct.
 *
 */
#ifdef __GNU_C__
#define container_of(ptr, type, member) ({			\
	const typeof( ((type *)0)->member ) *__mptr = (ptr);	\
	(type *)( (char *)__mptr - offsetof(type,member) );})
#else
#define container_of(ptr, type, member) (type*)((char*)ptr - offsetof(type,member))
#endif

#endif

