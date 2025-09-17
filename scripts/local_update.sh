#!/bin/bash

# this is se6 ota update script
if [ $# -lt 1  ] ; then
        echo "need md5 file"
        exit 1
fi

read_partition_config() {
    local xml_file="partition32G.xml"

    if [ ! -f "$xml_file" ]; then
        echo "ERROR: Partition configuration file $xml_file not found!"
        return 1
    fi

    declare -gA expected_sizes
    expected_sizes=()

    while IFS= read -r line; do
        partition_label=$(echo "$line" | grep -o 'label="[^"]*"' | awk -F'"' '{print $2}')
        size_kb=$(echo "$line" | grep -o 'size_in_kb="[^"]*"' | awk -F'"' '{print $2}')

        if [ -n "$partition_label" ] && [ -n "$size_kb" ]; then
            if [ "$partition_label" != "DATA" ]; then
                expected_sizes["$partition_label"]="$size_kb"
                echo "DEBUG: Found partition $partition_label with size $size_kb KB"
            else
                echo "DEBUG: Skipping DATA partition check"
            fi
        fi
    done < <(grep '<partition' "$xml_file")

    if [ ${#expected_sizes[@]} -eq 0 ]; then
        echo "ERROR: No partition configurations found in $xml_file"
        return 1
    fi

    declare -gA partition_mapping=(
        ["BOOT"]="mmcblk0p1"
        ["RECOVERY"]="mmcblk0p2"
        ["MISC"]="mmcblk0p3"
        ["ROOTFS"]="mmcblk0p4"
        ["ROOTFS_RW"]="mmcblk0p5"
    )

    return 0
}

check_partition_sizes() {
    echo ">>>>>Checking partition sizes (excluding DATA partition)..."

    if ! read_partition_config; then
        return 1
    fi

    local all_match=true

    for partition_label in "${!expected_sizes[@]}"; do
        expected_size=${expected_sizes[$partition_label]}
        device_node=${partition_mapping[$partition_label]}

        if [ -z "$device_node" ]; then
            echo "WARNING: No device mapping found for partition label: $partition_label"
            continue
        fi

        actual_size=$(grep "$device_node" /proc/partitions | awk '{print $3}')

        if [ -z "$actual_size" ]; then
            echo "ERROR: Partition $partition_label ($device_node) not found!"
            all_match=false
            continue
        fi

        if [ "$actual_size" -ne "$expected_size" ]; then
            echo "ERROR: Partition $partition_label ($device_node) size mismatch!"
            echo "  Expected: $expected_size blocks"
            echo "  Actual: $actual_size blocks"
            all_match=false
        else
            echo "Partition $partition_label ($device_node): OK (${actual_size} blocks)"
        fi
    done

    if $all_match; then
        echo ">>>>>All partition sizes (excluding DATA) match expected values."
        return 0
    else
        echo ">>>>>Partition size check failed!"
        return 1
    fi
}

echo ">>>>>start upgrade app package..."

echo ">>>>>md5sum check ..."

basepath=$(cd `dirname $0`; pwd)
echo $basepath
cd $basepath

md5sum -c $1 > ota_versino.txt
ret=$?
count=$#
rootpath="/data/ota"

if ! check_partition_sizes; then
    echo ">>>>> Partition size mismatch! Stop upgrade..."
    echo "update failed"
    exit 1
fi

if [ $ret -ne 0 ]; then
    echo ">>>>> upgrade package is wrong stop upgrade..."
    echo "update failed"
    exit 1
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
    sudo dd if=/dev/zero of=/dev/mmcblk0p3 bs=512 count=1
    if [ $# -ge 2 ]; then
        echo -e "boot-recovery\n/DATA/ota\n$2" > /dev/mmcblk0p3
    else
        echo -e "boot-recovery\n/DATA/ota" > /dev/mmcblk0p3
    fi
    echo "update success"
    sync
    reboot
fi
