# @file Makeile
# @brief Build rules for HotaruOS
# 
# @copyright
# This file is part of HotaruOS and is released under the terms
# of the MIT License - See LICENSE.md
# Copyright (c) 2024 NeonLightions

# Must include in every Makefile configs
include config.mk

build_dir ?= ${current_dir}/build
${build_dir}:
	@mkdir -p $@

.phony: all
all:
	echo ${this_makefile}

.PHONY: build
build: ${build_dir}
	-make -C ${current_dir}/kernel all build_dir=${build_dir}/kernel
	-cp build/kernel/bin/${output_name}-kernel hotaru-${arch}

	-make -C ${current_dir}/arch/${arch} all build_dir=${build_dir}/arch/${arch}
	cp build/arch/${arch}/bin/${output_name}-loader arch-loader

	-make -C ${current_dir}/modules all build_dir=${build_dir}/modules

###########################################################################################

.PHONY: run.disk
run.disk: ${output_name}.img
	@if [ ${use_emul} = "yes" ]; then \
		${emul_name} ${emul_params} -hda ${output_name}.img; \
	fi

.PHONY: run.iso
run.iso: ${output_name}.iso
	@if [ ${use_emul} = "yes" ]; then \
		${emul_name} ${emul_params} -cdrom ${output_name}.iso -boot order=c; \
	fi

############################################################################################

# Everytime invoke this rule, the previous disk will
# be deleted.
.PHONY: limine.disk
limine.disk: build ${output_name}.img
	sudo kpartx -a ${output_name}.img
	sudo mount /dev/mapper/loop0p2 /mnt/disk --mkdir
	sudo mount /dev/mapper/loop0p1 /mnt/disk/boot

	sudo cp arch-loader hotaru-${arch} /mnt/disk/boot
	sudo cp scripts/limine/limine-bios.sys scripts/limine.conf /mnt/disk/boot/limine
	sudo cp scripts/limine/BOOTX64.EFI /mnt/disk/boot/EFI/BOOT

	sudo umount -R /mnt/disk
	sudo kpartx -d ${output_name}.img

	./scripts/limine/limine bios-install ${output_name}.img

${output_name}.img:
# Create a blank 512 MiB disk
	dd if=/dev/zero of=${output_name}.img bs=1M count=512

# Format the disk, create GPT partition table and approriate partitions
# The disk will be structured as follow:
#		Partition 1: EFI System Paritition (32 MiB)
#		Partition 2: Root ext2 filesystem (Rest of the disk)
	sgdisk ${output_name}.img \
		-n 1:2048:+128M -t 1:ef00 \
		-n 2:: -t 2:8300

	sudo kpartx -a ${output_name}.img
	sudo mkfs.fat -F32 /dev/mapper/loop0p1
	sudo mkfs.ext2 -b 1024 /dev/mapper/loop0p2
	sudo mount /dev/mapper/loop0p2 /mnt/disk --mkdir
	sudo mount /dev/mapper/loop0p1 /mnt/disk/boot --mkdir
	
	sudo mkdir -p /mnt/disk/boot/{EFI/BOOT,limine}
	
	sudo umount -R /mnt/disk
	sudo kpartx -d ${output_name}.img

.PHONY: limine.iso
limine.iso: build
	mkdir -p iso_root/limine
	mkdir -p iso_root/EFI/BOOT
	
	cp arch-loader hotaru-${arch} iso_root
	cp scripts/limine.conf scripts/limine/limine-bios.sys scripts/limine/limine-bios-cd.bin \
		scripts/limine/limine-uefi-cd.bin iso_root/limine
	cp scripts/limine/BOOTX64.EFI iso_root/EFI/BOOT

	xorriso -as mkisofs -b limine/limine-bios-cd.bin \
			-no-emul-boot -boot-load-size 4 -boot-info-table \
			--efi-boot limine/limine-uefi-cd.bin \
			-efi-boot-part --efi-boot-image --protective-msdos-label \
			iso_root -o ${output_name}.iso
	
	./scripts/limine/limine bios-install ${output_name}.iso

###########################################################################################

.PHONY: clean
clean:
	@rm -rf build
	@rm -f  arch-loader hotaru-${arch}
	@rm -rf ${output_name}*
	@rm -rf iso_root

###########################################################################################