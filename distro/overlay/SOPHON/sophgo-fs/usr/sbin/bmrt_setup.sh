#!/bin/bash

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
		#	sed -i "s/ExecStart=\/usr\/bin\/dockerd -H fd:\/\//ExecStart=\/usr\/bin\/dockerd -g \/data\/docker -H fd:\/\//g" /lib/systemd/system/docker.service
		#	systemctl daemon-reload
		#	systemctl restart docker.service
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
		systemctl enable bsl_hack.service
		systemctl start bsl_hack.service


		touch /root/post_install/installed
	fi
}

ldconfig

while [ -f "/etc/systemd/system/basic.target.wants/resize-helper.service" ];
do
	echo "bmrt_setup waiting resize finish!!!"
	sleep 1;
done

sudo chown linaro:linaro -R /data
#store_reset_reason

/usr/sbin/read_oem.sh

if [ -f "/etc/systemd/system/bmssm.service" ]; then
	if [ ! -f "/etc/systemd/system/multi-user.target.wants/bmssm.service" ]; then
		echo "systemctl enable bmssm"
		systemctl daemon-reload
		systemctl enable bmssm.service
		systemctl start bmssm.service
		systemctl enable sophliteos.service
		systemctl start sophliteos.service
	fi
fi

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

