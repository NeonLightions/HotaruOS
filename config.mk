# @file config.mk
# @brief HotaruOS's build configurations
# 
# @copyright
# This file is part of HotaruOS and is released under the terms
# of the MIT License - See LICENSE.md
# Copyright (c) 2024 NeonLightions

current_dir   := $(realpath -s $(dir $(abspath $(firstword $(MAKEFILE_LIST)))))

# Nuke built-in variables
MAKEFLAGS += -rR
.SUFFIXES:

# Project information, don't change it
override name      = HotaruOS
override major     = 0
override minor     = 1
override sublevel  = 0

# Architecture to build, default x86_64
# See more supported architectures in arch/ directory
# Name must be corresponding to arch/${arch} name

# Supported architectures:
#	- x86_64
arch ?= x86_64

# This output name can be changed, but recommended to
# keep it default, maybe for debugging?
output_name ?= ${name}-${major}.${minor}.${sublevel}-${arch}


# Path for GCC. Using absolute path, change if need
compiler_prefix ?=

# Emulator (if use)
# For HotaruOS, the system must meet these requirements:
#	- 1G RAM or above
#	- Support UEFI
#	- CPU must support CPUID instruction
#	- Support IDE

# Supported values:
#	- no
#	- yes (default: qemu)
#	- qemu

# TODO: Currently only support QEMU,
# should I add more?
use_emul ?= yes

# Name of the emulator, must be a correct command
# to execute
# Default: qemu-system-x86_64
emul_name ?= qemu-system-x86_64

# Emulator params. This is the default for QEMU.
emul_rom 		?= -bios scripts/ovmf/x64/OVMF.fd
emul_ram 		?= -m 4G
emul_smp 		?= -smp 4
emul_machine 	?= -M q35
emul_debug		?= -debugcon mon:stdio
emul_extra		?= -vga std -usb -name "HotaruOS ${arch}"

emul_params ?= \
	${emul_rom} \
	${emul_ram} \
	${emul_smp} \
	${emul_machine} \
	${emul_debug} \
	${emul_extra}