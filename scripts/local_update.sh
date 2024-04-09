#!/bin/bash

# this is se6 ota update script
if [ $# -lt 1  ] ; then
        echo "need md5 file"
        exit
fi
echo ">>>>>start upgrade app package..."

echo ">>>>>md5sum check ..."

basepath=$(cd `dirname $0`; pwd)
echo $basepath
cd $basepath

md5sum -c $1 > ota_versino.txt
ret=$?
count=$#
rootpath="/data/ota"
if [ $ret -ne 0 ]; then
    echo ">>>>> upgrade package is wrong stop upgrade..."
    echo "update failed"
else
    echo ">>>>>upgrade package starting..."
    # backup user information
    echo ">>>>>backup user information..."
    rm -rf ${rootpath}/public_ota/backup
    mkdir -p ${rootpath}/public_ota/backup
    # update boot-loader
    #sudo flash_update -i spi_flash.bin -b 0x06000000 -f 0x0
    #sudo flash_update -i fip.bin -b 0x6000000 -f 0x40000
    # upgrade mcu
    #sudo mcu-util-aarch64 upgrade 1 0x17 sa5-mcu*.bin

    # private ota :boot-recovery /data/ota/startup.sh\nprivate_update"
    echo -e "boot-recovery\n/DATA/ota" > /dev/mmcblk0p3
    echo "update success"

    reboot
fi

