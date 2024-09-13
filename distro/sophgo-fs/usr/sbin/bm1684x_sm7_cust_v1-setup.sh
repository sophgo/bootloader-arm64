#!/bin/bash

systemctl stop ledSocketServer.service
systemctl disable ledSocketServer.service

systemctl stop SophonHDMIStatus.service
systemctl stop SophonHDMI.service
systemctl disable SophonHDMIStatus.service
systemctl disable SophonHDMI.service

sleep 0.2
echo 1 > /sys/class/leds/RUN_STATUS/brightness

function sata_led_scan()
{
	temp_file_mount_flag=$(mktemp)
	temp_file_led_status=$(mktemp)
	trap 'rm -f "$temp_file_mount_flag"; rm -f "$temp_file_led_status"' EXIT
	echo 0 > "$temp_file_mount_flag"
	echo 0 > "$temp_file_led_status"

	SATA_PATH="5fb80000.pcie/pci0000:00/0000:00:00.0/0000:01:00.0/usb2/2-1/2-1:1.0"

	lsblk | grep -vE "^├─|^└─|^mmcblk|^NAME" | awk '{print $1}' | while read -r line; do
		if [[ "$mount_flag" != "0" ]]; then
			remove_flag=$(cat /sys/block/$line/removable)
			if [[ "$remove_flag" == "0" ]]; then
				sata_path=$(udevadm info --query=path --name=/dev/$line)
				if [[ "$sata_path" == *"$SATA_PATH"* ]]; then
					echo 0 > "$temp_file_mount_flag"
					lsblk | grep "$line" | awk '{print $7}' | while read -r mount_line; do
						if [[ "$mount_line" != "" ]]; then
							echo 1 > $temp_file_mount_flag
						fi
					done
					mount_flag=$(cat $temp_file_mount_flag)
					if [[ "$mount_flag" == "1" ]]; then
						echo 1 > $temp_file_led_status;
						break;
					fi
				fi
			fi
		fi
	done

	leds=$(cat $temp_file_led_status);
	rm -f "$temp_file_mount_flag";
	rm -f "$temp_file_led_status";
	les_old=$(cat /sys/class/leds/SATA_STATUS/brightness);
	if [[ "$les_old" != "$leds" ]]; then
		date;
		echo "SATA LED: $les_old -> $leds";
	fi
	echo $leds > /sys/class/leds/SATA_STATUS/brightness;
}

fun_str=$(declare -f sata_led_scan | gzip -c - | base64)

# systemctl stop bm-sm7-custv1-scan-sata.service
# systemctl reset-failed bm-sm7-custv1-scan-sata.service

systemd-run --unit=bm-sm7-custv1-scan-sata /usr/bin/bash -c \
"source /dev/stdin <<< \$(echo \"$fun_str\" | base64 -d | gzip -d -c -); while true; do sata_led_scan; sleep 5; done"
systemctl status bm-sm7-custv1-scan-sata.service
