# @file arch/x86_64/config.mk
# @brief HotaruOS's x86_64 boot (pre-init) build configurations
# 
# @copyright
# This file is part of HotaruOS and is released under the terms
# of the MIT License - See LICENSE.md
# Copyright (c) 2024 NeonLightions

include ../../config.mk

# Must be cross compiler, even running on specific architecture.
target 	?= ${arch}-elf

cc 		?= ${compiler_prefix}${target}-gcc
ld 		?= ${compiler_prefix}${target}-ld
as 		?= ${compiler_prefix}${target}-as
objdump ?= ${compiler_prefix}${target}-objdump
objcopy ?= ${compiler_prefix}${target}-objcopy
readelf ?= ${compiler_prefix}${target}-readelf
hexdump ?= ${compiler_prefix}${target}-hexdump
strip 	?= ${compiler_prefix}${target}-strip
nm		?= ${compiler_prefix}${target}-nm

# CFLAGS for kernel, modifiable
kcflags ?= -g -O2 -pipe

# There will be some flags that can't be changed
override kcflags += \
	-Wall \
	-Wextra \
	-std=gnu11 \
	-ffreestanding \
	-MMD \
	-MP \
	-fno-stack-protector \
	-fno-stack-check \
	-fno-lto \
	-fno-PIC \
	-m64 \
	-mno-80387 \
	-mno-mmx \
	-mno-sse \
	-mno-sse2 \
	-mno-red-zone \
	-mcmodel=kernel

# LDFLAGS for kernel, modifiable
kldflags ?=

# There will be some flags that can't be changed
override kldflags += \
	-m elf_${arch} \
	-nostdlib \
	-static \
	-z max-page-size=0x1000