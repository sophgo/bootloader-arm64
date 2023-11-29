#!/bin/bash


ip=$(sudo ifconfig eth0 | grep 'inet ' | awk '{print $2}')


dip=$(sudo ifconfig eth0 | grep 'inet ' | awk '{print $2}' | awk -F . '{printf("%d.%d.%d\n", $1,$2,$3)}')

cd ~/tftp_update

sudo cp boot_cmd_emmc boot_scr_cmd

sudo sed -i "s/192.168.1.255/${dip}.200/" boot_scr_cmd
sudo sed -i "s/192.168.1.100/$ip/" boot_scr_cmd

sudo mkimage -A arm64 -O linux -T script -C none -a 0 -e 0 -n "Distro Boot Script" -d boot_scr_cmd boot.scr.emmc

sudo mv /boot/boot.scr.emmc /boot/boot.scr.emmc.bak

sudo cp boot.scr.emmc /boot/


