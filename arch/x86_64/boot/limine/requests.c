/**
 * @file arch/x86_64/boot/limine/requests.c
 * @brief limine requests
 * 
 * @copyright
 * This file is part of HotaruOS and is released under the terms
 * of the MIT License - See LICENSE.md
 * Copyright (c) 2024 NeonLightions
 */

#include "limine.h"
#include <stddef.h>

#define __limine_req __attribute__((used, section(".requests"))) static volatile

/**
 * Request Limine revision 2, Limine will fail
 * to boot when supported revision is lower than 2.
 */
__limine_req LIMINE_BASE_REVISION(2);


/** 
 * Every request will be between those tags.
 * This tag...
 */
__attribute__((used, section(".requests_start_marker")))
static volatile LIMINE_REQUESTS_START_MARKER;

__limine_req 
struct limine_bootloader_info_request 
bootloader_info = {
    .id = LIMINE_BOOTLOADER_INFO_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req
struct limine_firmware_type_request
firmware_type = {
    .id = LIMINE_FIRMWARE_TYPE_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req
struct limine_stack_size_request
stack_size = {
    .id = LIMINE_STACK_SIZE_REQUEST,
    .revision = 0,
    .stack_size = 16384, /** 16KiB */
    .response = NULL
};

__limine_req
struct limine_hhdm_request
hhdm = {
    .id = LIMINE_HHDM_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req
struct limine_framebuffer_request
framebuffer = {
    .id = LIMINE_FRAMEBUFFER_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req 
struct limine_paging_mode_request
paging_mode = {
    .id = LIMINE_PAGING_MODE_REQUEST,
    .revision = 0,
    .response = NULL,
    .mode = LIMINE_PAGING_MODE_X86_64_4LVL
    /** Just use 4-level paging, so no need
     *  for max_mode and min_mode
     */
};

__limine_req
struct limine_smp_request
smp = {
    .id = LIMINE_SMP_REQUEST,
    .revision = 0,
    .response = NULL,
    .flags = 0 /** X2APIC unsupported */
};

__limine_req 
struct limine_memmap_request
memmap = {
    .id = LIMINE_MEMMAP_REQUEST,
    .revision = 0,
    .response = NULL
};

extern void _start(void);

__limine_req
struct limine_entry_point_request
entry_point = {
    .id = LIMINE_ENTRY_POINT_REQUEST,
    .revision = 0,
    .response = NULL,
    .entry = _start
};

__limine_req
struct limine_kernel_file_request
kernel_file = {
    .id = LIMINE_KERNEL_FILE_REQUEST,
    .revision = 0,
    .response = NULL
};

/**
 * My goal is making HotaruOS mostly modularization,
 * users can optionally install or remove modules,
 * but there will be some "internal" modules that
 * are needed for the OS to operate normally. 
 * 
 * This feature has been removed from Limine since v8.0.0,
 * but I will keep hoping that it will be added again in
 * the future :D
 */
__limine_req
struct limine_module_request
modules = {
    .id = LIMINE_MODULE_REQUEST,
    .revision = 0,
    .response = NULL,

    /** Fields below are deprecated */
};

__limine_req
struct limine_rsdp_request
rsdp = {
    .id = LIMINE_RSDP_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req
struct limine_smbios_request
smbios = {
    .id = LIMINE_SMBIOS_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req
struct limine_efi_system_table_request
efi_system_table = {
    .id = LIMINE_EFI_SYSTEM_TABLE_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req
struct limine_efi_memmap_request
efi_memmap = {
    .id = LIMINE_EFI_MEMMAP_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req
struct limine_boot_time_request
boot_time = {
    .id = LIMINE_BOOT_TIME_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req
struct limine_kernel_address_request
kernel_address = {
    .id = LIMINE_KERNEL_ADDRESS_REQUEST,
    .revision = 0,
    .response = NULL
};

__limine_req
struct limine_dtb_request
dev_tree_blob = {
    .id = LIMINE_DTB_REQUEST,
    .revision = 0,
    .response = NULL
};

/**
 * ...and this tag.
 */
__attribute__((used, section(".requests_end_marker")))
static volatile LIMINE_REQUESTS_END_MARKER;

/** Boot params (just a collection of Limine requests) */
struct limine_boot_params limine_params = {
    .bootloader_info = &bootloader_info,
    .firmware_type = &firmware_type,
    .stack_size = &stack_size,
    .hhdm = &hhdm,
    .framebuffer = &framebuffer,
    .paging_mode = &paging_mode,
    .smp = &smp,
    .memmap = &memmap,
    .entry_point = &entry_point,
    .kernel_file = &kernel_file,
    .modules = &modules,
    .rsdp = &rsdp,
    .smbios = &smbios,
    .efi_system_table = &efi_system_table,
    .efi_memmap = &efi_memmap,
    .boot_time = &boot_time,
    .kernel_address = &kernel_address,
    .dtb = &dev_tree_blob
};