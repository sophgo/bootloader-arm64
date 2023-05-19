#!/bin/bash

echo 1 > /proc/sys/net/ipv4/ip_forward
wanname=$(ifconfig | grep enp | awk -F : 'NR==1{print $1}')

wanip=$(ifconfig $wanname | grep "inet "|awk '{print $2}' )

if [ "$wanip" = "" ]; then
	sleep 10
	wanip=$(ifconfig $wanname | grep "inet "|awk '{print $2}' )
fi
lan1ip=$(ifconfig eth0 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d.\n", $1,$2,$3)}' )
lan2ip=$(ifconfig eth1 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d.\n", $1,$2,$3)}' )

#lan2ip="$lanip.140."
#lan1ip="$lanip.150."
iptables -t nat -F

for ((i=1; i<=6; i++))
do

	iptables -t nat -A PREROUTING -d $wanip -p tcp --dport 2002$i -j DNAT --to-destination "${lan2ip}1${i}":22

	iptables -t nat -A PREROUTING -d $wanip -p udp --dport "2${i}081":"2${i}082" -j DNAT --to-destination "${lan2ip}1${i}":"2${i}081-2${i}082"

	iptables -t nat -A PREROUTING -d $wanip -p tcp --dport 1002$i -j DNAT --to-destination "${lan1ip}1${i}":22

	iptables -t nat -A PREROUTING -d $wanip -p udp --dport "1${i}081":"1${i}082" -j DNAT --to-destination "${lan1ip}1${i}":"1${i}081-1${i}082"


done

#iptables -t nat -A PREROUTING -d "${lan1ip}200" -j DNAT --to-destination $wanip
#iptables -t nat -A PREROUTING -d "${lan2ip}200" -j DNAT --to-destination $wanip
iptables -t nat -A POSTROUTING -o $wanname -j MASQUERADE


