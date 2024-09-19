#!/bin/bash
function load_ko()
{
	if [ -f /opt/sophon/libsophon-current/data/bmtpu.ko ]; then
		sudo mkdir -p /lib/firmware
		ln -s /opt/sophon/libsophon-current/data/bm1688_firmware0.bin \
			/lib/firmware/bm1688_firmware0.bin
		ln -s /opt/sophon/libsophon-current/data/bm1688_firmware1.bin \
			/lib/firmware/bm1688_firmware1.bin
		ln -s /opt/sophon/libsophon-current/data/bm1688_firmware0_os.bin \
			/lib/firmware/bm1688_firmware0_os.bin
		ln -s /opt/sophon/libsophon-current/data/bm1688_firmware1_os.bin \
			/lib/firmware/bm1688_firmware1_os.bin
		ln -s /opt/sophon/libsophon-current/lib/tpu_module/libbm1688_kernel_module.so \
			/lib/firmware/libbm1688_kernel_module.so
		insmod /opt/sophon/libsophon-current/data/bmtpu.ko
	fi

	if [ -f /opt/sophon/libsophon-current/data/load.sh ]; then
		pushd /opt/sophon/libsophon-current/data
		sudo chmod +x load.sh
		sudo chmod +x unload.sh
		sudo ./load.sh
		popd
	fi

	if [ -f /opt/sophon/libsophon-current/data/load_jpu.sh ]; then
		pushd /opt/sophon/libsophon-current/data
		sudo chmod +x load_jpu.sh
		sudo chmod +x unload_jpu.sh
		sudo ./load_jpu.sh
		popd
	fi
}

function load_soph_base_ko()
{
	echo load soph_base ko ...
	if [ -f /mnt/system/ko/soph_base.ko ]; then
		insmod /mnt/system/ko/soph_base.ko
	fi
}

function load_soph_2d_engine_ko()
{
	echo load soph_2d_engine ko ...
	if [ -f /mnt/system/ko/soph_2d_engine.ko ]; then
		insmod /mnt/system/ko/soph_2d_engine.ko
	fi
}

function load_soph_pwm_ko()
{
	echo load soph_pwm ko ...
	if [ -f /mnt/system/ko/soph_pwm.ko ]; then
		insmod /mnt/system/ko/soph_pwm.ko
	fi
}

function load_soph_saradc_ko()
{
	echo load soph_saradc ko ...
	if [ -f /mnt/system/ko/soph_saradc.ko ]; then
		insmod /mnt/system/ko/soph_saradc.ko
	fi
}

function load_soph_clock_cooling_ko()
{
	echo load soph_clock_cooling ko ...
	if [ -f /mnt/system/ko/soph_clock_cooling.ko ]; then
		insmod /mnt/system/ko/soph_clock_cooling.ko
	fi
}

function load_soph_dpu_ko()
{
	echo load soph_dpu ko ...
	if [ -f /mnt/system/ko/soph_dpu.ko ]; then
		insmod /mnt/system/ko/soph_dpu.ko
	fi
}

function load_soph_dwa_ko()
{
	echo load soph_dwa ko ...
	if [ -f /mnt/system/ko/soph_dwa.ko ]; then
		insmod /mnt/system/ko/soph_dwa.ko
	fi
}

function load_soph_ive_ko()
{
	echo load soph_ive ko ...
	if [ -f /mnt/system/ko/soph_ive.ko ]; then
		insmod /mnt/system/ko/soph_ive.ko
	fi
}

function load_soph_rtc_ko()
{
	echo load soph_rtc ko ...
	if [ -f /mnt/system/ko/soph_rtc.ko ]; then
		insmod /mnt/system/ko/soph_rtc.ko
	fi
}

function load_soph_stitch_ko()
{
	echo load soph_stitch ko ...
	if [ -f /mnt/system/ko/soph_stitch.ko ]; then
		insmod /mnt/system/ko/soph_stitch.ko
	fi
}

function load_soph_sys_ko()
{
	echo load soph_sys ko ...
	if [ -f /mnt/system/ko/soph_sys.ko ]; then
		insmod /mnt/system/ko/soph_sys.ko
	fi
}

function load_soph_vpss_ko()
{
	echo load soph_vpss ko...
	if [ -f /mnt/system/ko/soph_vpss.ko ]; then
		insmod /mnt/system/ko/soph_vpss.ko
	fi
}

function load_soph_drm_ko()
{
	echo load soph_drm ko	...
	if [ -f /mnt/system/ko/soph_drm.ko ]; then
		insmod /mnt/system/ko/soph_drm.ko
	fi
}

