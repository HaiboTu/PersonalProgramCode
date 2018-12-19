/**
 * Copyright (C) 2017 Tangram Technologies Incorporated.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are not permitted without the prior consent of Tangram
 * Technologies.
 *
 * Author: Haibo Tu
 * Email: haibo.tu@tangramtek.com
 * Data: 2018.01.01
 */

#include <linux/types.h>
#include <linux/memory.h>
#include <linux/mm.h>
#include <linux/slab.h>
#include <linux/module.h>
#include <linux/kernel.h>
#include <asm/msr.h>
#include <asm/local.h>
#include <linux/list.h>
#include <linux/cpumask.h>
#include <linux/uaccess.h>
#include "mod_delete.h"

#define MODULE_REF_BASE	1

static char target_name[MAX_TARGET_NAME_LENGTH] = {0x00};
static char *mod_name = &target_name[0]; 
module_param(mod_name, charp, S_IRUGO);

int __init mod_del_init(void)
{
    struct module *mod = NULL;
    int ret = 0x00;

    MOD_DEL_INFO("+");

    mod = find_module(mod_name);
    if (mod != NULL) {
        MOD_DEL_INFO("find module name %s.", mod_name);
        atomic_set(&mod->refcnt, MODULE_REF_BASE);
        mod->state = MODULE_STATE_LIVE;
    } else {
        MOD_DEL_INFO("cannot find mod name %s.", mod_name);
    }

    MOD_DEL_INFO("-");

    return ret;
}

void __exit mod_del_exit(void)
{
    MOD_DEL_INFO("+");
    memset(target_name, 0x00, MAX_TARGET_NAME_LENGTH);
    MOD_DEL_INFO("-");

    return;
}

MODULE_LICENSE("GPL");
module_init(mod_del_init);
module_exit(mod_del_exit);
