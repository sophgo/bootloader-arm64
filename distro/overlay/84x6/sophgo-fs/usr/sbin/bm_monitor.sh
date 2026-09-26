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

# ---- software fault (SE13: Alarm red 1Hz on OOM / kernel hung task) ----
softfault_oom_hold_file=${SCRIPT_DIR}/softfault_oom_hold
softfault_hung_hold_file=${SCRIPT_DIR}/softfault_hung_hold

softfault_oom_hold=60
softfault_hung_hold=60
[ -f "$softfault_oom_hold_file" ]   && read softfault_oom_hold   < "$softfault_oom_hold_file"
[ -f "$softfault_hung_hold_file" ] && read softfault_hung_hold < "$softfault_hung_hold_file"

softfault_state=0      # 0=first run, 1=fault(on), 2=clear(off)
prev_oom_kill=-1
oom_fault_until=0      # epoch seconds until OOM fault hold expires
prev_hung=-1
hung_fault_until=0      # epoch seconds until hung-task fault hold expires
tick=0                  # loop counter, OOM/hung sampled every 5 ticks

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

    # ---- software fault detection (SE13 only) ----
    now=$(date +%s)
    fault=0
    tick=$((tick + 1))

    # OOM/hung sampled every 5 ticks (down-sampled)
    if [ $((tick % 5)) -eq 0 ]; then
        # (a) OOM
        cur_oom=$(awk '/^oom_kill /{print $2}' /proc/vmstat 2>/dev/null)
        if [ -n "$cur_oom" ]; then
            if [ "$prev_oom_kill" -ge 0 ] && [ "$cur_oom" -gt "$prev_oom_kill" ]; then
                oom_fault_until=$((now + softfault_oom_hold))
            fi
            prev_oom_kill=$cur_oom
        fi

        # (b) hung task
        cur_hung=$(dmesg 2>/dev/null | grep -c "blocked for more than")
        if [ "$prev_hung" -ge 0 ] && [ "$cur_hung" -gt "$prev_hung" ]; then
            hung_fault_until=$((now + softfault_hung_hold))
        fi
        prev_hung=$cur_hung
    fi
    [ "$now" -lt "$oom_fault_until" ] && fault=1
    [ "$now" -lt "$hung_fault_until" ] && fault=1

    if [ "$fault" -eq 1 ] && [ "$softfault_state" -ne 1 ]; then
        ( echo "software_fault on" ) | telnet 127.0.0.1 $s_port &>temp.log
        grep -q "Connected to" temp.log && softfault_state=1
    elif [ "$fault" -eq 0 ] && [ "$softfault_state" -eq 1 ]; then
        ( echo "software_fault off" ) | telnet 127.0.0.1 $s_port &>temp.log
        grep -q "Connected to" temp.log && softfault_state=2
    fi

    sleep 1
done
