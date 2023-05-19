#!/bin/sh

echo "restart key pressed" > /var/log/acpid.log

#user can do someting or save something before reboot

echo "system will reboot" >> /var/log/acpid.log

reboot



