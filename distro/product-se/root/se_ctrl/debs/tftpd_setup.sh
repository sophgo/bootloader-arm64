#!/bin/bash

#fan and temperature monitor
systemctl enable bmSE6Monitor.service
systemctl restart bmSE6Monitor.service
echo "stop systemd-timesyncd services"

systemctl stop systemd-time-wait-sync.service

systemctl disable systemd-time-wait-sync.service

systemctl stop systemd-timesyncd.service
systemctl disable systemd-timesyncd.service
sudo dpkg -r  systemd-timesyncd

sudo dpkg -i /root/se_ctrl/debs/libopts*.deb
sudo rm -rf /etc/ntp.conf
sudo dpkg -i /root/se_ctrl/debs/ntp_*.deb
sudo dpkg -i /root/se_ctrl/debs/tftpd-hpa_*.deb


sed -i 's/TFTP_DIRECTORY=\"\/srv\/tftp\"/TFTP_DIRECTORY=\"\/recovery\/tftp\"/' /etc/default/tftpd-hpa

cp /etc/ntp.conf /etc/ntp.conf.bak

systemctl restart tftpd-hpa
systemctl restart NetworkManager.service
