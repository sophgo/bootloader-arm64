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
			sed -i "s/ExecStart=\/usr\/bin\/dockerd -H fd:\/\//ExecStart=\/usr\/bin\/dockerd\
			   	-g \/data\/docker -H fd:\/\//g" /lib/systemd/system/docker.service
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
if [ -f /root/se_ctrl/se_init.sh ]; then
	source /root/se_ctrl/se_init.sh
	se_init
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
echo bmrt_setup done!

function repartition_hd()
{
echo -e "yes\n" | parted /dev/sda mktable msdos
echo -e "yes\nignore\n" | parted /dev/sda mkpart p ext4 0% 62%
echo -e "yes\nignore\n" | parted /dev/sda mkpart p ext4 62% 85%
echo -e "yes\nignore\n" | parted /dev/sda mkpart p ext4 85% 90%
echo -e "yes\nignore\n" | parted /dev/sda mkpart p ext4 90% 100%
partprobe
mkfs.ext4 /dev/sda1 -L docker -q -F
mkfs.ext4 /dev/sda2 -L kubelet -q -F
mkfs.ext4 /dev/sda3 -L log -q -F
mkfs.ext4 /dev/sda4 -L share -q -F
parted /dev/sda print
}

function setup_hd()
{
echo setup SSD...
if [ ! -b /dev/sda4 ]; then
umount /dev/sda3
umount /dev/sda2
umount /dev/sda1
parted /dev/sda rm 3
parted /dev/sda rm 2
parted /dev/sda rm 1

repartition_hd
fi
}

echo sangfor_setup start!
echo "PROVIDER=SOPHGO" >> /factory/OEMconfig.ini
echo "MAX_GPU_COMPUTE_CAPABILITY=17.6" >> /factory/OEMconfig.ini

if [ -d /vendor/app_patch ]; then
systemctl stop docker
systemctl disable docker
# disable for safety reason
setup_hd

# mount hard disk
if [ ! -d /var/lib/docker ]; then
mkdir -p /var/lib/docker
fi
if [ ! -d /var/lib/kubelet ]; then
mkdir -p /var/lib/kubelet
fi
if [ ! -d /opt/share ]; then
mkdir -p /opt/share
fi
if [ -f /media/root-ro/etc/fstab.emmc.ro.ssd ]; then
mount -o remount,rw /media/root-ro
mv /media/root-ro/etc/fstab.emmc.ro.ssd /media/root-ro/etc/fstab.emmc.ro
mount -o remount,ro /media/root-ro
cp /media/root-ro/etc/fstab.emmc.ro /etc/fstab
systemctl stop rsyslog
systemctl stop systemd-journald
mount /dev/sda1
mount /dev/sda2
mount /dev/sda3
mount /dev/sda4
systemctl start rsyslog
systemctl start systemd-journald
fi

# install packages
if [ ! -f /root/customized ] ; then
echo customization begain...

# change user
userdel linaro
adduser --gecos sfedge --disabled-login sfedge
echo "sfedge:sfedge" | chpasswd
usermod -a -G sudo sfedge
usermod -a -G docker sfedge
mv /home/linaro/* /home/sfedge/
rm -rf /home/linaro

# change history size
sed -i -e "s/HISTSIZE=1000/HISTSIZE=3000/g" /home/sfedge/.bashrc

# enable services
update-alternatives --set iptables /usr/sbin/iptables-legacy
systemctl enable docker
systemclt start docker
systemctl enable acpid

# disable services
systemctl stop apparmor
systemctl disable apparmor
systemctl disable crash_kdump
systemctl disable systemd-pstore

systemctl stop lteModemManager
systemctl disable lteModemManager
systemctl stop bmDeviceDetect
systemctl disable bmDeviceDetect
systemctl stop SophonHDMI
systemctl disable SophonHDMI
systemctl stop SophonHDMIStatus
touch /root/customized
fi

echo install vendor patch...
pushd /vendor/app_patch
./install_app.sh
popd
rm -rf /vendor/app_patch
fi

echo sangfor_setup done!



