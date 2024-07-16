#!/bin/bash

chip_led_state=0
fan_led_state=0
heating_state=0
s_port=3456
count=0
bus1=$(lsusb | grep 174c:2074 | awk -F : '{print $1}')
bus2=$(lsusb | grep 174c:3074 | awk -F : '{print $1}')
if [ "$bus1" = "Bus 001 Device 002" ] && [ "$bus2" = "Bus 002 Device 002" ]; then
	fan_exist=1
	echo 1 >/sys/class/bm_fan_speed/bm_fan_speed-0/enable
else
	fan_exist=0
	echo 0 >/sys/class/bm_fan_speed/bm_fan_speed-0/enable
fi

if [ ! -f "/tmp/module.txt" ]; then
	dd if=/sys/bus/nvmem/devices/1-006a0/nvmem of=/tmp/module.txt count=7 bs=1 skip=352
fi

module_type=$(cat /tmp/module.txt)
if [ "$module_type" = "SE53221" ]; then
	max_rate=20000
else
	max_rate=10000
fi

while true; do

	chip=$(cat /sys/class/thermal/thermal_zone0/temp)
	chip_temp=$(expr $chip / 1000)
	fan=$(cat /sys/class/bm_fan_speed/bm_fan_speed-0/fan_speed | awk -F : '{print $2}')
	fan_rate=$(expr $fan \* 30)

	if [ $count -gt 10 ]; then
		echo "chip temperature : $chip_temp; chip_led_state : $chip_led_state ; heating_state : $heating_state ; fan exist : $fan_exist ; fan_led_state : $fan_led_state; fan speed : $fan_rate."
		count=0
	fi
	count=$(expr $count + 1)

	#温度大于等于3度,加热关闭.温度小于3度,加热开启
	if [ $chip_temp -ge 3 ] && [ $heating_state -eq 1 ]; then
		(
			echo "heating off"
			sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			heating_state=0
		fi
	elif [ $chip_temp -lt 3 ] && [ $chip_led_state -eq 0 ]; then
		(
			echo "heating on"
			sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			heating_state=1
		fi
	fi
	#高温警告
	if [ $chip_temp -gt 90 ] && [ $chip_led_state -eq 0 ]; then
		(
			echo "temperature on"
			sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			chip_led_state=1
		fi
	elif [ $chip_temp -le 85 ] && [ $chip_led_state -eq 1 ]; then
		(
			echo "temperature off"
			sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			chip_led_state=0
		fi
	fi

	#大于30度才风扇告警
	if [ $chip_temp -le 30 ] || [ $fan_exist -eq 0 ]; then
		if [ $count -gt 10 ]; then
			echo "temperature less 30 or no fan ,no warning for fan!"
		fi
		sleep 5
		continue
	fi
	if [ $fan_rate -gt $max_rate ] || [ $fan_rate -le 2000 ] && [ $fan_led_state -eq 0 ]; then
		(
			echo "fan on"
			sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			fan_led_state=1
		fi
	elif [ $fan_rate -le 9500 ] && [ $fan_rate -gt 2500 ] && [ $fan_led_state -eq 1 ]; then
		(
			echo "fan off"
			sleep 1
		) | telnet 127.0.0.1 $s_port &>temp.log
		grep "Connected to" temp.log
		if [ $? -eq 0 ]; then
			fan_led_state=0
		fi
	fi
	sleep 5
done
