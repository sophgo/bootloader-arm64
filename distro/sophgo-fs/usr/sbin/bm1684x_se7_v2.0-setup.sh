#!/bin/bash

function temp_scan()
{
    stage=0
    set_stage_0_down() {
        echo "set_stage_0_down"
        # VTPU
        pmbus -d 0 -s 0x50 -b 0x0 -v 0x0
        pmbus -d 0 -s 0x50 -w 0x21 -v 0x370
        sleep 0.1
        echo "setr tpll_clock 950000000" > /sys/kernel/debug/top/clock
        echo "setr vpll_clock 800000000" > /sys/kernel/debug/top/clock
        echo "setr mpll_clock 2300000000" > /sys/kernel/debug/top/clock
    }
    set_stage_1_down() {
        echo "set_stage_1_down"
        # VTPU
        pmbus -d 0 -s 0x50 -b 0x0 -v 0x0
        pmbus -d 0 -s 0x50 -w 0x21 -v 0x2E4
        sleep 0.1
        echo "setr tpll_clock 712500000" > /sys/kernel/debug/top/clock
        echo "setr vpll_clock 800000000" > /sys/kernel/debug/top/clock
        echo "setr mpll_clock 2300000000" > /sys/kernel/debug/top/clock
    }
    set_stage_1_up() {
        echo "set_stage_1_up"
        echo "setr tpll_clock 712500000" > /sys/kernel/debug/top/clock
        echo "setr vpll_clock 800000000" > /sys/kernel/debug/top/clock
        echo "setr mpll_clock 2300000000" > /sys/kernel/debug/top/clock
        sleep 0.1
        # VTPU
        pmbus -d 0 -s 0x50 -b 0x0 -v 0x0
        pmbus -d 0 -s 0x50 -w 0x21 -v 0x2E4
    }
    set_stage_2_down() {
        echo "set_stage_2_down"
        # VTPU
        pmbus -d 0 -s 0x50 -b 0x0 -v 0x0
        pmbus -d 0 -s 0x50 -w 0x21 -v 0x2E4
        sleep 0.1
        echo "setr tpll_clock 500000000" > /sys/kernel/debug/top/clock
        echo "setr vpll_clock 640000000" > /sys/kernel/debug/top/clock
        echo "setr mpll_clock 1800000000" > /sys/kernel/debug/top/clock
    }
    set_stage_2_up() {
        echo "set_stage_2_up"
        echo "setr tpll_clock 500000000" > /sys/kernel/debug/top/clock
        echo "setr vpll_clock 640000000" > /sys/kernel/debug/top/clock
        echo "setr mpll_clock 1800000000" > /sys/kernel/debug/top/clock
        sleep 0.1
        # VTPU
        pmbus -d 0 -s 0x50 -b 0x0 -v 0x0
        pmbus -d 0 -s 0x50 -w 0x21 -v 0x2E4
    }
    set_stage_3_down() {
        echo "set_stage_3_down"
        # VTPU
        pmbus -d 0 -s 0x50 -b 0x0 -v 0x0
        pmbus -d 0 -s 0x50 -w 0x21 -v 0x26c
        sleep 0.1
        echo "setr tpll_clock 25000000" > /sys/kernel/debug/top/clock
        echo "setr vpll_clock 640000000" > /sys/kernel/debug/top/clock
        echo "setr mpll_clock 1800000000" > /sys/kernel/debug/top/clock
    }
    set_stage_3_up() {
        echo "set_stage_3_up"
        echo "setr tpll_clock 25000000" > /sys/kernel/debug/top/clock
        echo "setr vpll_clock 640000000" > /sys/kernel/debug/top/clock
        echo "setr mpll_clock 1800000000" > /sys/kernel/debug/top/clock
        sleep 0.1
        # VTPU
        pmbus -d 0 -s 0x50 -b 0x0 -v 0x0
        pmbus -d 0 -s 0x50 -w 0x21 -v 0x26c
    }
    set_stage_4_up() {
        echo "set_stage_4_up"
        poweroff --force
    }
    while true; do
        temp_output=$(bm_get_temperature)
        chip_temp=$(echo $temp_output | awk -F'; ' '{print $2}' | grep -oP '\d+')
        max_t=$chip_temp
        case $stage in
            0)
                if [ $max_t -ge 85 ];then
                    stage=1
                    set_stage_1_up;
                else
                    stage=0
                fi
                ;;
            1)
                if [ $max_t -ge 95 ];then
                    stage=2
                    set_stage_2_up
                elif [ $max_t -le 80 ];then
                    stage=0
                    set_stage_0_down
                else
                    stage=1
                fi
                ;;
            2)
                if [ $max_t -ge 105 ];then
                    stage=3
                    set_stage_3_up
                elif [ $max_t -le 90 ];then
                    stage=1
                    set_stage_1_down
                else
                    stage=2
                fi
                ;;
            3)
                if [ $max_t -le 100 ];then
                    stage=2
                    set_stage_2_down
                else
                    stage=3
                    echo chip_temp:$chip_temp
                fi
                ;;
            esac
    sleep 5
    done
}

fun_str=$(declare -f temp_scan | gzip -c - | base64)

# systemctl stop bm-se7-v20-scan-temperature.service
# systemctl reset-failed bm-se7-v20-scan-temperature.service


systemd-run --unit=bm-se7-v20-scan-temperature /usr/bin/bash -c \
"source /dev/stdin <<< \$(echo \"$fun_str\" | base64 -d | gzip -d -c -); while true; do temp_scan; sleep 5; done"
systemctl status bm-se7-v20-scan-temperature.service
