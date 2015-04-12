/*
 * Copyright (c) 2015-4 Jinfeng Zhuang
 *
 * All Rights Reserved
 */

#include <mico/wlan.h>
#include <mico/rtos.h>
#include <mico/init.h>

#include <types.h>

#include <string.h>

void kernel_device_model_init(void)
{

}

/* initcalls has been declared in .initcallx.init sections, as I can't get the address by
 * __section_begin and __section_end, so here adopt another method, which go througth from
 * the fixed address until we reached a uint32_t value equals to NULL
 */
#if 0
static int do_one_initcall(initcall_t fn)
{
    int ret;

    ret = fn();

    return ret;
}

static void do_initcall_level(uint32_t start, uint32_t end)
{
    uint32_t fn_addr;

    for(fn_addr = start; fn_addr < end; fn_addr++) {
        do_one_initcall((initcall_t)fn_addr);
    }
}

void do_initcalls(void)
{
    int level;

    char section_name[16];
    uint32_t section_start, section_end;

    for(level = 0; level < 7; level++) {
        snprintf(section_name, 16, ".initcall%d.init", level);
        section_start = (uint32_t)__section_begin(".init.text");
        section_end = __section_end(section_name);

        do_initcall_level(section_start, section_end);
    }
}
#else
void do_initcalls(void)
{
    initcall_t fn;
    uint32_t address = (uint32_t)0x0800D000;    /* refer to IAR .icf file*/

    fn = (initcall_t)address;

    while(NULL != fn) {
        fn();
    }
}
#endif

/*
 * Ok, the machine is now initialized. None of the devices
 * have been touched yet, but the CPU subsystem is up and
 * running, and memory and process management works.
 *
 * Now we can finally start doing some real work..
 */
static void do_basic_setup(void)
{
    /* just init the kernel device model framework, not the real thing */
    kernel_device_model_init();

    /* call initcallx functions which be declared by 'arch_initcall' & 'module_init'
        * 'arch_initcall' do init_machine, which populate the platform devices to kernel
        * device model.
        * 'module_init' register the drivers to device model.
        * So the register sequence is device -> drivers
        */
    do_initcalls();
}

void init_architecture(void)
{
	setup_arch();

    /* init devices & drivers may take a long time, the initial process should be done in a
        * seperate thread. Linux does it in 'kernel_init' thread
        */

    do_basic_setup();
}

void init_platform(void)
{
	/* enable 802.11 device in reset mode */

	/* power save config */
}

int mico_platform_init(void)
{
    return 0;
}


/* power save in IDLE mode */
uint32_t platform_power_down_hook(uint32_t delay_ms)
{
	int ret = 0;

    /* __asm("wfi"); */

	return ret;
}

int application_start(void)
{
	mico_wlan_init();

	while(1)
	{
        sleep(1);
	}
}

