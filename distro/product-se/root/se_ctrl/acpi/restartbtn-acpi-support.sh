#!/bin/sh

echo "restart key pressed" > /var/log/acpid.log

cd /root/se_ctrl/script

./core_run_command_bynet.sh "sudo reboot" linaro linaro

echo "system will restart" >> /var/log/acpid.log

reboot_all

