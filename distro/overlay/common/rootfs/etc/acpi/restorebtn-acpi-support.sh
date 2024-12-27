#!/bin/sh

rm -rf /media/root-rw/*
#rm -rf /media/root-rw/overlay

#tar -zxf /media/root-ro/root/rootfs_rw.tgz -m -C /media/root-rw/
tar -zxf /media/root-rw/.rootfs_rw.tgz -m -C /media/root-rw/

#mkdir -p /media/root-rw/overlay/var/log

echo "restore factory setting key pressed" > /media/root-rw/acpid.log

echo "system will restore factory settting and reboot !!!" >> /media/root-rw/acpid.log

sync

reboot -f 

