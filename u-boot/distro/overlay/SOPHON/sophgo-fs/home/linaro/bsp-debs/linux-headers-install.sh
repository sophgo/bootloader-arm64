#!/bin/bash

cur_ver=$(uname -r)
echo ${cur_ver}
if [ -e /home/linaro/bsp-debs/linux-headers-${cur_ver}_arm64.deb ]; then
	if [ -d /lib/modules/${cur_ver} ]; then
		sudo dpkg -i /home/linaro/bsp-debs/linux-headers-${cur_ver}_arm64.deb
		sudo mkdir -p /usr/src/linux-headers-${cur_ver}/tools/include/tools
		sudo cp /home/linaro/bsp-debs/*.h  /usr/src/linux-headers-${cur_ver}/tools/include/tools
		cd /usr/src/linux-headers-${cur_ver}
		sudo make prepare0
		sudo make scripts
	else
		echo "/lib/modules not match"
	fi
else
	echo "linux header deb not match"
fi
