#!/bin/bash
function load_ko()
{
	if [ -f /opt/sophon/libsophon-current/data/bmtpu.ko ]; then
		sudo mkdir -p /lib/firmware
		ln -s /opt/sophon/libsophon-current/data/a53lite_pkg.bin \
			/lib/firmware/bm1684x_firmware.bin
		ln -s /opt/sophon/libsophon-current/data/bm1684_ddr.bin_v*-*-* \
			/lib/firmware/bm1684_ddr_firmware.bin
		ln -s /opt/sophon/libsophon-current/data/bm1684_tcm.bin_v*-*-* \
			/lib/firmware/bm1684_tcm_firmware.bin
		insmod /opt/sophon/libsophon-current/data/bmtpu.ko
	fi

	if [ -f /opt/sophon/libsophon-current/data/load.sh ]; then
		pushd /opt/sophon/libsophon-current/data
		sudo chmod +x load.sh
		sudo chmod +x unload.sh
		sudo ./load.sh
		popd
	fi

	if [ -f /opt/sophon/libsophon-current/data/load_jpu.sh ]; then
		pushd /opt/sophon/libsophon-current/data
		sudo chmod +x load_jpu.sh
		sudo chmod +x unload_jpu.sh
		sudo ./load_jpu.sh
		popd
	fi
}

function invoke_board_setup() {
    local board setup
    board="$(tr -d '\0' </proc/device-tree/info/file-name)"
    setup="/usr/sbin/$(basename $board .dtb)-setup.sh"
    test -x "$setup" && "$setup"
}

echo load bmrt ko ...
load_ko
invoke_board_setup
exit 0
