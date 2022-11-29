#!/bin/bash

sudo dpkg -i /root/se6_ctrl/debs/*.deb

sed -i 's/TFTP_DIRECTORY=\"\/srv\/tftp\"/TFTP_DIRECTORY=\"\/recovery\/tftp\"/' /etc/default/tftpd-hpa


systemctl restart tftpd-hpa
