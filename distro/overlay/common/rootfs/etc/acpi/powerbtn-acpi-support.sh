#!/bin/sh

# This script initiates a shutdown when the power putton has been
# pressed. Loosely based on the sample that ships with the acpid package.
# If the acpid sample is present as a real config file (as it was in earlier
# versions of acpid), we skip this script. (Purging and reinstalling acpid
# resolves this situation, or simply deleting /etc/acpi/events/powerbtn.)

echo "power key pressed" > /var/log/acpid.log

echo "system will poweroff" >> /var/log/acpid.log
poweroff

