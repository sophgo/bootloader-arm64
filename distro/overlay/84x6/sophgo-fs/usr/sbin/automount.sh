#!/bin/bash

logger_file() {
    logger -i "(automount.sh)LOG:[$1]"
    # echo "(automount.sh)LOG:[$1]" | tee -a /data/auto.log
}

rm_log() {
    logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} rm_log of [$1] successful"
    rm -rf $1
}

automount() {
    name="`basename "$DEVNAME"`"
    d_path=`udevadm info -n $name -q path`
    logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} d_path: $d_path"
    removable=$(
        udevadm info --attribute-walk --path=$(
            udevadm info --query=path --name=${DEVNAME} 2>/dev/null
        ) 2>/dev/null | grep -m 1 '{removable}' | awk -F'"' '{print $2}'
    )
    logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} device ${name} -> removable: $removable"

    if [[ "${removable}" == "0" ]]; then
        mount_dir="/media/storage-local-$name"
    else
        mount_dir="/media/storage-hot-$name"
    fi

    # If filesystem type is vfat, change the ownership group to 'disk', and
    # grant it with  w/r/x permissions.
    case $ID_FS_TYPE in
        vfat|fat|ext4|ext3|ext2|xfs)
            #MOUNT="$MOUNT -o umask=007,gid=`awk -F':' '/^disk/{print $3}' /etc/group`"
            #if ! $MOUNT -t auto -o iocharset=cp936 $DEVNAME $mount_dir
            ! test -d $mount_dir && mkdir -p $mount_dir
            if ! $MOUNT -t auto $DEVNAME $mount_dir
            then
                logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} $MOUNT -t auto $DEVNAME $mount_dir failed!"
                rm_log "$mount_dir"
            else
                logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} Auto-mount of [$mount_dir] successful"
                touch "/tmp/.automount-$name"
            fi
            ;;
        *)
            logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} device ${name} \
cannot support FS_TYPE: ${ID_FS_TYPE}"
            ;;
    esac
}

autoumount() {
    name="`basename "$DEVNAME"`"
    logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} autoumount DEVNAME:$DEVNAME name:$name"
    while [[ "$(cat /proc/mounts | grep "^${DEVNAME} " | wc -l)" != "0" ]]
    do
        umount_dir="$(cat /proc/mounts | grep -m 1 "^$DEVNAME " | awk '{print $2}')"
        logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} autoumount umount_dir:$umount_dir"
        if ! $UMOUNT "${umount_dir}"
        then
            logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} $UMOUNT ${umount_dir} failed!"
        else
            logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} $UMOUNT ${umount_dir} successful!"
            rm_log "${umount_dir}"
        fi
    done
    if [ -f "/tmp/.automount-$name" ]; then
        rm_log "/tmp/.automount-$name"
    fi
}

MOUNT="/bin/mount"
UMOUNT="/bin/umount"
name="`basename "$DEVNAME"`"
logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} sophgo auto mount start, DEVNAME: $DEVNAME name: $name"

if [ "$ACTION" = "add" ] && [ -x "$MOUNT" ] && [ -n "$DEVNAME" ] ; then
    name="`basename "$DEVNAME"`"
    symlink_file=$(ls -l /dev | grep " \-> ${name}\$" | awk '{print $(NF-2)}')
    logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} ADD: $DEVNAME $name $symlink_file"
    # mount info from fstab
    if [ -x $MOUNT ]; then
        $MOUNT $DEVNAME 2> /dev/null
    fi
    if [ -x $MOUNT ] && [ -n "$symlink_file" ]; then
        grep -q "^$DEVNAME " /proc/mounts || $MOUNT /dev/$symlink_file 2> /dev/null
    fi

    # If the device isn't mounted at this point, it isn't
    # configured in fstab (note the root filesystem can show up as
    # /dev/root in /proc/mounts, so check the device number too)
    if expr $MAJOR "*" 256 + $MINOR != `stat -c %d /`; then
        grep -q "^$DEVNAME " /proc/mounts || automount
    fi
elif [ "$ACTION" = "remove" ] && [ -x "$UMOUNT" ] && [ -n "$DEVNAME" ]; then
    # Remove empty directories from auto-mounter
    name="`basename "$DEVNAME"`"
    logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} REMOVE: $DEVNAME $name"
    autoumount
fi

logger_file "${FUNCNAME[1]} ${BASH_SOURCE[1]} ${LINENO} sophgo auto mount end, DEVNAME: $DEVNAME name: $name"
