#!/bin/bash

chip_temp_alarm_defaut=80000
s_port=3456
SCRIPT=$(readlink -f "$0")
SCRIPT_DIR=$(dirname "$SCRIPT")
temp_alarm_file=${SCRIPT_DIR}/temp_alarm

# 0 for fist run this script
# 1 for ssd normal state
# 2 for ssd not present
# 3 for ssd mount failed
ssd_state=0
# 0 for fist run this script
# 1 for alarm temperature
# 2 for normal temperature
chip_temp_state=0

while true; do
    if [ ! -f "$temp_alarm_file" ]; then
        chip_temp_alarm=$chip_temp_alarm_defaut
    else
        chip_temp_alarm=$(cat $temp_alarm_file)
        if [ -z "$chip_temp_alarm" ]; then
            chip_temp_alarm=$chip_temp_alarm_defaut
        fi
        if ! [[ "$chip_temp_alarm" =~ ^[0-9]+$ ]]; then
            chip_temp_alarm=$chip_temp_alarm_defaut
        fi
    fi

    chip_temp_alarm=$(expr $chip_temp_alarm / 1000)

    chip=$(cat /sys/class/thermal/thermal_zone0/temp)
    chip_temp=$(expr $chip / 1000)

    if [ $chip_temp -gt $chip_temp_alarm ] && [ $chip_temp_state -ne 1 ]; then
        (
            echo "temperature on"
        ) | telnet 127.0.0.1 $s_port &>temp.log
        grep "Connected to" temp.log
        if [ $? -eq 0 ]; then
            chip_temp_state=1
        fi
    elif [ $chip_temp -le $((chip_temp_alarm - 5)) ] && [ $chip_temp_state -ne 2 ]; then
        (
            echo "temperature off"
        ) | telnet 127.0.0.1 $s_port &>temp.log
        grep "Connected to" temp.log
        if [ $? -eq 0 ]; then
            chip_temp_state=2
        fi
    fi

    if busybox lsscsi | grep -q "ATA"; then
        if df -h | grep -q "sda"; then
            if [ $ssd_state -ne 1 ]; then
                (
                    echo "ssd normal state"
                    sleep 0.1
                ) | telnet 127.0.0.1 $s_port &>temp.log
                grep "Connected to" temp.log
                if [ $? -eq 0 ]; then
                    ssd_state=1
                fi
            fi
        else
            (
                echo "ssd mount failed"
                sleep 0.1
            ) | telnet 127.0.0.1 $s_port &>temp.log
            grep "Connected to" temp.log
            if [ $? -eq 0 ]; then
                ssd_state=3
            fi
        fi
    elif [ $ssd_state -ne 2 ]; then
        (
            echo "ssd not present"
            sleep 0.1
        ) | telnet 127.0.0.1 $s_port &>temp.log
        grep "Connected to" temp.log
        if [ $? -eq 0 ]; then
            ssd_state=2
        fi
    fi

    stat=$(busybox devmem 0x0502601c)
    stat_bit0=$((stat & 0x1))
    stat_bit1=$(( (stat & 0x2) >> 1 ))
    if [ "$stat_bit0" -eq 1 ]; then
        busybox devmem 0x0502601c 32 $(($(busybox devmem 0x0502601c) &~ 0x1))
        /etc/acpi/powerbtn-acpi-support.sh
    fi
    if [ "$stat_bit1" -eq 1 ]; then
        busybox devmem 0x0502601c 32 $(($(busybox devmem 0x0502601c) &~ 0x2))
        /etc/acpi/restorebtn-acpi-support.sh
    fi

    sleep 1
done
