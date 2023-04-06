#!/bin/bash


function se6_install_prepackages()
{
	# for se6 only
	if [ ! -f /root/se6_ctrl/debs/installed ] ; then

		# install tftp server and config it
		product=$(cat /sys/bus/i2c/devices/1-0017/information | grep model | awk -F \" '{print $4}')
		if ([ "$product" = "SE6-CTRL" ] || [ "$product" = "SE6 CTRL" ]); then
			cp /root/se6_ctrl/script/reboot_all /usr/sbin/
			cp -r /root/se6_ctrl/script /home/linaro/
			rm /home/linaro/script/reboot_all
			rm /home/linaro/script/switch_uart.sh
			rm /home/linaro/script/core_run_command.py
			chown linaro.linaro -R /home/linaro/script
		fi
		if [ -d /root/se6_ctrl/debs ]; then
			/root/se6_ctrl/debs/nfs_setup.sh
			touch /root/se6_ctrl/debs/installed
		fi
		cp /etc/ntp.conf.bak /etc/ntp.conf
	fi
}

# config ntp local clock
config_ntp_local_clock() {
	echo "[# Config local clock!"
	#server 127.127.1.0
	echo "1.server:"
	ret_str_ntp=$(grep -n "server 127.127.1.0" /etc/ntp.conf)
	if [[ -z $ret_str_ntp ]];then
		sudo bash -c "echo '# Undisciplined Local Clock. This is a fake driver intended for backup' >> /etc/ntp.conf"
		sudo bash -c "echo '# and when no outside source of synchronized time is available.' >> /etc/ntp.conf"
		sudo bash -c "echo 'server 127.127.1.0' >> /etc/ntp.conf"
		sed -i "/restrict 127.0.0.1/a restrict 0.0.0.0 mask 0.0.0.0 nomodify notrap" /etc/ntp.conf
		#replace a li source
		sed -i "s/pool.0.ubuntu.pool.ntp.org/server ntp.aliyun.com/g" /etc/ntp.conf
		sed -i "s/pool.1.ubuntu.pool.ntp.org/server ntp1.aliyun.com/g" /etc/ntp.conf
		sed -i "s/pool.2.ubuntu.pool.ntp.org/server ntp2.aliyun.com/g" /etc/ntp.conf
		sed -i "s/pool.3.ubuntu.pool.ntp.org/server ntp3.aliyun.com/g" /etc/ntp.conf
		echo "Server configuration completed!"
	else
		echo "Server already configured!"
	fi
	#fudge 127.127.1.0 stratum 10
	echo "2.fudge:"
	ret_str_ntp_2=$(grep -n "fudge 127.127.1.0 stratum 10" /etc/ntp.conf)
	if [[ -z $ret_str_ntp_2 ]];then
		sudo bash -c "echo 'fudge 127.127.1.0 stratum 10' >> /etc/ntp.conf"
		echo "Fudge configuration completed!"
	else
		echo "Fudge already configured!"
	fi
	echo "3.tinker:"
	ret_str_ntp_3=$(grep -n "tinker panic 0" /etc/ntp.conf)
	if [[ -z $ret_str_ntp_3 ]];then
		sudo bash -c "sed -i '1itinker panic 0' /etc/ntp.conf"
		echo "Tinker configuration completed!"
	else
		echo "Tinker already configured!"
	fi
	#restart ntp
	if [[ -z $ret_str_ntp ]] || [[ -z $ret_str_ntp_2 ]] || [[ -z $ret_str_ntp_3 ]];then
		sleep 1
		sudo systemctl daemon-reload > /dev/null 2>&1
		sudo systemctl restart ntp > /dev/null 2>&1
	fi
}


function se6_init()
{
	product=$(cat /sys/bus/i2c/devices/1-0017/information | grep model | awk -F \" '{print $4}')

	se6_install_prepackages
	if [ "$product" = "SE6-CTRL" ] || [ "$product" = "SE6 CTRL" ] ; then
		echo "se6 ctl init!"
		# remove sophon system, sophon hdmi server
		if [ -f /etc/systemd/system/multi-user.target.wants/SophonHDMI.service ]; then
			systemctl stop SophonHDMIStatus.service
			systemctl stop SophonHDMI.service
			systemctl stop SophonSystem.service
			systemctl stop bmSysMonitor.service
			systemctl stop lteModemManager.service
			systemctl disable SophonHDMIStatus.service
			systemctl disable SophonHDMI.service
			systemctl disable SophonSystem.service
			systemctl disable bmSysMonitor.service
			systemctl disable lteModemManager.service
			#remove sophon system config files
			rm -rf /data/config
			rm -rf /data/log

			# setup bm-ssm
			mkdir -p /data/ota
			chown linaro.linaro /data/ota
			pushd /system/bmssm
			/system/bmssm/deploy-bmssm.sh
			popd
			cp /root/se6_ctrl/acpi/* /etc/acpi/
			systemctl restart acpid
		fi

		if [ ! -f /etc/systemd/system/multi-user.target.wants/bmSE6Monitor.service ]; then
			systemctl stop bmSysMonitor.service
			systemctl disable bmSysMonitor.service
			systemctl enable bmSE6Monitor.service
			systemctl start bmSE6Monitor.service
		fi
		systemctl stop ledSocketServer.service
		systemctl disable ledSocketServer.service

		#waiting for network ready
		sleep 10
		lanlist=(172.16 172.18 172.20 10.168)
		i_device=$(ifconfig | grep enp | awk -F : 'NR==1{print $1}')
		wanip=$(ifconfig $i_device | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d\n", $1,$2)}' )

		echo "$(ifconfig eth0 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d\n", $1,$2,$3)}' )"
		echo "$(ifconfig eth1 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d\n", $1,$2,$3)}' )"
		echo "$(ifconfig eth0 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d\n", $4)}' )"
		echo "$(ifconfig eth1 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d\n", $4)}' )"


		lan1ip=$(ifconfig eth0 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d\n", $1,$2,$3)}')
		lan2ip=$(ifconfig eth1 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d\n", $1,$2,$3)}')

		lan1net=$(ifconfig eth0 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d\n", $1,$2)}')
		lan2net=$(ifconfig eth1 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d\n", $1,$2)}')

		lan1host=$(ifconfig eth0 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d\n", $4)}' )
		lan2host=$(ifconfig eth1 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d\n", $4)}' )

		if [ "$lan1host" != "200" ] || [ "$lan2host" != "200" ] || [ "$lan1ip" = "" ] || [ "$lan2ip" = "" ] || [ "$wanip" = "$lan1net" ] || [ "$wanip" = "$lan2net" ]; then
			echo "use default lan ip"
			lanip=${lanlist[0]}
			for ip in ${lanlist[@]}
			do
				#       echo "$lanip"
				if [ $wanip != $ip ];then
					echo "$ip"
					lanip=$ip
					break
				fi

			done
			lan1ip="${lanip}.140"
			lan2ip="${lanip}.150"
		else
			echo "use customer lan ip"
			lanip=$(ifconfig eth0 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d\n", $1,$2)}')
		fi

		echo "startup core board!!"
		source /root/se6_ctrl/se6ctr.sh

		se6ctr_set_aiu_ipaddr ${lan1ip} ${lan2ip}
		#config ntp for cores
		config_ntp_local_clock
		#add static ip for debug
		#ip addr add 192.168.150.1/24 dev enp3s0
		bm_set_ip eth0 ${lan1ip}.200 255.255.255.0 "" ""
		bm_set_ip eth1 ${lan2ip}.200 255.255.255.0 "" ""

		dsn=$(grep DEVICE_SN /factory/OEMconfig.ini | awk -F '= ' '{print $2}' |  sed 's/.*\(......\)$/\1/')
		cur=$(hostname)
		if [ "$cur" != "$dsn-host" ];then
			hostnamectl set-hostname "$dsn-host"
			sed -i '/127.0.1.1/d' /etc/hosts
			echo "127.0.1.1       $dsn-host"| sudo tee -a /etc/hosts
			sync
		fi
		systemctl enable ledSocketServer.service
		systemctl start ledSocketServer.service
		#echo set nat for cores
		/root/se6_ctrl/iptable_setup.sh
	else
		coreip=$(cat /sys/bus/i2c/devices/1-0017/board-ip | awk -F : '{print $2}')

		core=$(echo $coreip | awk -F . '{printf("%d.%d.%d\n", $1,$2,$3)}')
		if [ "$coreip" = "0.0.0.0" ] || [ "$coreip" = "" ];then
			echo "not se6 product"
			if [ -f /etc/systemd/system/multi-user.target.wants/bmSE6Monitor.service ]; then
				systemctl stop bmSE6Monitor.service
				systemctl disable bmSE6Monitor.service
				systemctl enable bmSysMonitor.service
				systemctl start bmSysMonitor.service
				#mv /system/usr /system/old_lib
				mv /system/usr/lib/aarch64-linux-gnu/libm.* /system/usr
			fi
		else
			# remove sophon system, sophon hdmi server
			if [ -f /etc/systemd/system/multi-user.target.wants/SophonHDMI.service ]; then
				systemctl stop SophonHDMIStatus.service
				systemctl stop SophonHDMI.service
				systemctl stop SophonSystem.service
				systemctl stop bmSysMonitor.service
				systemctl stop lteModemManager.service
				systemctl disable SophonHDMIStatus.service
				systemctl disable SophonHDMI.service
				systemctl disable SophonSystem.service
				systemctl disable bmSysMonitor.service
				systemctl disable lteModemManager.service
				#remove sophon system config files
				rm -rf /data/config
				rm -rf /data/log


			fi
			# cores init only
			if [ -f /etc/systemd/system/multi-user.target.wants/bmSE6Monitor.service ]; then
				systemctl stop bmSE6Monitor.service
				systemctl stop ledSocketServer.service
				systemctl disable bmSE6Monitor.service
				systemctl disable ledSocketServer.service
			fi

			# cores init only
			if [ ! -d /home/linaro/tftp_update ]; then
				cp -r /root/se6_ctrl/tftp_update /home/linaro
				cp -r /root/se6_ctrl/script /home/linaro
				chown linaro.linaro -R /home/linaro/*
				cp /etc/systemd/timesyncd.conf  /etc/systemd/timesyncd.conf.bak
				sed -i "s/#NTP=/NTP=${core}.200/" /etc/systemd/timesyncd.conf
				# rename system/usr lib
				#mv /system/usr /system/old_lib
				mv /system/usr/lib/aarch64-linux-gnu/libm.* /system/usr
				# setup bm-ssm
				pushd /system/bmssm
				sed -i "s/192.168.150.101/${coreip}/" /system/bmssm/deviceConf.json
				/system/bmssm/deploy-bmssm.sh
				popd

			fi
			echo "se6 core set ip"
			device_path="/etc/netplan/01-netcfg.yaml"
			rm /etc/netplan/*
			echo "network:" | sudo tee -a $device_path
			echo "        version: 2" | sudo tee -a  $device_path
			echo "        renderer: networkd" | sudo tee -a  $device_path
			echo "        ethernets:" | sudo tee -a  $device_path
			bm_set_ip eth0 $coreip 255.255.255.0 ${core}.200 "8.8.8.8,114.114.114.114"
			# set ntp conf
			#cp /etc/systemd/timesyncd.conf.bak /etc/systemd/timesyncd.conf
			exist=$(grep "${core}.200" /etc/systemd/timesyncd.conf | wc -l)
			if [ $exist -lt 1 ];then
				sed -i "0,/NTP=/{s/NTP=/NTP=${core}.200 /}" /etc/systemd/timesyncd.conf
			fi

			dsn=$(grep DEVICE_SN /factory/OEMconfig.ini | awk -F '= ' '{print $2}' |  sed 's/.*\(......\)$/\1/')
			id=$(cat /sys/bus/i2c/devices/1-0017/board-id | awk -F : '{print $2}')
			cur=$(hostname)
			if [ "$cur" != "$dsn-$id" ];then
				hostnamectl set-hostname "$dsn-$id"
				sed -i '/127.0.1.1/d' /etc/hosts
				echo "127.0.1.1       $dsn-$id"| sudo tee -a /etc/hosts
				sync
			fi
			# restart bmssm service
			systemctl restart bmssm.service
			sleep 15
			systemctl restart systemd-timesyncd.service
		fi

	fi

}
