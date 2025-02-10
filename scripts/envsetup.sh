#!/bin/bash

# supported board:
#     qemu
#     bm1684
#     mango

CHIP=${CHIP:-bm1684}
DEBUG=${DEBUG:-0} # now only for TFA
DISTRO=${DISTRO:-focal} # focal = Ubuntu 20.04; kylinos
KERNEL_VARIANT=${KERNEL_VARIANT:-normal} # normal; mininum
PRODUCT=${PRODUCT:-} # se6; cust01; cust02

if [ "$CHIP" == "qemu" ]; then
	DEBUG=1
fi

if [ "$CHIP" == "bm1684" -o "$CHIP" == "qemu" ]; then
	VENDOR=bitmain
else
	VENDOR=sophgo
fi

if [ $DEBUG -eq 1 ]; then
	TFA_TYPE=debug
else
	TFA_TYPE=release
fi

function gettop
{
	local TOPFILE=bootloader-arm64/scripts/envsetup.sh
	if [ -n "$TOP" -a -f "$TOP/$TOPFILE" ] ; then
		# The following circumlocution ensures we remove symlinks from TOP.
		(cd $TOP; PWD= /bin/pwd)
	else
		if [ -f $TOPFILE ] ; then
			# The following circumlocution (repeated below as well) ensures
			# that we record the true directory name and not one that is
			# faked up with symlink names.
			PWD= /bin/pwd
		else
			local HERE=$PWD
			T=
			while [ \( ! \( -f $TOPFILE \) \) -a \( $PWD != "/" \) ]; do
				\cd ..
				T=`PWD= /bin/pwd -P`
			done
			\cd $HERE

			if [ -f "$T/$TOPFILE" ]; then
				echo $T
			fi
		fi
	fi
}

function build_tfa()
{
	mkdir -p $OUTPUT_DIR

	pushd $TFA_SRC_DIR

	# clean fip tool as some options may changed
	make PLAT=${PROJECT_NAME} DEBUG=${DEBUG} --no-print-directory -C $FIP_TOOL_DIR clean
	# create a dummy u-boot binary for packing fip
	touch $OUTPUT_DIR/u-boot.bin

	if [ $DEBUG -eq 1 ] ; then
		make -j$(nproc) PLAT=${PROJECT_NAME} \
			DEBUG=1 CFLAGS="-O0 -g -DCONFIG_PRODUCT_${PRODUCT}" \
			BL33=$OUTPUT_DIR/u-boot.bin all fip
	else
		make -j$(nproc) PLAT=${PROJECT_NAME} \
			DEBUG=0 CFLAGS="-g -DCONFIG_PRODUCT_${PRODUCT}" LOG_LEVEL=40 ENABLE_ASSERTIONS=1 \
			BL33=$OUTPUT_DIR/u-boot.bin all fip
	fi
	ret=$?

	popd
	if [ $ret -ne 0 ]; then
		echo "making TFA failed"
		return $ret
	fi

	cp $TFA_BUILD_DIR/bl*.bin $OUTPUT_DIR/
	cp $TFA_BUILD_DIR/fip.bin $OUTPUT_DIR/
	cp $TFA_BUILD_DIR/bl1/bl1.elf $OUTPUT_DIR/
	cp $TFA_BUILD_DIR/bl1/bl1.dump $OUTPUT_DIR/
	cp $TFA_BUILD_DIR/bl2/bl2.elf $OUTPUT_DIR/
	cp $TFA_BUILD_DIR/bl2/bl2.dump $OUTPUT_DIR/
	cp $TFA_BUILD_DIR/bl31/bl31.elf $OUTPUT_DIR/
	cp $TFA_BUILD_DIR/bl31/bl31.dump $OUTPUT_DIR/

	if [ $CHIP == "qemu" ]; then
		pushd $OUTPUT_DIR
		dd if=bl1.bin of=flash.bin bs=4096 conv=notrunc
    		dd if=fip.bin of=flash.bin seek=64 bs=4096 conv=notrunc
    		popd
	fi
}

function clean_tfa()
{
	pushd $TFA_SRC_DIR
	make PLAT=${PROJECT_NAME} DEBUG=${DEBUG} clean
	make PLAT=${PROJECT_NAME} DEBUG=${DEBUG} -C $FIP_TOOL_DIR clean
	popd

	rm -f $OUTPUT_DIR/bl*.bin
	rm -f $OUTPUT_DIR/fip.bin
	rm -f $OUTPUT_DIR/bl*.elf
	rm -f $OUTPUT_DIR/bl*.dump
	rm -f $OUTPUT_DIR/flash.bin
}

function build_uboot()
{
	mkdir -p $OUTPUT_DIR
	mkdir -p $UBOOT_BUILD_DIR

	pushd $UBOOT_SRC_DIR

	export KBUILD_OUTPUT=$UBOOT_BUILD_DIR
	make ${VENDOR}_${PROJECT_NAME}_defconfig
	make -j$(nproc) all
	ret=$?
	unset KBUILD_OUTPUT

	popd
	if [ $ret -ne 0 ]; then
		echo "making u-boot failed"
		return $ret
	fi

	cp $UBOOT_BUILD_DIR/u-boot.bin $OUTPUT_DIR/
	cp $UBOOT_BUILD_DIR/u-boot $OUTPUT_DIR/u-boot.elf
	${CROSS_COMPILE}objdump -S $OUTPUT_DIR/u-boot.elf > $OUTPUT_DIR/u-boot.dump
}

function clean_uboot()
{
	rm -rf $UBOOT_BUILD_DIR
	rm -f $OUTPUT_DIR/u-boot.bin
	rm -f $OUTPUT_DIR/u-boot.elf
	rm -f $OUTPUT_DIR/u-boot.dump
}

function build_fip()
{
	build_uboot
	ret=$?
	if [ $ret -ne 0 ]; then
		return $ret
	fi
	build_tfa
	ret=$?
	if [ $ret -ne 0 ]; then
		return $ret
	fi

	gcc -g -Werror $SCRIPTS_DIR/gen_spi_flash.c -o $OUTPUT_DIR/gen_spi_flash

	pushd $OUTPUT_DIR
	rm -f ./spi_flash.bin
	if [ "$CHIP" == "bm1684" ]; then
		./gen_spi_flash -c bm1684
		mv spi_flash.bin spi_flash_bm1684.bin
		./gen_spi_flash -c bm1684x
		mv spi_flash.bin spi_flash_bm1684x.bin
		echo combine spi flash binary...
		dd if=spi_flash_bm1684x.bin of=spi_flash.bin bs=4194304 conv=notrunc
    		dd if=spi_flash_bm1684.bin of=spi_flash.bin seek=1 bs=4194304 conv=notrunc
	else
		./gen_spi_flash -c $CHIP
	fi
	popd
}

function clean_fip()
{
	clean_uboot
	clean_tfa

	rm -f $OUTPUT_DIR/gen_spi_flash
	rm -f $OUTPUT_DIR/spi_flash*.bin
}

