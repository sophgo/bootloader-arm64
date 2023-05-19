#!/bin/bash

if [ -d '/sys/class/pwm/pwmchip0/pwm0' ];then
	echo "already export"
else
	echo 0 > /sys/class/pwm/pwmchip0/export
fi
echo 40000 > /sys/class/pwm/pwmchip0/pwm0/period
echo 39999 > /sys/class/pwm/pwmchip0/pwm0/duty_cycle
echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable

if [ -d '/sys/class/bm_fan_speed/bm_fan_speed-0/enable' ];then
	fan_path='bm_fan_speed/bm_fan_speed-0'
else
	fan_path='bm-tach/bm-tach-0'
fi
sleep 30
echo 1 > /sys/class/${fan_path}/enable
count=0

net_warning=0
temp_warning=0
fan_warning=0

net_state=0
s_port=3456

# type=1 is 96, type=ff is 192
ptype=$(i2cget -f -y 0x1 0x6f 0x41)

rm /root/.ssh/known_hosts

while true;
do

	lan1ip=$(ifconfig eth0 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d.\n", $1,$2,$3)}' )
	lan2ip=$(ifconfig eth1 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d.\n", $1,$2,$3)}' )

	max_t=0

	fan=$(cat /sys/class/${fan_path}/fan_speed | awk -F : '{print $2}')
	fan_rate=$(expr $fan \* 30)

	net_warning=0

	for ((i=1; i<=6; i++))
	do
		if [ "$ptype" = "0xff" ];then
			res=$(/root/se6_ctrl/script/ssh_anycmd.exp "${lan1ip}1${i}" linaro linaro "bm_get_temperature" )
			chip_t=$(echo "$res" | grep 'chip temperature' | awk -F : '{printf("%s\n"),$3}' | awk -F \' '{printf("%d\n"), $1}')
			board_t=$(echo "$res" | grep 'chip temperature' | awk -F : '{printf("%s\n"),$2}'| awk -F \' '{printf("%d\n"), $1}')
		else
			chip_t=30
			board_t=30
		fi
		res1=$(/root/se6_ctrl/script/ssh_anycmd.exp "${lan2ip}1${i}" linaro linaro "bm_get_temperature")
		chip2_t=$(echo "$res1" | grep 'chip temperature' | awk -F : '{printf("%s\n"),$3}' | awk -F \' '{printf("%d\n"), $1}')
		board2_t=$(echo "$res1" | grep 'chip temperature' | awk -F : '{printf("%s\n"),$2}'| awk -F \' '{printf("%d\n"), $1}')


		if [ "$chip_t" = "" ] || [ "$chip2_t" = "" ];then
			net_warning=1
		fi
		if [ "$chip_t" != "" ] && [ $chip_t -gt $max_t ];then
			max_t=$chip_t
		fi
		if [ "$chip2_t" != "" ] && [ $chip2_t -gt $max_t ];then
			max_t=$chip2_t
		fi
		if [ $count -gt 10 ]; then
			echo "chip max temperature : $max_t; fan_speed : $fan_rate; id :$i ; chip_t: $chip_t ; chip2_t : $chip2_t "
		fi
	done

	count=$(expr $count + 1)
	# get ctrl temperature
	chip_t=$(bm_get_temperature | grep 'chip temperature' | awk -F : '{printf("%s\n"),$3}' | awk -F \' '{printf("%d\n"), $1}')
	if [ $chip_t -gt $max_t ];then
		max_t=$chip_t
	fi

	ratio=0
	if [ $max_t -ge 85 ];then
		rate=0
	elif [ $max_t -ge 68 ] && [ $max_t -le 85 ] ;then
		ratio=$(expr $max_t \- 68)
		rate=$(expr 30000 \- $(expr $ratio \* 1764))
	elif [ $max_t -ge 64 ] && [ $max_t -le 68 ] ;then
		ratio=$(expr $max_t \- 64)
		rate=$(expr 34000 \- $(expr $ratio \* 1000))
	elif [ $max_t -ge 60 ] && [ $max_t -le 64 ] ;then
		ratio=$(expr $max_t \- 60)
		rate=$(expr 36000 \- $(expr $ratio \* 500))
		rate=36000
	elif [ $max_t -le 60 ] ;then
		rate=39999
	fi

	echo "$rate" > /sys/class/pwm/pwmchip0/pwm0/duty_cycle

	echo "set fan duty cycle is: $rate; ratio $ratio; control board t : $chip_t "
	echo "network warning is $net_state ; temperature warning is $temp_warning ; fan warning is $ $fan_warning"

	# core network warning handle
	if [ $net_warning -eq 1 ] && [ $net_state -eq 0 ];then
		(
		echo "network on"
		sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			net_state=1
		fi
	elif [ $net_warning -eq 0 ] && [ $net_state -eq 1 ];then
		(
		echo "network off"
		sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			net_state=0
		fi
	fi

	# temp warning handle
	if [ $max_t -ge 95 ] && [ $temp_warning -eq 0 ];then
		(
		echo "temperature on"
		sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			temp_warning=1
		fi
	elif [ $max_t -le 90 ] && [ $temp_warning -eq 1 ];then
		(
		echo "temperature off"
		sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			temp_warning=0
		fi
	fi

	# fan warning handle
	if [ $fan_rate -le 1000 ] && [ $fan_warning -eq 0 ];then
		(
		echo "fan on"
		sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			fan_warning=1
		fi
	elif [ $fan_rate -gt 1500 ] && [ $fan_warning -eq 1 ];then
		(
		echo "fan off"
		sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			fan_warning=0
		fi
	fi

	sleep 5
done

