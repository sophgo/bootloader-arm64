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

monitor_memory() {
	local THRESHOLD=$((160 * 1024))
	local avail_mem
	avail_mem=$(grep MemAvailable /proc/meminfo | awk '{print $2}')
	if [ "$avail_mem" -le "$THRESHOLD" ]; then
		local TOP_PID
		TOP_PID=$(ps aux --sort=-%mem | awk 'NR==2 {print $2}')
		TOP_CMD=$(ps -p ${TOP_PID} -o cmd=)
		local LOGFILE="/var/log/mem_monitor.log"
		local TS
		TS=$(date '+%Y-%m-%d %H:%M:%S')
		echo "----------------------------------------" >> "$LOGFILE"
		echo "[$TS] memory info:" >> "$LOGFILE"
		ps aux --sort=-%mem | head -n 20 >> "$LOGFILE"
		cat /proc/meminfo >> "$LOGFILE"
		kill -9 "$TOP_PID"
		wall "Warrning: free mem < 160MB, kill (PID: $TOP_PID) (CMD: $TOP_CMD) !"
		echo "Warrning: free mem < 160MB, kill (PID: $TOP_PID) (CMD: $TOP_CMD) !" >> "$LOGFILE"
		echo "----------------------------------------" >> "$LOGFILE"
	fi
}
monitor_memory_str=$(declare -f monitor_memory | gzip -c - | base64)

echo load bmrt ko ...
load_ko
invoke_board_setup

systemd-run --unit=sophgo-monitor-memory /usr/bin/bash -c \
"source /dev/stdin <<< \$(echo \"$monitor_memory_str\" | base64 -d | gzip -d -c -); while true; do monitor_memory; sleep 2; done"
systemctl status sophgo-monitor-memory.service -l --no-page

exit 0
