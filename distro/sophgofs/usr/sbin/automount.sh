#!/bin/bash

logger "-----bitmain auto mount----------------"
MOUNT="/bin/mount"
UMOUNT="/bin/umount"

#for line in `grep -v ^# /etc/udev/mount.blacklist`
#do
#	name="`basename "$DEVNAME"`"
#	if [ ` expr match "$DEVNAME" "$line" ` -gt 0 ] || [ ` expr match "$name" "$line" ` -gt 0 ]
#	then
#		logger "udev/mount.sh" "[$DEVNAME] is blacklisted, ignoring"
#		exit 0
#	fi
#done

automount() {
	name="`basename "$DEVNAME"`"
	d_path=`udevadm info -n $name -q path`
	echo "d_path: $d_path"

	if [[ $name =~ sd ]]
	then
		if [[ $d_path =~ "usb2/2-2" ]]
		then
			mount_dir="/data2"
		else
			mount_dir="/media/usb-$name"
		fi
		! test -d $mount_dir && mkdir -p $mount_dir
	fi

	# If filesystem type is vfat, change the ownership group to 'disk', and
	# grant it with  w/r/x permissions.
	case $ID_FS_TYPE in
		vfat|fat|ext4|ext3|ext2)
			#MOUNT="$MOUNT -o umask=007,gid=`awk -F':' '/^disk/{print $3}' /etc/group`"
			#if ! $MOUNT -t auto -o iocharset=cp936 $DEVNAME $mount_dir
			if ! $MOUNT -t auto $DEVNAME $mount_dir
			then
				logger "mount.sh/automount" "$MOUNT -t auto $DEVNAME $mount_dir failed!"
			else
				logger "mount.sh/automount" "Auto-mount of [ $mount_dir] successful"
				touch "/tmp/.automount-$name"
			fi
			;;
			# TODO
			*)
			;;
	esac
}

autoumount() {
	name="`basename "$DEVNAME"`"
	d_path=`udevadm info -n $name -q path`
	#echo "d_path: $d_path"

	for mnt in `cat /proc/mounts | grep "$DEVNAME" | cut -f 2 -d " " `
	do
		$UMOUNT $mnt
	done

	if [[ $name =~ sd ]]
	then
		if [[ $d_path =~ "usb2/2-2" ]]
		then
			mount_dir="/data2"
			logger "mount.sh/autoumount" "Auto-umount of [ $mount_dir] successful"
		else
			mount_dir="/media/usb-$name"
			logger "mount.sh/autoumount" "Auto-umount of [ $mount_dir] successful"
			test -e $mount_dir && rm_dir $mount_dir
		fi
	fi
}

rm_dir() {
	logger "rm_dir of [ $1] successful"
	rm -rf $1
}

name="`basename "$DEVNAME"`"

if [ "$ACTION" = "add" ] && [ -n "$DEVNAME" ] ; then
	logger "-------$name--ADD------------"
	if [ -x $MOUNT ]; then
		$MOUNT $DEVNAME 2> /dev/null
	fi

	# If the device isn't mounted at this point, it isn't
	# configured in fstab (note the root filesystem can show up as
	# /dev/root in /proc/mounts, so check the device number too)
	if expr $MAJOR "*" 256 + $MINOR != `stat -c %d /`; then
		grep -q "^$DEVNAME " /proc/mounts || automount
	fi
fi

if [ "$ACTION" = "remove" ] && [ -x "$UMOUNT" ] && [ -n "$DEVNAME" ]; then
	logger "-------$name--REMOVE------------"
	# Remove empty directories from auto-mounter
	name="`basename "$DEVNAME"`"
	autoumount
fi
