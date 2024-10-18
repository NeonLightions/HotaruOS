/**
 * @file arch/x86_64/util/string.c
 * @brief common string utilities
 * 
 * @copyright
 * This file is part of HotaruOS and is released under the terms
 * of the MIT License - See LICENSE.md
 * Copyright (c) 2024 NeonLightions
 */

#pragma once

#include <stddef.h>


/** These four MUST be present, as required by GCC. */
void *memset(void * restrict __dst, unsigned char __c, size_t __cnt);
void *memcpy(void * restrict __dst, const void * restrict __src, size_t __cnt);
void *memmove(void * restrict __dst, const void * restrict __src, size_t __cnt);
int memcmp(const void * restrict __ptr1, const void * restrict __ptr2, size_t __cnt);

size_t strlen(const char *__str);

size_t strnlen(const char *__str, size_t __cnt);
int strncmp(const char *__str1, const char *__str2, size_t __cnt);
char *strncpy(char *__dst, const char *__src, size_t __cnt);
char *strncat(char *__dst, const char *__src, size_t __cnt);
