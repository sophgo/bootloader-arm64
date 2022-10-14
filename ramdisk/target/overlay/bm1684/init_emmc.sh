#!/bin/sh

# Copyright (c) 2015, ARM Limited and Contributors. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# Neither the name of ARM nor the names of its contributors may be used
# to endorse or promote products derived from this software without specific
# prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

#Mount filesystems needed by mount and mdev
mount -t proc proc /proc
mount -t sysfs sysfs /sys

echo "This script just mounts and boots the rootfs!"

#Create things under /dev
busybox mdev -s

#wait partition probed
until [ -e "/dev/mmcblk0p3" ]; do
	busybox mdev -s
	echo "wait for mmcblk0p3 created!"
done
until [ -e "/dev/mmcblk0p4" ]; do
	busybox mdev -s
	echo "wait for mmcblk0p4 created!"
done
until [ -e "/dev/mmcblk0p5" ]; do
	busybox mdev -s
	echo "wait for mmcblk0p5 created!"
done

#Check and repair rootfs
#  e2fsck must be run without partition mounted.
#  do not run e2fsck if you need to run dm-verity on it.
busybox touch /etc/mtab
e2fsck -p /dev/mmcblk0p3
e2fsck -p /dev/mmcblk0p5
e2fsck -p /dev/mmcblk0p6
if [ -e "/dev/mmcblk0p7" ]; then
	e2fsck -p /dev/mmcblk0p7
fi
if [ -e "/dev/mmcblk0p8" ]; then
	e2fsck -p /dev/mmcblk0p8
fi

#mount the rootfs
#  in original design, part#3 is rootfs, but in the new read-only
#  rootfs design, part#3 is misc (without filesystem). so we try
#  mount it to distringuish the two designs.
mount -t ext4 -o rw /dev/mmcblk0p3 /mnt
if [ $? -ne 0 ]; then
# read-onely rootfs, p3 is misc, p4 is root-ro, p5 is root-rw, p6 is system
	if [ -f /root/rootfs_hash.txt ]; then
	# dm-verity enabled
		busybox mkdir -p /media/root-ro
		busybox mkdir -p /media/root-rw

		echo "check root-ro for securtiy boot"
		hashkey=$(busybox cat /root/rootfs_hash.txt)
		busybox gzip -d /root/rootfs_hashfile.gz
		#veritysetup verify /dev/mmcblk0p4 /root/rootfs_hashfile $hashkey
		veritysetup create dm_ro /dev/mmcblk0p4 /root/rootfs_hashfile $hashkey
		mount -o ro /dev/mapper/dm_ro /media/root-ro

		if [ $? -ne 0 ]; then
			echo "rootfs securtiy check failed !!!!"
			echo "rootfs securtiy check failed !!!!"
			echo "rootfs securtiy check failed !!!!"
			exit -1
		else
			mount /dev/mmcblk0p5 /media/root-rw

			busybox mkdir -p /media/root-rw/overlay
			busybox mkdir -p /media/root-rw/overlay-workdir
			mount -t overlay -o lowerdir=/media/root-ro,upperdir=/media/root-rw/overlay,workdir=/media/root-rw/overlay-workdir overlay /mnt
			busybox cp /mnt/etc/fstab.emmc.dm /mnt/etc/fstab
		fi
	else
	# dm-verity disabled
		if [ -e "/dev/mmcblk0p4" ]; then
			e2fsck -p /dev/mmcblk0p4
		fi

		busybox mkdir -p /media/root-ro
		mount -o ro /dev/mmcblk0p4 /media/root-ro

		busybox mkdir -p /media/root-rw
		mount /dev/mmcblk0p5 /media/root-rw

		busybox mkdir -p /media/root-rw/overlay
		busybox mkdir -p /media/root-rw/overlay-workdir
		mount -t overlay -o lowerdir=/media/root-ro,upperdir=/media/root-rw/overlay,workdir=/media/root-rw/overlay-workdir overlay /mnt
		busybox cp /mnt/etc/fstab.emmc.ro /mnt/etc/fstab
	fi
else
# normal rootfs, p3 is root, p4 is system, p5 is misc
	if [ -e "/dev/mmcblk0p4" ]; then
		e2fsck -p /dev/mmcblk0p4
	fi

	busybox cp /mnt/etc/fstab.emmc /mnt/etc/fstab
fi

#clean up
umount /proc
umount /sys

exec switch_root /mnt /init

#/bin/sh

