#!/bin/bash

USB_MOUNT_DIR=/data2
OTA_DIR=/data/ota
MOUNT_POINT=$(df -P "$USB_MOUNT_DIR" | awk 'NR==2 {print $1}')

# check usb mounted or not
if [ -d "$USB_MOUNT_DIR" ] && [ "$MOUNT_POINT" != "overlay" ]; then
    echo "USB already mounted at $USB_MOUNT_DIR"
	echo "MOUNT_POINT: $MOUNT_POINT"
	UPDATE_FILES=$(awk '{print $2}' $USB_MOUNT_DIR/md5.txt)

	pushd $USB_MOUNT_DIR
    # check update file
	md5sum -c md5.txt > ota_versino.txt
	ret=$?
	if [ $ret -ne 0 ]; then
		popd
		exit -1
    else
		echo "doing copy operation ..."
		cp md5.txt $OTA_DIR
		cp $UPDATE_FILES $OTA_DIR
		sync
		echo "finished copy operation"
		pushd $OTA_DIR
		./local_update.sh md5.txt
    fi
else
    echo "No USB device is mounted"
	echo "MOUNT_POINT: $MOUNT_POINT"
fi

