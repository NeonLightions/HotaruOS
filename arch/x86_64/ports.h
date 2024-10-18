#pragma once

#include <stdint.h>

/** Only need size_t */
#define __need_size_t
#include <stddef.h>

static inline uint8_t inb(uint16_t __port)
{
    uint8_t _ret;
    asm volatile ("inb %1, %0" : "=a"(_ret) : "dN"(__port));
    return _ret;
}

static inline uint16_t inw(uint16_t __port)
{
    uint16_t _ret;
    asm volatile ("inw %1, %0" : "=a"(_ret) : "dN"(__port));
    return _ret;
}

static inline uint32_t inl(uint16_t __port)
{
    uint32_t _ret;
    asm volatile ("inl %1, %0" : "=a"(_ret) : "dN"(__port));
    return _ret;
}

static inline void insl(uint16_t __port, void *__addr, size_t __cnt)
{
    asm volatile ("rep insl"
                    : "+D"(__addr), "+c"(__cnt)
                    : "dN"(__port)
                );
}


static inline void outb(uint16_t __port, uint8_t __value)
{
    asm volatile ("outb %0, %1" : : "a"(__value), "dN"(__port));
}

static inline void outw(uint16_t __port, uint16_t __value)
{
    asm volatile ("outw %0, %1" : : "a"(__value), "dN"(__port));
}

static inline void outl(uint16_t __port, uint32_t __value)
{
    asm volatile ("outl %0, %1" : : "a"(__value), "dN"(__port));
}

static inline void outsl(uint16_t __port, const void *__addr, size_t __cnt)
{
    asm volatile ("rep outsl"
                    : "+S"(__addr), "+c"(__cnt)
                    : "dN"(__port)
                );
}