function build_mango_flash()
{
	rm -f $OUTPUT_DIR/ramdisk_mini.cpio*
	cp $RAMDISK_BUILD_DIR/workspace/ramdisk_mini.cpio $OUTPUT_DIR

	gcc -g -Werror $SCRIPTS_DIR/gen_spi_flash.c -o $OUTPUT_DIR/gen_spi_flash

	pushd $OUTPUT_DIR
	gzip ./ramdisk_mini.cpio
	mkimage -A arm64 -O linux -T ramdisk -d ramdisk_mini.cpio.gz initramfs_arm64.img

	rm -f ./spi_flash.bin
	./gen_spi_flash -c $CHIP opensbi riscv64/fw_jump.bin 0x00000000 \
				 riscv64_Image riscv64/Image 0x00200000 \
				 mango_rv_pld.dtb riscv64/sg2042.dtb 0x20000000 \
				 initramfs.linux_riscv64.cpio riscv64/initramfs.linux_riscv64.cpio 0x30000000 \
				 zsbl riscv64/zsbl.bin 0x40000000 \
				 arm64_Image Image 0x00180000 \
				 mango_pld.dtb mango_pld.dtb 0x02000000 \
				 mango_fpga.dtb mango_fpga.dtb 0x02000000 \
				 mango_evb_v0.0.dtb mango_evb_v0.0.dtb 0x02000000 \
				 initramfs_arm64.img initramfs_arm64.img 0x03000000
	popd

	pushd $SCRIPTS_DIR/
	echo packing update image...
	./mango_make_package.sh sdcard $OUTPUT_DIR
	popd
}

function clean_mango_sdcard()
{
	rm -rf $OUTPUT_DIR/sdcard
}

function build_mango_bsp()
{
	build_fip &&

	build_rv_all &&

	build_kernel &&
	build_ramdisk uclibc xmr &&
	build_debs &&
	build_rootp &&

	build_mango_flash &&
	build_mango_sdcard &&
	build_pld &&
	build_sdimage
}

function clean_mango_bsp()
{
	clean_fip &&

	clean_rv_all &&

	clean_kernel &&
	clean_ramdisk uclibc xmr &&
	clean_debs &&
	clean_rootp &&

	clean_mango_flash &&
	clean_mango_sdcard &&
	clean_pld &&
	clean_sdimage
}

function install_debs()
{
	if [ ! -d $DEB_INSTALL_DIR ]; then
		mkdir -p $DEB_INSTALL_DIR
	fi
	echo install $1
	cp $1 $DEB_INSTALL_DIR/
}

function build_kernel()
{
	mkdir -p $OUTPUT_DIR
	mkdir -p $KERNEL_BUILD_DIR

	pushd $KERNEL_SRC_DIR
	if [ -f arch/arm64/configs/${VENDOR}_${PROJECT_NAME}_${PRODUCT}_defconfig ]; then
		./scripts/kconfig/merge_config.sh -O arch/arm64/configs/ -m \
						arch/arm64/configs/${VENDOR}_${PROJECT_NAME}_${KERNEL_VARIANT}_defconfig \
						arch/arm64/configs/${VENDOR}_${PROJECT_NAME}_${PRODUCT}_defconfig
		cp arch/arm64/configs/.config arch/arm64/configs/${PRODUCT}_defconfig
		make ARCH=arm64 O=$KERNEL_BUILD_DIR ${PRODUCT}_defconfig
		ret=$?
		if [ $ret -ne 0 ]; then
			popd
			echo "making customized kernel config failed"
			return $ret
		fi
		rm arch/arm64/configs/${PRODUCT}_defconfig
	else
		make ARCH=arm64 O=$KERNEL_BUILD_DIR ${VENDOR}_${PROJECT_NAME}_${KERNEL_VARIANT}_defconfig
		ret=$?
		if [ $ret -ne 0 ]; then
			popd
			echo "making kernel config failed"
			return $ret
		fi
	fi
	popd

	pushd $KERNEL_BUILD_DIR
	KERNELRELEASE=$(make ARCH=arm64 kernelrelease)

	make ARCH=arm64 -j$(nproc) Image dtbs modules
	ret=$?
	if [ $ret -ne 0 ]; then
		popd
		echo "making kernel image failed"
		return $ret
	fi

	rm -rf ./modules
	make ARCH=arm64 modules_install INSTALL_MOD_PATH="./modules"
	ret=$?
	if [ $ret -ne 0 ]; then
		popd
		echo "making kernel modules failed"
		return $ret
	fi

	if [ "$1" != "r" ] ; then
		# remove previous build
		rm -f ../linux-*
		rm -rf ./debian
		rm -rf ./debs

		make ARCH=arm64 Image.gz bindeb-pkg
		ret=$?
		if [ $ret -ne 0 ]; then
			popd
			echo "making deb package failed"
			return $ret
		fi

		mkdir ./debs
		cp ../linux-image-${KERNELRELEASE}_*.deb ./debs/linux-image-${KERNELRELEASE}.deb
		cp ../linux-image-${KERNELRELEASE}-dbg_*.deb ./debs/linux-image-${KERNELRELEASE}-dbg.deb
		cp ../linux-headers-${KERNELRELEASE}_*.deb ./debs/linux-headers-${KERNELRELEASE}.deb
		rm -f $DEB_INSTALL_DIR/linux-*.deb
		install_debs "./debs/*.deb"
		install_debs $KERNEL_SRC_DIR/tools/include/tools/be_byteshift.h
		install_debs $KERNEL_SRC_DIR/tools/include/tools/le_byteshift.h

		# remove debian folder to avoid unnecessary traverse when building other projects
		rm -rf ./debian
	fi
	popd

	# copy kernel image and device tree to output folder
	cp $KERNEL_BUILD_DIR/arch/arm64/boot/Image $OUTPUT_DIR/
	cp $KERNEL_BUILD_DIR/arch/arm64/boot/dts/${VENDOR}/${PROJECT_NAME}*.dtb $OUTPUT_DIR/
	cp $KERNEL_BUILD_DIR/vmlinux $OUTPUT_DIR/

	# copy kernel image and device tree to ramdisk
	mkdir -p $RAMDISK_BUILD_DIR/workspace
	cp $KERNEL_BUILD_DIR/arch/arm64/boot/Image $RAMDISK_BUILD_DIR/workspace
	cp $KERNEL_BUILD_DIR/arch/arm64/boot/dts/${VENDOR}/${PROJECT_NAME}*.dtb $RAMDISK_BUILD_DIR/workspace

	echo "export KERNEL_PATH=${KERNEL_BUILD_DIR}" > ${SCRIPTS_DIR}/KERNEL_PATH.sh
}

