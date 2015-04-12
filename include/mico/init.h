#ifndef MICO_INIT_H
#define MICO_INIT_H

#include <mico/compiler.h>

#define __sdt			__section(.sdt)
#define __initdata		__section(.init.data)

#define __section__(S)		__section(S)

/*
 * Used for initialization calls..
 */
typedef int (*initcall_t)(void);
typedef void (*exitcall_t)(void);

/* initcalls are now grouped by functionality into separate 
 * subsections. Ordering inside the subsections is determined
 * by link order. 
 * For backwards compatibility, initcall() puts the call in 
 * the device init subsection.
 *
 * The `id' arg to __define_initcall() is needed so that multiple initcalls
 * can point at the same handler without causing duplicate-symbol build errors.
 */
 
#define __define_initcall(fn, id) \
	__root static initcall_t  __initcall_##fn##id  \
	__section__(.initcall##id.init) = fn;

/*
 * Early initcalls run before initializing SMP.
 *
 * Only for built-in code, not modules.
 */
#define early_initcall(fn)		__define_initcall(fn, early)

/*
 * A "pure" initcall has no dependencies on anything else, and purely
 * initializes variables that couldn't be statically initialized.
 *
 * This only exists for built-in code, not for modules.
 * Keep main.c:initcall_level_names[] in sync.
 */
#define pure_initcall(fn)		__define_initcall(fn, 0)

#define core_initcall(fn)		__define_initcall(fn, 1)
#define postcore_initcall(fn)		__define_initcall(fn, 2)
#define arch_initcall(fn)		__define_initcall(fn, 3)
#define subsys_initcall(fn)		__define_initcall(fn, 4)
#define fs_initcall(fn)			__define_initcall(fn, 5)
#define rootfs_initcall(fn)		__define_initcall(fn, rootfs)
#define device_initcall(fn)		__define_initcall(fn, 6)
#define late_initcall(fn)		__define_initcall(fn, 7)

#define __initcall(fn) device_initcall(fn)

#define module_init(x)	__initcall(x);

#endif
