#!/bin/bash

# Force PCI to rescan the devices
echo 1 >/sys/bus/pci/rescan
sleep 3

load_mod() {
    local mod="$1"
    /sbin/lsmod | grep -q $(basename $mod .ko) || /sbin/insmod $mod
}

toggle() {
    echo 0 >/sys/class/leds/$1/brightness
    sleep 0.2
    echo 1 >/sys/class/leds/$1/brightness
}

# reset usb hub powers
toggle USB30_HUB_RST
toggle HUB20_PWR_EN

# reset usb host powers
toggle USB30_VCC5V0_EN
toggle USB20_5V_EN

# reset wifi
toggle WIFI_PWR_EN

# reset sata power
sleep 3
toggle SATA_PWR_EN
sleep 3

# reset 4g pwr
toggle 4G_PWR_SW

# reset hdmi and sound
toggle USB30_HDMI_PWR_EN
toggle VCC5V0_AUDIO_EN

# insmod wifi mod
#load_mod /lib/modules/*/kernel/drivers/net/wireless/realtek/rtl8822bu/88x2bu.ko

# insmod fl2000 HDMI display driver mod
#load_mod /lib/modules/*/kernel/drivers/video/fl2000/fl2000.ko

# ec20 would disturb /dev/ttyUSB1, so disable it
if [ -L /etc/systemd/system/multi-user.target.wants/ec20.service ]; then
       systemctl stop ec20.service
       systemctl disable ec20.service
fi
# se7 powerkey monitor
echo "start poweroff button server"
chmod +x /usr/sbin/bm_se7_powerkey_monitor
systemd-run --unit=bm-se7-powerkey-monitor /usr/sbin/bm_se7_powerkey_monitor

echo done