function clean_kernel()
{
	rm -rf $KERNEL_BUILD_DIR
	rm -f $KERNEL_SRC_DIR/build/$PROJECT_NAME/linux-*
	rm -f $OUTPUT_DIR/Image
	rm -f $OUTPUT_DIR/vmlinux
	rm -f $OUTPUT_DIR/*.dtb
}

TOOLS_LIST=(
carveout
ion_test
flash_update
)

function build_debs()
{
	echo make BSP tools...
	rm -rf $TOOLS_DST_DIR
	for i in ${TOOLS_LIST[@]}
	do
		if [ -d  $TOOLS_SRC_DIR/$i ]; then
			pushd $TOOLS_SRC_DIR/$i
			make
			ret=$?
			if [ $ret -ne 0 ]; then
				make clean
				popd
				echo "making $i failed"
				return $ret
			fi
			mkdir -p $TOOLS_DST_DIR/bin
			cp ./$i $TOOLS_DST_DIR/bin
			make clean
			popd
		fi
	done

	pushd $TOOLS_DST_DIR
	mkdir -p deb/usr/sbin
	cp ./bin/* ./deb/usr/sbin
	cp -r $TOOLS_SRC_DIR/DEBIAN ./deb/
	local version=$(echo $(cat $TOOLS_SRC_DIR/DEBIAN/control | grep Version) | cut -d ' ' -f 2)
	rm -f $DEB_INSTALL_DIR/sophgo-bsp-tools_*_arm64.deb
	dpkg-deb -b deb/ sophgo-bsp-tools_${version}_arm64.deb
	install_debs "sophgo-bsp-tools_${version}_arm64.deb"
	popd

	echo make BSP images...
	sudo rm -rf $IMAGES_DST_DIR
	mkdir -p $IMAGES_DST_DIR/deb/DEBIAN
	mkdir -p $IMAGES_DST_DIR/deb/boot

	pushd $IMAGES_DST_DIR
	cp $SCRIPTS_DIR/bsp-images/* ./deb/DEBIAN/
	cp $OUTPUT_DIR/emmcboot.itb ./deb/boot/
	cp $OUTPUT_DIR/boot.scr.emmc ./deb/boot/
	cp $OUTPUT_DIR/multi.its ./deb/boot/
	cp $OUTPUT_DIR/spi_flash.bin ./deb/boot/
	# /boot is a FAT32 partion so we have to make file property here identical to those in FAT32
	# partition, otherwise dpkg will try to change property during installation and fail with error.
	chmod 755 ./deb/boot/*
	sudo chown root:root ./deb/boot/*
	rsync -a --no-links $KERNEL_BUILD_DIR/modules/ ./deb/
	local version=$(echo $(cat $SCRIPTS_DIR/bsp-images/control | grep Version) | cut -d ' ' -f 2)
	rm -f $DEB_INSTALL_DIR/sophgo-bsp-images_*_arm64.deb
	dpkg-deb -b deb/ sophgo-bsp-images_${version}_arm64.deb
	install_debs "sophgo-bsp-images_${version}_arm64.deb"
	popd

	echo make BSP rootfs modification deb...
	sudo rm -rf $ROOTFS_DST_DIR
	mkdir -p $ROOTFS_DST_DIR/

	pushd $ROOTFS_DST_DIR
	local version=$(echo $(cat $DISTRO_MOD_DIR/sophgo-fs/DEBIAN/control | grep Version) | cut -d ' ' -f 2)
	rm -f $DEB_INSTALL_DIR/sophgo-bsp-rootfs_*_arm64.deb
	dpkg-deb -b $DISTRO_MOD_DIR/sophgo-fs sophgo-bsp-rootfs_${version}_arm64.deb
	install_debs "sophgo-bsp-rootfs_${version}_arm64.deb"

	if [ "$PRODUCT" != "" ] && [ -d $DISTRO_MOD_DIR/product-$PRODUCT ]; then
		echo make product-$PRODUCT deb...
		local version=$(echo $(cat $DISTRO_MOD_DIR/product-$PRODUCT/DEBIAN/control | grep Version) | cut -d ' ' -f 2)
		rm -f $DEB_INSTALL_DIR/sophgo-${PRODUCT}_*_arm64.deb
		dpkg-deb -b $DISTRO_MOD_DIR/product-$PRODUCT sophgo-${PRODUCT}_${version}_arm64.deb
		install_debs "sophgo-${PRODUCT}_${version}_arm64.deb"
	fi
	popd
}

function clean_debs()
{
	rm -rf $TOOLS_DST_DIR
	rm -rf $IMAGES_DST_DIR
	rm -rf $DEB_INSTALL_DIR
}

function create_ramdisk_folders()
{
	mkdir -p $OUTPUT_DIR
	mkdir -p $RAMDISK_BUILD_DIR/target
	rm -rf $RAMDISK_BUILD_DIR/target/*
	mkdir -p $RAMDISK_BUILD_DIR/configs
	rm -rf $RAMDISK_BUILD_DIR/configs/*

	# create target folder with project overwrite
	# here we use --remove-destination to overwrite symbolic links
	cp -r --remove-destination $RAMDISK_DIR/target/rootfs_$1/* $RAMDISK_BUILD_DIR/target/
	if [ -d $RAMDISK_DIR/target/overlay/$PROJECT_NAME ] ; then
		cp -r --remove-destination $RAMDISK_DIR/target/overlay/$PROJECT_NAME/* $RAMDISK_BUILD_DIR/target/
	fi

	if [ "$PRODUCT" != "" ] && [ -d $RAMDISK_DIR/target/overlay/$PRODUCT ]; then
		echo copy product $PRODUCT ramdisk overlay files...
		sudo cp -rf $RAMDISK_DIR/target/overlay/$PRODUCT/* $RAMDISK_BUILD_DIR/target/
	fi

	# cook target folder
	if [ "$2" == "emmc" ]; then
		rm $RAMDISK_BUILD_DIR/target/init
		mv $RAMDISK_BUILD_DIR/target/init_emmc.sh $RAMDISK_BUILD_DIR/target/init
	elif [ "$2" == "emmc_ro" ]; then
		rm $RAMDISK_BUILD_DIR/target/init
		mv $RAMDISK_BUILD_DIR/target/init_emmc_ro.sh $RAMDISK_BUILD_DIR/target/init
	elif [ "$2" == "pcie" ]; then
		cp -r --remove-destination $RAMDISK_DIR/target/overlay/${PROJECT_NAME}_pcie/* $RAMDISK_BUILD_DIR/target/
	elif [ "$2" == "mix" ]; then
		cp -r --remove-destination $RAMDISK_DIR/target/overlay/${PROJECT_NAME}_mix/* $RAMDISK_BUILD_DIR/target/
	fi

	# create config folder
	if [ -d $RAMDISK_DIR/configs/$PROJECT_NAME ] ; then
		cp -r $RAMDISK_DIR/configs/$PROJECT_NAME/* $RAMDISK_BUILD_DIR/configs
	fi
}

RAMDISK_TYPES=(
uclibc
glibc
mini
)

RAMDISK_FAVORS=(
emmc
emmc_ro
pcie
mix
recovery
)

function build_ramdisk()
{
	for i in ${RAMDISK_TYPES[@]}
	do
		if [ "$i" == "$1" ]; then
			local RAMDISK_TYPE=$1
		fi
	done
	if [ -z "$RAMDISK_TYPE" ]; then
		echo please specify a ramdisk type:
		for i in ${RAMDISK_TYPES[@]}
		do
			echo -e "\t$i"
		done
		return
	fi

	if [ -n "$2" ]; then
		for i in ${RAMDISK_FAVORS[@]}
		do
			if [ "$i" == "$2" ]; then
				local RAMDISK_FAVOR=$2
			fi
		done
		if [ -z "$RAMDISK_FAVOR" ]; then
			echo please specify a ramdisk favor:
			for i in ${RAMDISK_FAVORS[@]}
			do
				echo -e "\t$i"
			done
			return
		fi
	fi

	echo build ramdisk type:$RAMDISK_TYPE favor:$RAMDISK_FAVOR
	create_ramdisk_folders ${RAMDISK_TYPE} ${RAMDISK_FAVOR}

	mkdir -p $RAMDISK_BUILD_DIR/workspace
	pushd $RAMDISK_BUILD_DIR/workspace
	rm -f ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}_files.txt

	if [ -f $KERNEL_BUILD_DIR/arch/arm64/boot/Image ]; then
		cp $KERNEL_BUILD_DIR/arch/arm64/boot/Image .
		cp $KERNEL_BUILD_DIR/arch/arm64/boot/dts/${VENDOR}/${PROJECT_NAME}*.dtb .
	fi

	cp ../configs/multi.its .
	sed -i "s/data = \/incbin\/(\".\/rootfs.cpio\");/data = \/incbin\/(\".\/ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}.cpio\");/g" multi.its

	$KERNEL_SRC_DIR/usr/gen_initramfs_list.sh $RAMDISK_BUILD_DIR/target > ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}_files.txt
	echo -e "\nnod /dev/null 660 0 0 c 1 3\n" >>  ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}_files.txt

	$KERNEL_BUILD_DIR/usr/gen_init_cpio ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}_files.txt > ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}.cpio
	$UBOOT_BUILD_DIR/tools/mkimage -f multi.its ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}.itb

	if [ "$RAMDISK_FAVOR" == "emmc" -o "$RAMDISK_FAVOR" == "emmc_ro" ] ; then
		cp ./ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}.itb $OUTPUT_DIR/emmcboot.itb
		$UBOOT_BUILD_DIR/tools/mkimage -A arm64 -O linux -T script -C none -a 0 -e 0 -n "eMMC Boot Script" -d ../configs/boot.cmd.emmc $OUTPUT_DIR/boot.scr.emmc
	elif [ "$RAMDISK_FAVOR" == "recovery" ] ; then
		cp ./ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}.itb $OUTPUT_DIR/recovery.itb
	elif [ "$RAMDISK_FAVOR" == "" ]; then
		cp ./ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}.itb $OUTPUT_DIR/ramdisk_${RAMDISK_TYPE}.itb
	else
		cp ./ramdisk_${RAMDISK_TYPE}_${RAMDISK_FAVOR}.itb $OUTPUT_DIR/
	fi

	cp ./multi.its  $OUTPUT_DIR/
	popd
}

function clean_ramdisk()
{
	rm -rf $RAMDISK_BUILD_DIR
	rm -f $OUTPUT_DIR/*.its
	rm -f $OUTPUT_DIR/*.itb
	rm -f $OUTPUT_DIR/boot.scr.*
}

function build_bsp_without_package()
{
	build_fip &&

	build_kernel &&
	build_ramdisk uclibc emmc &&
	build_ramdisk glibc recovery &&
	build_bootp &&

	build_debs
}

# for building se6:
# $ PRODUCT=se6
# $ source bootloader-arm64/scripts/envsetup.sh
# $ build_bsp_without_package
# $ build_rootp
# $ build_update tftp
# in the last step of building tftp package, after generated
# the tftp folder, it will build a sdcard pakcage, then
# put the tftp folder into the recovery partition of the fresh
# sdcard package.

function build_package()
{
	build_rootp &&
	build_update tgz &&
	build_update sdcard &&
	build_update tftp
}

function build_bsp()
{
	build_bsp_without_package
	build_package
}

function build_bsp_ro()
{
	build_fip &&

	build_kernel &&
	build_ramdisk uclibc emmc_ro &&
	build_ramdisk glibc recovery &&
	build_bootp &&

	build_debs &&
	build_rootp &&
	build_update tgz &&
	build_update sdcard &&
	build_update tftp
}

function clean_bsp()
{
	clean_fip
	clean_kernel
	clean_ramdisk
	clean_bootp

	clean_debs
	clean_rootp
	clean_update
}

function build_doc()
{
	#Zh doc
	pushd $TOP_DIR/bootloader-arm64/docs/bm1684x/
	make pdf LANG=zh BUILD_RELEASE_VERSION=1.0.0
	cp -f $TOP_DIR/bootloader-arm64/docs/bm1684x/build/*.pdf $OUTPUT_DIR
	popd
	#En doc
	pushd $TOP_DIR/bootloader-arm64/docs/bm1684x-en/
	make pdf LANG=en BUILD_RELEASE_VERSION=1.0.0
	cp -f $TOP_DIR/bootloader-arm64/docs/bm1684x-en/build/*.pdf $OUTPUT_DIR
	popd
}

function clean_doc()
{
	pushd $TOP_DIR/bootloader-arm64/docs/bm1684x/
	make clean
	rm -f $TOP_DIR/install/soc_$PROJECT_NAME/*.pdf
	popd
	pushd $TOP_DIR/bootloader-arm64/docs/bm1684x-en/
	make clean
	rm -f $TOP_DIR/install/soc_$PROJECT_NAME/*.pdf
	popd
}

function run_qemu()
{
	if [ ! -x $TOP_DIR/install/soc_qemu ]; then
		return -1
	fi

	qemu-system-aarch64 \
		-gdb tcp::2021 \
		-nographic -machine virt,secure=on -cpu cortex-a53 -smp 4 -m 1024 \
		-netdev user,id=eth0 -device virtio-net-device,netdev=eth0 \
		-bios $TOP_DIR/install/soc_qemu/flash.bin \
		-device loader,file=$TOP_DIR/install/soc_qemu/recovery.itb,addr=0x44000000,force-raw=on
}

function build_distro()
{
	sudo rm -rf $DISTRO_DIR/$DISTRO
	mkdir -p $DISTRO_DIR/$DISTRO

	sudo qemu-debootstrap --arch=arm64 $DISTRO $DISTRO_DIR/$DISTRO

	pushd $DISTRO_DIR/$DISTRO
# following lines must not be started with space or tab.
sudo chroot . /bin/bash << "EOT"
adduser --gecos linaro --disabled-login linaro
echo "linaro:linaro" | chpasswd
usermod -a -G sudo linaro
adduser --gecos admin --disabled-login admin
echo "admin:admin" | chpasswd
usermod -a -G sudo admin

apt install -y software-properties-common
add-apt-repository universe

DEBIAN_FRONTEND=noninteractive apt install -y \
irqbalance kexec-tools busybox i2c-tools \
efivar grub-efi-arm64 initramfs-tools overlayroot \
net-tools openssh-server libnss-mdns ethtool ifupdown \
build-essential docker docker.io flex bison libssl-dev \
pciutils usbutils binutils bsdmainutils mmc-utils \
parted gdisk vim sysstat minicom atop u-boot-tools tree \
memtester rng-tools psmisc gawk automake pkg-config bc \
rsync lsof cmake dnsutils python3-dev nginx python3-pip \
acpid curl dnsutils linux-tools-generic libgflags-dev \
expect libgoogle-glog-dev libboost-all-dev

apt clean

pip3 install flask psutil numpy pyserial

sed -i -e '
/\%sudo/ c \
%sudo	ALL=(ALL) NOPASSWD: ALL
' /etc/sudoers

echo -e "127.0.0.1       sophon\n" >> /etc/hosts
echo -e "sophon\n" > /etc/hostname
echo -e "LC_ALL=C.UTF-8\n" > /etc/default/locale

ln -s /sbin/init /init

exit
EOT
# the end
	sudo rm -f $DISTRO_DIR/distro_$DISTRO.tgz
	sudo tar -czf $DISTRO_DIR/distro_$DISTRO.tgz *
	popd
}

function build_sdimage()
{
	if [ -d $OUTPUT_DIR/ext4 ]; then
		clean_sdimage
	fi

	echo create an image file...
	rm -f $OUTPUT_DIR/sd.img
	dd if=/dev/zero of=$OUTPUT_DIR/sd.img bs=1GiB count=3

	echo create partitions...
	sudo parted $OUTPUT_DIR/sd.img mktable msdos
	sudo parted $OUTPUT_DIR/sd.img mkpart p fat32 0% 128MiB
	sudo parted $OUTPUT_DIR/sd.img mkpart p fat32 128MiB 256MiB
	sudo parted $OUTPUT_DIR/sd.img mkpart p ext4 256MiBMiB 100%
	loops=$(sudo kpartx -av $OUTPUT_DIR/sd.img | cut -d ' ' -f 3)
	fat32part=$(echo $loops | cut -d ' ' -f 1)
	fat32part2=$(echo $loops | cut -d ' ' -f 2)
	ext4part=$(echo $loops | cut -d ' ' -f 3)
	echo EFI: $fat32part
	echo recovery: $fat32part2
	echo root: $ext4part
	sleep 3
	sudo mkfs.vfat /dev/mapper/$fat32part -n EFI
	ret=$?
	if [ $ret -ne 0 ]; then
		return $ret
	fi
	sudo mkfs.vfat /dev/mapper/$fat32part2 -n RECOVERY
	ret=$?
	if [ $ret -ne 0 ]; then
		return $ret
	fi
	sudo mkfs.ext4 /dev/mapper/$ext4part -L rootfs
	ret=$?
	if [ $ret -ne 0 ]; then
		return $ret
	fi

	echo mount rootfs partition...
	mkdir $OUTPUT_DIR/ext4
	sudo mount /dev/mapper/$ext4part $OUTPUT_DIR/ext4

	echo copy distro rootfs files...
	zcat $DISTRO_DIR/distro_$DISTRO.tgz | sudo tar -C $OUTPUT_DIR/ext4 -x -f -

	echo copy minimum distro overlay files...
	sudo cp -rf $DISTRO_OVERLAY_DIR/minimum/rootfs/* $OUTPUT_DIR/ext4

	echo copy bsp debs...
	cp -r $DEB_INSTALL_DIR $OUTPUT_DIR/ext4/home/linaro/

	echo mount EFI partition...
	sudo mkdir $OUTPUT_DIR/ext4/boot/efi
	sudo mount /dev/mapper/$fat32part $OUTPUT_DIR/ext4/boot/efi

	echo copy bootloader...
	sudo cp $OUTPUT_DIR/fip.bin $OUTPUT_DIR/ext4/boot/efi/
	sudo touch $OUTPUT_DIR/ext4/boot/efi/BOOT

	echo mount system nodes to target...
	sudo mount --bind /dev $OUTPUT_DIR/ext4/dev
	sudo mount --bind /dev/pts $OUTPUT_DIR/ext4/dev/pts
	sudo mount --bind /proc $OUTPUT_DIR/ext4/proc
	sudo mount --bind /sys $OUTPUT_DIR/ext4/sys

	echo modify configurations...
#	sudo sed -i 's/GRUB_TIMEOUT_STYLE=hidden/GRUB_TIMEOUT_STYLE=menu/g' \
#		$OUTPUT_DIR/ext4/etc/default/grub
#	sudo sed -i 's/GRUB_TIMEOUT=0/GRUB_TIMEOUT=3/g' \
#		$OUTPUT_DIR/ext4/etc/default/grub
	sudo sed -i 's/GRUB_CMDLINE_LINUX_DEFAULT="quiet splash"/GRUB_CMDLINE_LINUX_DEFAULT=""/g' \
		$OUTPUT_DIR/ext4/etc/default/grub
	sudo sed -i 's/GRUB_CMDLINE_LINUX=""/GRUB_CMDLINE_LINUX="console=ttyS0,115200 earlycon user_debug=31 overlayroot=disabled"/g' \
		$OUTPUT_DIR/ext4/etc/default/grub
	sudo bash -c "echo >> $OUTPUT_DIR/ext4/etc/default/grub"
	sudo bash -c "echo GRUB_RECORDFAIL_TIMEOUT=3 >> $OUTPUT_DIR/ext4/etc/default/grub"
	sudo bash -c "echo GRUB_DISABLE_OS_PROBER=true >> $OUTPUT_DIR/ext4/etc/default/grub"

#	sudo sed -i 's/overlayroot=""/overlayroot="device:dev=LABEL=root-rw"/g' \
#		$OUTPUT_DIR/ext4/etc/overlayroot.conf
	sudo sed -i 's/overlayroot=""/overlayroot="tmpfs"/g' \
		$OUTPUT_DIR/ext4/etc/overlayroot.conf

	# copy dtb file after installed linux-image package
	sudo bash -c "echo >> $OUTPUT_DIR/ext4/etc/kernel/postinst.d/initramfs-tools"
	sudo bash -c "echo 'cp /usr/lib/linux-image-\${version}/${VENDOR}/${PROJECT_NAME}*.dtb /boot' >> \
		$OUTPUT_DIR/ext4/etc/kernel/postinst.d/initramfs-tools"

	echo install linux image and update grub...
	pushd $OUTPUT_DIR/ext4
	sudo bash -c  "echo /dev/mapper/$fat32part > efidev"
# following lines must not be started with space or tab.
sudo chroot . /bin/bash << "EOT"
efidev=$(cat efidev)
grub-install $efidev
dpkg -i /home/linaro/bsp-debs/linux-image-*.deb
dpkg -i /home/linaro/bsp-debs/sophgo-bsp-tools_*.deb
exit
EOT
	sudo rm efidev
	popd

	echo create fstab...
# following lines must not be started with space or tab.
sudo bash -c "cat > $OUTPUT_DIR/ext4/etc/fstab << "EOF"
# /etc/fstab: static file system information.
#
# Use 'blkid' to print the universally unique identifier for a
# device; this may be used with UUID= as a more robust way to name devices
# that works even if disks are added and removed. See fstab(5).
#
# <file system> <mount point>   <type>  <options>       <dump>  <pass>
#
EOF"
# the end
	fat32uuid=$(sudo blkid /dev/mapper/$fat32part -s UUID -o value)
	ext4uuid=$(sudo blkid /dev/mapper/$ext4part -s UUID -o value)
	sudo bash -c "echo -e \"UUID=${fat32uuid}\t/boot/efi\tvfat\tumask=0077\t0\t1\" >> $OUTPUT_DIR/ext4/etc/fstab"
	sudo bash -c "echo -e \"UUID=${ext4uuid}\t/\text4\terrors=remount-ro\t0\t1\" >> $OUTPUT_DIR/ext4/etc/fstab"

	echo cleanup...
	sync
	sudo umount $OUTPUT_DIR/ext4/dev/pts
	sudo umount $OUTPUT_DIR/ext4/dev
	sudo umount $OUTPUT_DIR/ext4/proc
	sudo umount $OUTPUT_DIR/ext4/sys
	sudo umount /dev/mapper/$fat32part
	ret=$?
	if [ $ret -ne 0 ]; then
		return $ret
	fi
	sudo umount /dev/mapper/$ext4part
	ret=$?
	if [ $ret -ne 0 ]; then
		return $ret
	fi
	sudo kpartx -d $OUTPUT_DIR/sd.img
	ret=$?
	if [ $ret -ne 0 ]; then
		return $ret
	fi
	rm -r $OUTPUT_DIR/ext4
}

function clean_sdimage()
{
	rm -f $OUTPUT_DIR/sd.img
}

function build_pld()
{
	local PLD_MEMGEN=$SCRIPTS_DIR/mb2h/mb2h
	local PLD_CURRENT=out_$(date "+%Y%m%d_%H%M%S")
	local PLD_OUT=$PLD_INSTALL_DIR/$PLD_CURRENT

	rm -rf $PLD_INSTALL_DIR/out_*
	mkdir -p $PLD_OUT

	gcc -O2 ${PLD_MEMGEN}.c -o ${PLD_MEMGEN}

	hexdump -v -e '1/4 "%08x\n"' $OUTPUT_DIR/bl1.bin > $PLD_OUT/bl1.bin.text
	hexdump -v -e '1/1 "%02x\n"' $OUTPUT_DIR/spi_flash.bin > $PLD_OUT/fip.bin.text

	$PLD_MEMGEN $OUTPUT_DIR/ramdisk_mini.itb $PLD_OUT/a53-itb-%d.hex

	pushd $PLD_OUT
	$SCRIPTS_DIR/bootrom_padding.py
	popd

	# try riscv
	if [ "x$(type -t build_rv_pld)" == "xfunction" ]; then
		build_rv_pld $PLD_OUT
	fi

	pushd $PLD_INSTALL_DIR
	tar -czvf $PLD_CURRENT.tgz $PLD_CURRENT
	popd
}

function clean_pld()
{
	rm -rf $PLD_INSTALL_DIR
}

function build_bootp()
{
	rm -rf $OUTPUT_DIR/boot
	rm -f $OUTPUT_DIR/boot.tgz
	rm -f $OUTPUT_DIR/recovery.tgz

	pushd $OUTPUT_DIR
	mkdir ./boot

	echo copy boot files...
	cp emmcboot.itb spi_flash.bin multi.its boot.scr.emmc ./boot
	cp emmcboot.itb ./boot/emmcboot.itb.bak
	cp spi_flash.bin ./boot/spi_flash.bin.bak
	cp multi.its ./boot/multi.its.bak
	cp boot.scr.emmc ./boot/boot.scr.emmc.bak

	if [ "$PRODUCT" != "" ] && [ -d $DISTRO_OVERLAY_DIR/$PRODUCT/boot ]; then
		echo copy product $PRODUCT boot overlay files...
		sudo cp -rf $DISTRO_OVERLAY_DIR/$PRODUCT/boot/* ./boot
	fi

	cd ./boot
	tar -czvf ../boot.tgz *
	cd ..
	rm -rf ./boot

	tar -czvf recovery.tgz recovery.itb
	popd
}

function clean_bootp()
{
	rm -f $OUTPUT_DIR/boot.tgz
	rm -f $OUTPUT_DIR/recovery.tgz
}

function build_athena2_rootp()
{
	echo cleanup previous build...
	mkdir -p $OUTPUT_DIR/rootfs
	sudo rm -rf $OUTPUT_DIR/rootfs
	rm -f $OUTPUT_DIR/rootfs.tgz
	mkdir $OUTPUT_DIR/rootfs

	echo copy distro rootfs files from ${DISTRO_BASE_PKT}...
	zcat $DISTRO_BASE_PKT | sudo tar -C $OUTPUT_DIR/rootfs -x -f -

	echo copy linux debs...
	sudo mkdir -p $OUTPUT_DIR/rootfs/home/linaro
	sudo cp -r $DEB_INSTALL_DIR $OUTPUT_DIR/rootfs/home/linaro/

	echo copy overlay file to rootfs...
	if [ -d $DISTRO_OVERLAY_DIR/common/rootfs ]; then
		echo copy common rootfs overlay files...
		sudo cp -rf $DISTRO_OVERLAY_DIR/common/rootfs/* $OUTPUT_DIR/rootfs
	fi
	if [ -d $DISTRO_OVERLAY_DIR/$PROJECT_NAME/rootfs ]; then
		echo copy project rootfs overlay files...
		sudo cp -rf $DISTRO_OVERLAY_DIR/$PROJECT_NAME/rootfs/* $OUTPUT_DIR/rootfs
	fi
	# debs will be installed later after chroot and then deleted
	sudo cp -rf $DISTRO_MOD_DIR/debs $OUTPUT_DIR/rootfs

	if [ "$PRODUCT" != "" ] && [ -d $DISTRO_OVERLAY_DIR/$PRODUCT/debs ]; then
		echo copy product $PRODUCT debs overlay files...
		sudo cp -rf $DISTRO_OVERLAY_DIR/$PRODUCT/debs/* $OUTPUT_DIR/rootfs/debs/
	fi

	echo install packages...
	pushd $OUTPUT_DIR/rootfs
# following lines must not be started with space or tab.
# install bsp images first, so it won't run flash_update
sudo chroot . /bin/bash << "EOT"

if [  -d /debs ] && [ $(ls /debs/*.deb | wc -l) -gt 0 ]; then
	dpkg -i -R /debs
	while [ $? -ne 0 ];
	do
		sleep 1
		dpkg -i -R /debs
	done
fi
for file in /debs/*
do
	file=$(basename $file)
	if  [ "${file##*.}" == "whl" ]; then
		pip3 install --no-index --find-links=file:///debs ${file%%-*}
	fi
done
rm -rf /debs

if [  -d /home/linaro/debs ] && [ $(ls /home/linaro//debs/*.deb | wc -l) -gt 0 ]; then
	dpkg -i -R /home/linaro/debs
	while [ $? -ne 0 ];
	do
		sleep 1
		dpkg -i -R /home/linaro/debs
	done
fi

exit
EOT
	popd

	echo packing rootfs...
	pushd $OUTPUT_DIR/rootfs
	sudo chown 1000:1000 -R data
	sudo tar -czf ../rootfs.tgz *
	popd
}

function build_rootp()
{
	echo cleanup previous build...
	sudo rm -rf $OUTPUT_DIR/rootfs
	rm -f $OUTPUT_DIR/rootfs.tgz
	mkdir $OUTPUT_DIR/rootfs

	echo copy distro rootfs files from ${DISTRO_BASE_PKT}...
	zcat $DISTRO_BASE_PKT | sudo tar -C $OUTPUT_DIR/rootfs -x -f -

	echo copy linux debs...
	sudo mkdir -p $OUTPUT_DIR/rootfs/home/linaro
	sudo cp -r $DEB_INSTALL_DIR $OUTPUT_DIR/rootfs/home/linaro/

	echo copy overlay file to rootfs...
	if [ -d $DISTRO_OVERLAY_DIR/common/rootfs ]; then
		echo copy common rootfs overlay files...
		sudo cp -rf $DISTRO_OVERLAY_DIR/common/rootfs/* $OUTPUT_DIR/rootfs
	fi
	if [ -d $DISTRO_OVERLAY_DIR/$PROJECT_NAME/rootfs ]; then
		echo copy project rootfs overlay files...
		sudo cp -rf $DISTRO_OVERLAY_DIR/$PROJECT_NAME/rootfs/* $OUTPUT_DIR/rootfs
	fi
	# debs will be installed later after chroot and then deleted
	sudo cp -rf $DISTRO_MOD_DIR/debs $OUTPUT_DIR/rootfs

	if [ "$PRODUCT" != "" ] && [ -d $DISTRO_OVERLAY_DIR/$PRODUCT/debs ]; then
		echo copy product $PRODUCT debs overlay files...
		sudo cp -rf $DISTRO_OVERLAY_DIR/$PRODUCT/debs/* $OUTPUT_DIR/rootfs/debs/
	fi

	echo install packages...
	pushd $OUTPUT_DIR/rootfs
# following lines must not be started with space or tab.
# install bsp images first, so it won't run flash_update
sudo chroot . /bin/bash << "EOT"

if [  -d /debs ] && [ $(ls /debs/*.deb | wc -l) -gt 0 ]; then
	dpkg -i -R /debs
	while [ $? -ne 0 ];
	do
		sleep 1
		dpkg -i -R /debs
	done
fi
for file in /debs/*
do
	file=$(basename $file)
	if  [ "${file##*.}" == "whl" ]; then
		pip3 install --no-index --find-links=file:///debs ${file%%-*}
	fi
done
rm -rf /debs

dpkg -i /home/linaro/bsp-debs/sophgo-bsp-images_*.deb
dpkg -i /home/linaro/bsp-debs/sophgo-bsp-tools_*.deb
dpkg -i /home/linaro/bsp-debs/sophgo-bsp-rootfs_*.deb
dpkg -i /home/linaro/bsp-debs/sophgo-bsp-qt5_*.deb

dpkg -i /home/linaro/bsp-debs/sophon-soc-libsophon*.deb
dpkg -i /home/linaro/bsp-debs/sophon-mw-soc-sophon-ffmpeg*.deb
dpkg -i /home/linaro/bsp-debs/sophon-mw-soc-sophon-opencv*.deb

os_release=$(lsb_release -i | awk  '{print $3}')
echo "os is $os_release"
if [ "$os_release" = "Kylin" ]; then
	echo "add linaro user for kylin os!!!"
	adduser --gecos linaro --disabled-login linaro
	echo "linaro:linaro" | chpasswd
	usermod -a -G sudo linaro
	chown linaro.linaro -R /home/linaro
fi
if [ -f /home/linaro/bsp-debs/sophgo-se_*.deb  ]; then
	echo "install se6 deb"
	dpkg -i /home/linaro/bsp-debs/sophgo-se_*.deb
else
	if [ "$os_release" != "Kylin" ]; then
		echo "not se6 and not kylin, try install hdmi and system deb"
		dpkg -i /home/linaro/bsp-debs/sophgo-hdmi_*.deb
	fi
fi

exit
EOT
	popd

	# to make it simple, cust overlay always comes at last
	if [ "$PRODUCT" != "" ] && [ -d $DISTRO_OVERLAY_DIR/$PRODUCT/rootfs ]; then
		echo copy product $PRODUCT rootfs overlay files...
		sudo cp -rf $DISTRO_OVERLAY_DIR/$PRODUCT/rootfs/* $OUTPUT_DIR/rootfs
	fi

	if [ "$(ls $OUTPUT_DIR/rootfs/opt)" != "" ]; then
		echo separate opt partition...
		pushd $OUTPUT_DIR/rootfs/opt
		sudo rm -f $OUTPUT_DIR/opt.tgz
		sudo tar -zcf $OUTPUT_DIR/opt.tgz *
		if [ -L ./sophon/libsophon-current ]; then
			cd ./sophon
			libpath=$(basename $(readlink libsophon-current))
			echo packing ${libpath}...
			cd ./${libpath}
			sudo bash -c "echo ${libpath} > ./data/buildinfo.txt"
			sudo tar -zcf $OUTPUT_DIR/system.tgz *
		fi
		sudo rm -rf $OUTPUT_DIR/rootfs/opt/*
		popd
	fi

	echo packing rootfs...
	pushd $OUTPUT_DIR/rootfs
	sudo chown 1000:1000 -R data
	sudo tar -czf ../rootfs.tgz *
	popd
}

function clean_rootp()
{
	sudo rm -rf $OUTPUT_DIR/rootfs
	rm -f $OUTPUT_DIR/rootfs.tgz
}

UPDATE_TYPES=(
sdcard
tftp
tgz
)

function revert_package()
{
        mkdir -p $OUTPUT_DIR/package_update/update/sdcard
	cp -r $SCRIPTS_DIR/revert_package.sh $OUTPUT_DIR/package_update/update/sdcard
	sdcard_file="$OUTPUT_DIR/sdcard.tgz"

	if [ -f "$sdcard_file" ]; then
		echo "the sdcard.tgz exists."
		pushd $OUTPUT_DIR
		tar -zxf sdcard.tgz -m -C ./package_update/
		cp -r ./package_update/sdcard/* ./package_update/update/sdcard/
		cp -r ./package_update/sdcard/*.bin $OUTPUT_DIR/
		cd ./package_update/update/sdcard
        	./revert_package.sh boot data opt rootfs rootfs_rw recovery

		cd ../
		sudo rm -rf ./*.tgz
		mv ./sdcard/*.tgz ./
		sudo rm -rf ./sdcard
		cp -r ./* $OUTPUT_DIR/
		popd
		echo "revert package finished!"
	else
		echo "sdcard.tgz does not exist."
		echo "please copy sdcard.tgz to install/soc_bm1684/ and try again."
	fi
}

function build_update()
{
	for i in ${UPDATE_TYPES[@]}
	do
		if [ "$i" == "$1" ]; then
			local UPDATE_TYPE=$1
		fi
	done
	if [ -z "$UPDATE_TYPE" ]; then
		echo please specify an update type:
		for i in ${UPDATE_TYPES[@]}
		do
			echo -e "\t$i"
		done
		return
	fi

	if [ "$UPDATE_TYPE" == "tgz" ]; then
		echo packing bootloader and kernel image...
		pushd $OUTPUT_DIR
		mkdir bsp_update

		cp emmcboot.itb ./bsp_update
		cp spi_flash.bin ./bsp_update
		cp spi_flash_bm1684.bin ./bsp_update
		cp spi_flash_bm1684x.bin ./bsp_update
		cp boot.scr.emmc ./bsp_update
		cp multi.its ./bsp_update
		cp $TOOLS_DST_DIR/bin/flash_update ./bsp_update
		cd ./bsp_update
		md5sum * > md5.txt
		cd ..
		cp $SCRIPTS_DIR/bsp_update.sh ./bsp_update

		tar -czvf bsp_update.tgz bsp_update
		ret=$?
		rm -r ./bsp_update
		popd
		return $ret
	fi

	pushd $SCRIPTS_DIR/
	if [ ! -e ./mk_gpt ]; then
		pushd mk-gpt
		make
		popd
	fi
	echo packing update image...
	if [ $DISTRO == "kylinos" ]; then
		if [ "$PRODUCT" == "se" ] && [ "$UPDATE_TYPE" == "tftp" ]; then
			# se6 core board falls into here, it doesn't use kylinos
			./bm_make_package.sh $UPDATE_TYPE ./partition32G.xml $OUTPUT_DIR
		else
			./bm_make_package.sh $UPDATE_TYPE ./partition32G_kylinos.xml $OUTPUT_DIR
		fi
	else
		./bm_make_package.sh $UPDATE_TYPE ./partition32G.xml $OUTPUT_DIR
	fi
	popd

	pushd $OUTPUT_DIR/$1
	cp $SCRIPTS_DIR/local_update.sh .
	md5sum * > md5.txt
	popd

	if [ "$PRODUCT" == "se" ] && [ "$UPDATE_TYPE" == "tftp" ]; then
		echo "packet tftp package and sdcard package for se6..."
		echo $OUTPUT_DIR
		rm -f $OUTPUT_DIR/opt.tgz
		rm -f $OUTPUT_DIR/recovery.tgz
		rm -rf $OUTPUT_DIR/se_ctl_sdcard

		# try not overwrite someone else's sdcard folder
		if [ -d "$OUTPUT_DIR/sdcard" ];then
			mv $OUTPUT_DIR/sdcard $OUTPUT_DIR/sdcard-bak
		fi

		# pack core board's tftp package into control board's recovery partition
		pushd $OUTPUT_DIR
		tar -czvf recovery.tgz recovery.itb tftp
		popd

		# make sdcard package for control board
		pushd $SCRIPTS_DIR/
		if [ $DISTRO == "kylinos" ]; then
			./bm_make_package.sh sdcard ./partition32G_kylinos.xml $OUTPUT_DIR
		else
			./bm_make_package.sh sdcard ./partition32G.xml $OUTPUT_DIR
		fi
		popd

		mv $OUTPUT_DIR/sdcard $OUTPUT_DIR/se_ctl_sdcard
		cp $SCRIPTS_DIR/local_update.sh $OUTPUT_DIR/se_ctl_sdcard
		pushd $OUTPUT_DIR/se_ctl_sdcard
		md5sum * > md5.txt
		popd
		if [ -d "$OUTPUT_DIR/sdcard-bak" ];then
			mv $OUTPUT_DIR/sdcard-bak $OUTPUT_DIR/sdcard
		fi
	fi
}

function clean_update
{
	rm -rf $OUTPUT_DIR/sdcard
	rm -rf $OUTPUT_DIR/tftp
	rm -rf $OUTPUT_DIR/bsp_update.tgz
}

# name
PROJECT_NAME=${CHIP}

# absolute path
TOP_DIR=$(gettop)
SCRIPTS_DIR=$TOP_DIR/bootloader-arm64/scripts
OUTPUT_DIR=$TOP_DIR/install/soc_$PROJECT_NAME

DEB_INSTALL_DIR=$OUTPUT_DIR/bsp-debs
PLD_INSTALL_DIR=$OUTPUT_DIR/pld

TFA_SRC_DIR=$TOP_DIR/bootloader-arm64/trusted-firmware-a
FIP_TOOL_DIR=$TFA_SRC_DIR/tools/fiptool
TFA_BUILD_DIR=$TFA_SRC_DIR/build/$PROJECT_NAME/$TFA_TYPE
UBOOT_SRC_DIR=$TOP_DIR/bootloader-arm64/u-boot
UBOOT_BUILD_DIR=$UBOOT_SRC_DIR/build/$PROJECT_NAME

KERNEL_SRC_DIR=$TOP_DIR/linux-arm64
KERNEL_BUILD_DIR=$KERNEL_SRC_DIR/build/$PROJECT_NAME/$KERNEL_VARIANT
RAMDISK_DIR=$TOP_DIR/bootloader-arm64/ramdisk
RAMDISK_BUILD_DIR=$RAMDISK_DIR/build/$PROJECT_NAME

# out-of-tree path
DISTRO_DIR=$TOP_DIR/distro
DISTRO_BASE_PKT=$DISTRO_DIR/distro_$DISTRO.tgz

DISTRO_MOD_DIR=$TOP_DIR/bootloader-arm64/distro
DISTRO_OVERLAY_DIR=$TOP_DIR/bootloader-arm64/distro/overlay

TOOLS_SRC_DIR=$KERNEL_SRC_DIR/tools/bitmain
TOOLS_DST_DIR=$OUTPUT_DIR/bsp-tools
IMAGES_DST_DIR=$OUTPUT_DIR/bsp-images
ROOTFS_DST_DIR=$OUTPUT_DIR/bsp-rootfs

# toolchain
if [ -z $CROSS_COMPILE_64 ]; then
	CROSS_COMPILE_64=$TOP_DIR/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin/aarch64-linux-gnu-
fi
if [ "$CHIP" == "qemu" ]; then
	CROSS_COMPILE_64=aarch64-linux-gnu-
fi
if [ "$(uname -m)" == "aarch64" ]; then
	CROSS_COMPILE_64=
fi

# export
export CROSS_COMPILE=$CROSS_COMPILE_64
GCC_VER=$(${CROSS_COMPILE}gcc --version | grep gcc | sed 's/^.*) //g')

echo "building: $VENDOR $PROJECT_NAME $PRODUCT"
echo "in: $TOP_DIR"
echo "using: $CROSS_COMPILE v$GCC_VER"
echo "with: DEBUG=$DEBUG, KERNEL=$KERNEL_VARIANT"
echo "to: $OUTPUT_DIR"
echo "distro: $DISTRO_BASE_PKT $DISTRO_OVERLAY_DIR"

# include riscv environment
RV_SCRIPT_DIR=$TOP_DIR/bootloader-riscv/scripts
if ([ "$CHIP" == "mango" ] || [ "$CHIP" == "qemu" ]) && [ -f $RV_SCRIPT_DIR/envsetup.sh ]; then
	echo 'import riscv build instructions'
	source $RV_SCRIPT_DIR/envsetup.sh
fi
