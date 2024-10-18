# @file arch/x86_64/Makeile
# @brief Build rules for x86_64 boot process
# 
# @copyright
# This file is part of HotaruOS and is released under the terms
# of the MIT License - See LICENSE.md
# Copyright (c) 2024 NeonLightions

include config.mk

override linker_file := linker.lds
build_dir ?= ${current_dir}/build

override cfiles := $(shell find -L * -type f -name '*.c' | LC_ALL=C sort)
override asfiles := $(shell find -L * -type f -name '*.S' | LC_ALL=C sort)
override objs := $(addprefix ${build_dir}/, $(cfiles:.c=.o) $(asfiles:.S=.o))
override deps := $(addprefix ${build_dir}/, $(cfiles:.c=.d) $(asfiles:.S=.d))

.PHONY: all
all: ${build_dir}/bin/${output_name}-loader

${build_dir}/bin/${output_name}-loader: ${linker_file} ${objs}
	mkdir -p $(dir $@)
	${ld} ${objs} ${kldflags} -T ${linker_file} -o $@.elf-${arch}
	cp $@.elf-${arch} $@
	${strip} $@
	
# Include header dependencies
-include ${deps}

${build_dir}/%.o: %.c
	mkdir -p $(dir $@)
	${cc} ${kcflags} -c $< -o $@

${build_dir}/%.o: %.S
	mkdir -p $(dir $@)
	${cc} ${kcflags} -c $< -o $@