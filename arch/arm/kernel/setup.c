/*
 * Created by zhuangjf, 2015/4/4
 * All Rights Reserved
 */

#include <mico/init.h>

#include <asm/mach/arch.h>

#include <types.h>

extern struct machine_desc * setup_machine_sdt(uint32_t dt_addr);

/*
 * init machine early, which not based on kernel device model or device tree
 * purely based on ARCH-specified functions
 */
void setup_arch(void)
{
	const struct machine_desc *mdesc;

    mdesc = setup_machine_sdt(0x08004000);

    if(mdesc->init_early) {
        mdesc->init_early();
    }

    /* NVIC & Systick */
    if(mdesc->init_irq) {
        mdesc->init_irq();
    }

    /* RTC */
    if(mdesc->init_time) {
        mdesc->init_time();
    }
}

