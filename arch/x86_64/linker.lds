/**
 * @file arch/x86_64/linker.lds
 * @brief Linker for x86_64 target
 * 
 * @copyright
 * This file is part of HotaruOS and is released under the terms
 * of the MIT License - See LICENSE.md
 * Copyright (c) 2024 NeonLightions
 */

OUTPUT_FORMAT(elf64-x86-64)
ENTRY(_start)

PHDRS
{
    requests    PT_LOAD;
    text        PT_LOAD;
    rodata      PT_LOAD;
    data        PT_LOAD;
}

SECTIONS
{
    .text.boot : {
        *(.text.boot)
    } :text

    . = 0xffffffff80000000;

    .requests : {
        requests_start_marker = .;
        KEEP(*(.requests_start_marker))

        KEEP(*(.requests))

        requests_end_marker = .;
        KEEP(*(.requests_end_marker))
    } :requests

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .text : {
        *(.text .text.*)
    } :text

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .rodata : {
        *(.rodata .rodata.*)
    } :rodata

    . = ALIGN(CONSTANT(MAXPAGESIZE));

    .data : {
        *(.data .data.*)
    } :data

    .bss : {
        *(.bss .bss.*)
        *(COMMON)
    } :data

    /DISCARD/ : {
        *(.eh_frame*)
        *(.note .note.*)
    }
}