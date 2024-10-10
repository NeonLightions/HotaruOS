# Project information
name      = HotaruOS
major     = 1
minor     = 1
sublevel  = 0

# Output
build_dir = ${current_dir}/build

# Sources
kernel_dir 	= ${current_dir}/kernel
boot_dir 	= ${current_dir}/boot
arch_dir 	= ${current_dir}/arch
module_dir 	= ${current_dir}/modules

# Emulator (if use)
# For HotaruOS, the system must meet these requirements:
#	- 1G RAM or above
#	- Support UEFI
#	- CPU must support CPUID instruction
#	- Support IDE
use_emul ?= n