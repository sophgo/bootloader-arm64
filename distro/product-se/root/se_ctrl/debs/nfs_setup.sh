#!/bin/bash
product=$(cat /sys/bus/i2c/devices/1-0017/information | grep model | awk -F \" '{print $4}')
if ([ "$product" = "SE6-CTRL" ] || [ "$product" = "SE6 CTRL" ]\
	|| [ "$product" = "SM7 CTRL" ] || [ "$product" = "SE8 CTRL" ]); then

	if [ -f /data/.sophon.net/install.sh ]; then
		/data/.sophon.net/install.sh
		echo "reinstall sophon.net"
	fi

	#fan and temperature monitor
	systemctl enable bmSE6Monitor.service
	systemctl restart bmSE6Monitor.service
	echo "stop systemd-timesyncd services"

	systemctl stop systemd-time-wait-sync.service

	systemctl disable systemd-time-wait-sync.service

	systemctl stop systemd-timesyncd.service
	systemctl disable systemd-timesyncd.service
	sudo dpkg -r  systemd-timesyncd

	sudo rm -rf /etc/ntp.conf
	sudo dpkg -i -R /root/se_ctrl/debs
	while [ $? -ne 0 ];
	do
		sleep 2
		sudo dpkg -i -R /root/se_ctrl/debs
	done

	sed -i 's/TFTP_DIRECTORY=\"\/srv\/tftp\"/TFTP_DIRECTORY=\"\/recovery\/tftp\"/' /etc/default/tftpd-hpa
	sed -i 's/\(TFTP_OPTIONS="\)/\1-v /' /etc/default/tftpd-hpa

	cp /etc/ntp.conf /etc/ntp.conf.bak

	systemctl restart tftpd-hpa
	systemctl restart NetworkManager.service

else
	rm -f /root/se_ctrl/debs/nfs-kernel-server*.deb
	rm -f /root/se_ctrl/debs/sophliteos_soc_*.deb
	rm -f /root/se_ctrl/debs/tftpd-hpa*.deb
	rm -f /root/se_ctrl/debs/ntp_*.deb
	rm -f /root/se_ctrl/debs/bmsec_*.deb

	sudo dpkg -i -R /root/se_ctrl/debs
	while [ $? -ne 0 ];
	do
		sleep 2
		sudo dpkg -i -R /root/se_ctrl/debs
	done

fi
