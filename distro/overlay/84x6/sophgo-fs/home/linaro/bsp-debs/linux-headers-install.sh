#!/bin/bash

cur_ver=$(uname -r)
echo ${cur_ver}
if [ -e /home/linaro/bsp-debs/linux-headers_${cur_ver}_arm64.deb ]; then
	sudo dpkg -i /home/linaro/bsp-debs/linux-headers_${cur_ver}_arm64.deb
	cd /usr/src/linux-headers-${cur_ver}
	sudo make prepare0
	sudo make scripts
else
	echo "linux header deb not match"
fi
