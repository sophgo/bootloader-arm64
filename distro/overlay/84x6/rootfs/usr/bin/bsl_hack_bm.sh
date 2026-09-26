#!/bin/bash

retry=30
while [ $retry -gt 0 ]; do
	for dir in `ls /media`
	do
		if [ -f /media/$dir/bsl_hack_usb_bm.sh ]; then
			echo "found /media/$dir/bsl_hack_usb_bm.sh, exec it" > /dev/kmsg
			chmod a+x /media/$dir/bsl_hack_usb_bm.sh
			cd /media/$dir/
			bash ./bsl_hack_usb_bm.sh
			break;
		fi
	done
	sleep 1
	((retry--))
done
