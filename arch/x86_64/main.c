/**
 * @file arch/x86_64/main.c
 * @brief x86_64's core process
 * 
 * @copyright
 * This file is part of HotaruOS and is released under the terms
 * of the MIT License - See LICENSE.md
 * Copyright (c) 2024 NeonLightions
 */

#include <stddef.h>

#include "ports.h"
#include "util/printf.h"

extern void limine_init(void);

void (*_putchar)(char) = NULL;

/** */
static void _qemu_out(char __c)
{
    outb(0xe9, __c);
}

void _start(void)
{
    _putchar = _qemu_out;

    printf("Hello Wolrd!\n");

    limine_init();

    asm volatile (
        "1: jmp 1b"
    );
}