#!/bin/bash
period=40000
cur_rate=40000

# $1: target_rate
ctrl_fan_slowly()
{
	target_rate=$1
	if [ $target_rate -ge $(expr $cur_rate + 200) ];then
		echo speed up $former $newSpd
		cur_rate=$(expr $cur_rate + 400)
	elif [ $target_rate -le $(expr $cur_rate - 200) ];then
		echo slow down $former $newSpd
		cur_rate=$(expr $cur_rate - 400)
	else
		echo no update
	fi
}

if [ -d '/sys/class/pwm/pwmchip0/pwm0' ];then
	echo "already export"
else
	echo 0 > /sys/class/pwm/pwmchip0/export
fi
echo $period > /sys/class/pwm/pwmchip0/pwm0/period
echo $cur_rate > /sys/class/pwm/pwmchip0/pwm0/duty_cycle
echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable

while true;
do
	max_t=0

	# get ctrl temperature
	chip_t=$(bm_get_temperature | grep 'chip temperature' | \
		awk -F : '{printf("%s\n"),$3}' | \
		awk -F \' '{printf("%d\n"), $1}')
	if [ $chip_t -gt $max_t ];then
		max_t=$chip_t
	fi

	product=$(cat /sys/bus/i2c/devices/1-0017/information | grep model | awk -F \" '{print $4}')
	if [ "$product" = "SM7 AIRBOX" ];then
		if [ $max_t -ge 75 ];then
			echo temperature greater than 75
			rate=39999
        elif [ $max_t -ge 70 ] && [ $max_t -lt 75 ] ;then
			echo temperature greater than 70
            rate=36000
        elif [ $max_t -ge 60 ] && [ $max_t -lt 70 ] ;then
			echo temperature greater than 60
            rate=32000
        elif [ $max_t -lt 60 ] ;then
			echo temperature less than 60
            rate=24000
		fi
		ctrl_fan_slowly $rate
	fi
	echo "$cur_rate" > /sys/class/pwm/pwmchip0/pwm0/duty_cycle

	echo "set fan duty cycle is: $(expr $cur_rate / 400 )%; control board t : $chip_t "

	sleep 2
done

