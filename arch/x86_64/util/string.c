/**
 * @file arch/x86_64/util/string.c
 * @brief common string utilities
 * 
 * @copyright
 * This file is part of HotaruOS and is released under the terms
 * of the MIT License - See LICENSE.md
 * Copyright (c) 2024 NeonLightions
 */

#include <stddef.h>

#include "string.h"


/**
 * @brief Copies the byte C into the first __CNT bytes pointed to by DST.
 * 
 * @return a copy of the pointer __DST.
 */
void *
memset(void * restrict __dst, unsigned char __c, size_t __cnt)
{
    unsigned char *_dst_copy = (unsigned char *) __dst;
    while (__cnt-- > 0)
        *_dst_copy++ = __c;
    return __dst;
}

/**
 * @brief Copies __CNT bytes from where SRC points to into where __DST points to.
 * Assumes no overlapping between these two regions.
 * 
 * @return a copy of the pointer __DST.
 */
void *
memcpy(void * restrict __dst, const void * restrict __src, size_t __cnt)
{
    unsigned char *_dst_copy = (unsigned char *) __dst;
    unsigned char *_src_copy = (unsigned char *) __src;
    while (__cnt-- > 0)
        *_dst_copy++ = *_src_copy++;
    return __dst;
}

/**
 * @brief Copies __CNT bytes from where __SRC points to into where __DST points to.
 * The copy is like relayed by an internal buffer, so it is OK if these
 * two memory regions overlap.
 * 
 * @return a copy of the pointer __DST.
 */
void *
memmove(void * restrict __dst, const void * restrict __src, size_t __cnt)
{
    unsigned long int _dstp = (long int) __dst;
    unsigned long int _srcp = (long int) __src;
    if (_dstp - _srcp >= __cnt)   /** Unsigned compare. */
        __dst = memcpy(__dst, __src, __cnt);
    else {  /** SRC region overlaps start of DST, do reversed order. */
        unsigned char *_dst_copy = ((unsigned char *) __dst) + __cnt;
        unsigned char *_src_copy = ((unsigned char *) __src) + __cnt;
        while (__cnt-- > 0)
            *_dst_copy-- = *_src_copy--;
    }
    return __dst;
}

/**
 * @brief Compare two memory regions byte-wise. Returns zero if they are equal.
 * 
 * @return <0 if the first unequal byte has a lower unsigned value in
 * PTR1, and >0 if higher.
 */
int
memcmp(const void * restrict __ptr1, const void * restrict __ptr2, size_t __cnt)
{
    const char *_ptr1_cast = (const char *) __ptr1;
    const char *_ptr2_cast = (const char *) __ptr2;
    char _b1 = 0, _b2 = 0;
    while (__cnt-- > 0) {
        _b1 = *_ptr1_cast++;
        _b2 = *_ptr2_cast++;
        if (_b1 != _b2)
            return ((int) _b1) - ((int) _b2);
    }
    return ((int) _b1) - ((int) _b2);
}


/** @return Length of the string (excluding the terminating '\0'). */
size_t
strlen(const char *__str)
{
    size_t _len = 0;
    while (__str[_len])
        _len++;
    return _len;
}


/**
 * @return Length of the string (excluding the terminating '\0').
 * If string STR does not terminate before reaching __cnt chars, returns
 * __cnt.
 */
size_t
strnlen(const char *__str, size_t __cnt)
{
    size_t _len = 0;
    while (__str[_len] && __cnt > 0) {
        _len++;
        __cnt--;
    }
    return _len;
}

/**
 * @brief Compare two strings 
 * 
 * @return less than, equal to or greater than zero
 * if STR1 is lexicographically less than, equal to or greater than S2.
 * 
 * @note Limited to upto __cnt chars.
 */
int
strncmp(const char *__str1, const char *__str2, size_t __cnt)
{
    char _c1 = '\0', _c2 = '\0';
    while (__cnt-- > 0) {
        _c1 = *__str1++;
        _c2 = *__str2++;
        if (_c1 == '\0' || _c1 != _c2)
            return ((int) _c1) - ((int) _c2);
    }
    return ((int) _c1) - ((int) _c2);
}

/**
 * @brief Copy string SRC to DST. Assume DST is large enough.
 * Adds implicit null terminator even if __cnt is smaller 
 * than actual length of SRC.
 * 
 * @return a copy of pointer __DST
 * 
 * @note Limited to upto __cnt chars.
 */
char *
strncpy(char *__dst, const char *__src, size_t __cnt)
{
    size_t _size = strnlen(__src, __cnt);
    if (_size != __cnt)
        memset(__dst + _size, '\0', __cnt - _size);
    __dst[_size] = '\0';
    return memcpy(__dst, __src, _size);
}

/**
 * @brief Concatenate string DST with SRC. Assume DST is large enough.
 * 
 * @return Returns a copy of the pointer DST.
 * 
 * @note Limited to upto __cnt chars.
 */
char *
strncat(char *__dst, const char *__src, size_t __cnt)
{
    char *_s = __dst;
    __dst += strlen(__dst);
    size_t _size = strnlen(__src, __cnt);
    __dst[_size] = '\0';
    memcpy(__dst, __src, _size);
    return _s;
}