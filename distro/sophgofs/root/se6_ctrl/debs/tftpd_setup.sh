#!/bin/bash

#fan and temperture monitor 
systemctl enable bmSE6Monitor.service 
systemctl restart bmSE6Monitor.service 
echo "stop systemd-timesyncd services"

systemctl stop systemd-time-wait-sync.service
 
systemctl disable systemd-time-wait-sync.service

systemctl stop systemd-timesyncd.service
systemctl disable systemd-timesyncd.service
sudo dpkg -r  systemd-timesyncd

sudo dpkg -i /root/se6_ctrl/debs/*.deb

sed -i 's/TFTP_DIRECTORY=\"\/srv\/tftp\"/TFTP_DIRECTORY=\"\/recovery\/tftp\"/' /etc/default/tftpd-hpa

cp /etc/ntp.conf /etc/ntp.conf.bak

systemctl restart tftpd-hpa
