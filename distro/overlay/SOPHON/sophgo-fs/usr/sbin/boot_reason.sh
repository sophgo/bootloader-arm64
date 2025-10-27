#!/bin/bash

OUTPUT_FILE="/root/.boot_reason"

REG_ADDR="0x050260F8"

REG_VALUE=$(busybox devmem $REG_ADDR 2>/dev/null)
if [ -z "$REG_VALUE" ]; then
    echo "无法读取寄存器 $REG_ADDR" >> $OUTPUT_FILE
    exit 1
fi

REG_DEC=$((REG_VALUE))

STATE_BITS=$((REG_DEC & 0x7))
case $STATE_BITS in
    0) STATE_REASON="由断电返回到上电状态" ;;
    3) STATE_REASON="由Power-cycle或Warm-reset回到上电状态" ;;
    9) STATE_REASON="由休眠回到上电状态" ;;
    *) STATE_REASON="未知状态 (0x$(printf '%X' $STATE_BITS))" ;;
esac

TRIGGER_BITS=$(((REG_DEC >> 16) & 0xFFFF))
REASONS=()

(( TRIGGER_BITS & 0x0004 )) && REASONS+=("RTC_EN_AUTO_POWER_UP(断电重启)")
(( TRIGGER_BITS & 0x0100 )) && REASONS+=("REQ_PWR_CYC(Power-cycle触发重启)")
(( TRIGGER_BITS & 0x0400 )) && REASONS+=("REQ_WARM_RST(Warm-reset触发重启)")
(( TRIGGER_BITS & 0x0800 )) && REASONS+=("REQ_WDG_RST(看门狗触发重启)")
(( TRIGGER_BITS & 0x4000 )) && REASONS+=("REQ_WAKEUP(事件唤醒)")

if [ ${#REASONS[@]} -eq 0 ]; then
    REASONS+=("none")
fi

{
    echo "time: $(date)"
    echo "$STATE_REASON"
    for reason in "${REASONS[@]}"; do
        echo "reboot reason: $reason"
    done
    echo ""
} >> "$OUTPUT_FILE"