function load_g_serial_ko()
{
	echo load g_serial ko...
	if [ -f /mnt/system/ko/g_serial.ko ]; then
		insmod /mnt/system/ko/g_serial.ko
	fi
}

function load_usb_f_obex_ko()
{
	echo load usb_f_obex ko ...
	if [ -f /mnt/system/ko/usb_f_obex.ko ]; then
		insmod /mnt/system/ko/usb_f_obex.ko
	fi
}

function load_usb_f_serial_ko()
{
	echo load usb_f_serial ko ...
	if [ -f /mnt/system/ko/usb_f_serial.ko ]; then
		insmod /mnt/system/ko/usb_f_serial.ko
	fi
}

function load_soph_vc_drv_ko()
{
	echo load soph_vc_drv ko	...
	if [ -f /mnt/system/ko/soph_vc_drv.ko ]; then
		insmod /mnt/system/ko/soph_vc_drv.ko
	fi
}

function load_soph_ldc_ko()
{
        echo load soph_ldc ko ...
        if [ -f /mnt/system/ko/soph_ldc.ko ]; then
                insmod /mnt/system/ko/soph_ldc.ko
        fi
}

function load_ethernet_ko()
{
        echo load ethernet ko ...
        if [ -f /mnt/system/ko/r8169.ko ]; then
                insmod /mnt/system/ko/r8169.ko
        fi
        if [ -f /mnt/system/ko/igb.ko ]; then
                insmod /mnt/system/ko/igb.ko
        fi
}

function load_spacc_ko()
{
	echo load spacc ko ...
	if [ -f /mnt/system/ko/sophon_spacc.ko ]; then
		insmod /mnt/system/ko/sophon_spacc.ko
	fi
}

function load_80211_ko()
{
        echo load cfg80211.ko ...
        if [ -f /mnt/system/ko/cfg80211.ko ]; then
                insmod /mnt/system/ko/cfg80211.ko
        fi
        echo load mac80211.ko ...
        if [ -f /mnt/system/ko/mac80211.ko ]; then
                insmod /mnt/system/ko/mac80211.ko
        fi
}

load_80211_ko
load_soph_base_ko
load_soph_sys_ko
load_soph_vpss_ko
load_soph_dwa_ko
load_soph_clock_cooling_ko
load_soph_vc_drv_ko
load_soph_rtc_ko
load_soph_ive_ko
echo load bmrt ko ...
load_ko
load_soph_2d_engine_ko
load_soph_pwm_ko
load_soph_saradc_ko
load_soph_dpu_ko
load_soph_stitch_ko
load_soph_drm_ko
# load_g_serial_ko
# load_usb_f_obex_ko
# load_usb_f_serial_ko
load_soph_ldc_ko
load_ethernet_ko
load_spacc_ko

# modify permission for drivers
echo "load.sh starting..."
./sbin/load.sh -d soph-base
./sbin/load.sh -d soph-sys
./sbin/load.sh -d soph-tde0
./sbin/load.sh -d soph-tde1
./sbin/load.sh -d soph-vpss
./sbin/load.sh -d soph_vc_dec
./sbin/load.sh -d soph_vc_enc
./sbin/load.sh -p /dev/dri/ -d card0
./sbin/load.sh -d soph-dpu
./sbin/load.sh -d soph-dwa
./sbin/load.sh -d soph-ive
./sbin/load.sh -d soph-stitch
./sbin/load.sh -d soph-ldc
./sbin/load.sh -d spacc
./sbin/load.sh -p /dev/snd/ -d controlC0
./sbin/load.sh -p /dev/snd/ -d controlC1
./sbin/load.sh -p /dev/snd/ -d controlC2
./sbin/load.sh -p /dev/snd/ -d pcmC0D0c
./sbin/load.sh -p /dev/snd/ -d pcmC0D1c
./sbin/load.sh -p /dev/snd/ -d pcmC1D0p
./sbin/load.sh -p /dev/snd/ -d pcmC1D1p
./sbin/load.sh -p /dev/snd/ -d pcmC2D0p
./sbin/load.sh -p /dev/snd/ -d timer
for file in $(find /dev/ -name video*);do
	file_name=${file##*/}
	./sbin/load.sh -d $file_name
done

for((i=0;i<=7;i++));do
	cmd="/sys/class/net/eth0/queues/rx-$i/rps_cpus"
	if [ -f $cmd ]; then
		echo f > $cmd
		echo 2048 > /sys/class/net/eth0/queues/rx-$i/rps_flow_cnt
	fi

	cmd="/sys/class/net/eth1/queues/rx-$i/rps_cpus"
	if [ -f $cmd ]; then
		echo f > $cmd
		echo 2048 > /sys/class/net/eth1/queues/rx-$i/rps_flow_cnt
	fi
done

exit 0
