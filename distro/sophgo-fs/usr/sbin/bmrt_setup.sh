#!/bin/bash


function load_ko()
{
	if [ -f /opt/sophon/libsophon-current/data/bmtpu.ko ]; then
		sudo mkdir -p /lib/firmware
		ln -s /opt/sophon/libsophon-current/data/a53lite_pkg.bin \
			/lib/firmware/bm1684x_firmware.bin
		ln -s /opt/sophon/libsophon-current/data/bm1684_ddr.bin_v*-*-* \
			/lib/firmware/bm1684_ddr_firmware.bin
		ln -s /opt/sophon/libsophon-current/data/bm1684_tcm.bin_v*-*-* \
			/lib/firmware/bm1684_tcm_firmware.bin
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
function reset_module()
{
	product=$(cat /sys/bus/i2c/devices/1-0017/information | grep model | awk -F \" '{print $4}')
	# rescan pci for missing fl2000
	if [ ! -e /dev/fl2000-0 ] && [ "$product" = "SE5" ]; then
		echo 1 > /sys/bus/pci/devices/0000:01:00.0/remove
		echo 1 > /sys/bus/pci/rescan
		echo "missing fl2000 and rescan pci"
	fi

	# reset lte module for missing 4g module
	if [ ! -e /dev/ttyUSB1 ]; then
		sudo i2cset -y -f 1 0x6c 0x2 0x81
		sleep 2
		sudo i2cset -y -f 1 0x6c 0x2 0x01
	fi

	# overwrite reboot command
	if [ -e /dev/bm-wdt-0 ]; then
		rm /sbin/reboot
		echo '#!/bin/bash' > /sbin/reboot
		echo 'echo 120 > /dev/bm-wdt-0' >> /sbin/reboot
		echo 'echo manual > /dev/bm-wdt-0' >> /sbin/reboot
		echo 'echo enable > /dev/bm-wdt-0' >> /sbin/reboot
		echo 'systemctl reboot' >> /sbin/reboot
		chmod +x /sbin/reboot
		echo 'timeout 60' > /dev/bm-wdt-0
		echo 'interval 10' > /dev/bm-wdt-0
	fi
	# ModemManager would disturb /dev/ttyUSB2, so disable it
	if [ -L /etc/systemd/system/multi-user.target.wants/ModemManager.service ]; then
		systemctl stop ModemManager.service
		systemctl disable ModemManager.service
	fi
}


function store_reset_reason()
{
	# store mcu boot reason
	name=$(date +%m-%d-%H-%M-%S)
	name="$name.txt"
	mkdir -p /root/.boot/
	count=$(ls /root/.boot/*.txt|wc -l)
	if [ $count -gt 10 ];then
		rm /root/.boot/*.txt
	fi
	dd if=/sys/bus/nvmem/devices/1-006a0/nvmem of=/root/.boot/$name count=4 bs=1 skip=160

	# erase mcu reason
	echo "0000">sn.txt
	xxd -p -u -r sn.txt > sn.bin
	echo 0 > /sys/devices/platform/5001c000.i2c/i2c-1/1-0017/lock

	dd if=sn.bin of=/sys/bus/nvmem/devices/1-006a0/nvmem count=4 bs=1 seek=160

	echo 1 > /sys/devices/platform/5001c000.i2c/i2c-1/1-0017/lock
	rm sn.txt
	rm sn.bin

	# read oem info for all-in-one version,don't copy to se5
	# se5 read it by gate app
	mkdir -p /factory
	/usr/sbin/read_oem

}
function install_prepackages()
{
	# install packages
	if [ ! -f /root/post_install/installed ] ; then
		systemctl disable proc-sys-fs-binfmt_misc.mount

		debs_num=$(ls /root/post_install/debs/*.deb | wc -l)
		if [  -d /root/post_install/debs ] && [ $debs_num -gt 0 ] ; then
			dpkg -i -R /root/post_install/debs

			while [ $? -ne 0 ];
			do
				sleep 2
				dpkg -i -R /root/post_install/debs
			done
		fi
		# configure docker
		if [ -f /lib/systemd/system/docker.service ]; then
			usermod -aG docker linaro
			sed -i "s/ExecStart=\/usr\/bin\/dockerd -H fd:\/\//ExecStart=\/usr\/bin\/dockerd -g \/data\/docker -H fd:\/\//g" /lib/systemd/system/docker.service
			systemctl daemon-reload
			systemctl restart docker.service
		fi

		# avoid conficts with last_kmsg service
		systemctl disable systemd-pstore

		systemctl enable acpid
		systemctl restart acpid

		systemctl enable rc-local.service
		systemctl restart rc-local.service

		#enable ssh service and disable ssh socket serveice
		sed -i "/RuntimeDirectory=sshd/a RuntimeDirectoryPreserve=yes" /lib/systemd/system/ssh.service
		systemctl stop ssh.socket
		systemctl disable ssh.socket
		systemctl enable ssh.service
		systemctl start ssh.service


		touch /root/post_install/installed
	fi
}
function invoke_board_setup() {
    local board setup
    board="$(tr -d '\0' </proc/device-tree/info/file-name)"
    setup="/usr/sbin/$(basename $board .dts)-setup.sh"
    test -x "$setup" && "$setup"
}

# enable /etc/ld.so.conf.d/system.conf
ldconfig

while [ -f "/etc/systemd/system/basic.target.wants/resize-helper.service" ];
do
	echo "bmrt_setup waiting resize finish!!!"
	sleep 1;
done

sudo chown linaro:linaro -R /data
load_ko
reset_module
store_reset_reason
install_prepackages
if [ -f /root/se6_ctrl/se6_init.sh ]; then
	source /root/se6_ctrl/se6_init.sh
	se6_init
else
	echo "not se6 product"
	if [ -f /etc/systemd/system/multi-user.target.wants/bmSE6Monitor.service ]; then
		systemctl stop bmSE6Monitor.service
		systemctl disable bmSE6Monitor.service
		systemctl enable bmSysMonitor.service
		systemctl start bmSysMonitor.service
	fi

fi
invoke_board_setup
