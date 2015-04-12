/*
 * Copyright (C) Jinfeng Zhuang 2015-4
 * All Rights Reserved
 */

#include <mico/debug.h>

#include <types.h>

extern struct machine_desc * sdt_match_machine(uint32_t dt_addr);

struct machine_desc * setup_machine_sdt(uint32_t dt_addr)
{
    struct machine_desc *mdesc_best = NULL;

    if(NULL == dt_addr) {
        return NULL;
    }

    mdesc_best = sdt_match_machine(dt_addr);
    if(!mdesc_best) {
        DEBUG("\nUnsupported Device Tree\n");

        while(1);
    }

    return mdesc_best;
}

