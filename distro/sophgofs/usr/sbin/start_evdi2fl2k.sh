#!/bin/bash
if ! modprobe evdi; then
        echo 'evdi kernel module not found' 1>&2
        exit 1
fi

systemctl stop SophonHDMI
systemctl disable SophonHDMI
systemctl stop SophonHDMIStatus
systemctl disable SophonHDMIStatus

if ! ./evdi2fl2k; then
        if [ -f /usr/bin/Xorg ]; then
                /usr/bin/Xorg &
        else
                echo "Xorg not found!"
                exit 1
        fi
        sleep 1s
fi

systemctl restart display-manager 2>&1
echo 'start feeding data to fl2000'
./evdi2fl2k &



