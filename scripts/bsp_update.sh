#!/bin/bash

echo update BSP iamges, please do not power off board
read -n 1 -s -r -p "Press any key to continue"
echo
echo

md5sum -c ./md5.txt
ret=$?
if [ $ret -ne 0 ]; then
	echo file md5 mismatch, please check
	return $ret
fi

mkdir backup
cp /boot/emmcboot.itb ./backup/
cp /boot/boot.scr.emmc ./backup/
cp /boot/multi.its ./backup/
if [ -e /sbin/flash_update ]; then
	sudo mv /sbin/flash_update ./backup/
	sudo cp ./flash_update /usr/sbin/
fi
cd ./backup
sudo flash_update -d spi_flash_dump.bin -b 0x6000000 -o 0 -l 0x200000
md5sum * > md5.txt
cd ..

sudo cp /boot/emmcboot.itb /boot/emmcboot.itb.bak
sudo cp /boot/boot.scr.emmc /boot/boot.scr.emmc.bak
if [ -e /boot/multi.its ]; then
	sudo cp /boot/multi.its /boot/multi.its.bak
fi
if [ -e /boot/spi_flash.bin ]; then
	sudo cp /boot/spi_flash.bin /boot/spi_flash.bin.bak
fi

sudo cp ./emmcboot.itb /boot/
sudo cp ./boot.scr.emmc /boot/
sudo cp ./multi.its /boot/
sudo cp ./spi_flash.bin /boot/
sudo mkdir -p /lib/firmware
latest=$(ls -dr /system/data/bm1684x.bin* 2>/dev/null | head -n 1)
if [ -n \"$latest\" ]; then
	ln -s $latest /lib/firmware/bm1684x_firmware.bin;
fi
latest=$(ls -dr /system/data/bm1684_ddr.bin* 2>/dev/null | head -n 1)
if [ -n \"$latest\" ]; then
	ln -s $latest /lib/firmware/bm1684_ddr_firmware.bin;
fi
latest=$(ls -dr /system/data/bm1684_tcm.bin* 2>/dev/null | head -n 1)
if [ -n \"$latest\" ]; then
	ln -s $latest /lib/firmware/bm1684_tcm_firmware.bin;
fi
sync
sudo flash_update -i spi_flash.bin -b 0x6000000

echo
echo
echo all done, please run \'sudo reboot\'
