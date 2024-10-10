this_makefile := $(abspath $(lastword $(MAKEFILE_LIST)))
current_dir   := $(dir ${this_makefile})

include config.mk

.phony: all
all:
	echo ${current_dir} ${this_makefile}

build: ${build_dir}
	make -C ${kernel_dir} all build_dir=${build_dir}
	make -C ${boot_dir}	  all build_dir=${build_dir}
	make -C ${arch_dir}   all build_dir=${build_dir}
	make -C ${module_dir} all build_dir=${build_dir}
	

run:
# Insert command to run your emulator,
# see requirments in config.mk
	@if [ ${use_emul} = "y" ]; then \
		\
	fi