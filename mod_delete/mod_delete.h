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

#ifndef MOD_DEL_H
#define MOD_DEL_H

#define MAX_TARGET_NAME_LENGTH  (256)
#define TARGET_MOD              ("avic_test")

#define MOD_DEL_DBG

#ifdef MOD_DEL_DBG

#define MOD_DEL_INFO(fmt, ...) \
    pr_info("[%s][%d]: "fmt, __func__, __LINE__, ##__VA_ARGS__)

#define MOD_DEL_ERR(fmt, ...) \
    pr_err("[%s][%d]: "fmt, __func__, __LINE__, ##__VA_ARGS__)

#else 

#define MOD_DEL_INFO(fmt, ...)
#define MOD_DEL_ERR(fmt, ...)

#endif

#endif
