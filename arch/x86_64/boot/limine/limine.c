/**
 * @file arch/x86_64/boot/limine/limine.c
 * @brief Limine main loader
 * 
 * @copyright
 * This file is part of HotaruOS and is released under the terms
 * of the MIT License - See LICENSE.md
 * Copyright (c) 2024 NeonLightions
 */

#include "limine.h"
#include "../../util/printf.h"
#include "../../util/string.h"

#undef dprintf_prefix
#define dprintf_prefix "[LIMINE] "

extern struct limine_boot_params limine_params;

void 
limine_init(void)
{
    dprintf("Parsing Limine information...\n");

    dprintf("   * Bootloader info: %s (%s)\n", 
            limine_params.bootloader_info->response->name,
            limine_params.bootloader_info->response->version);
}