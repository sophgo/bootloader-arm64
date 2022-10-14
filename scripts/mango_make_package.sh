#!/bin/bash

PROGNAME=$(basename $0)

set -e

EMMC_DEV_NUM=0
SDCARD_DEV_NUM=1
LOAD_PARTITION_NUM=1


LOAD_COMMAND=fatload

SECTOR_BYTES=512
CHUNK_SIZE=200704

BOOT_PART_OFFSET=8192
SCRIPT_ADDR="\${scriptaddr}"
IN_ADDR="\${ramdisk_addr_r}"
IN_ADDR_B="\${ramdisk_addr_b}"
OUT_ADDR="\${unzip_addr}"

RECOVERY_DIR=recovery_files
PARTITION_FILE=partition32G.xml
BOOTCMD_SCRIPT=boot_emmc
SPIFCMD_SCRIPT=boot_spif
TOP_SCRIPT=boot
MOUNT_DIR=tmp

OTA_PATH='/$ota_path/'
ERASE_PARTITION=false

SOURCE_FILES_PATH=



# help function
function usage()
{
	echo >&2
	echo "${PROGNAME}: $@" >&2
	echo >&2
	echo "Usage: ${PROGNAME} <type> <partition file> <source tgz files path>" >&2
	echo >&2
	echo "	type:" >&2
	echo "	sdcard		build sdcard update img" >&2
	echo "	tftp		build tftp update img" >&2
	echo >&2
	echo "	partition file:" >&2
	echo "	specified a partition file" >&2
	echo >&2
	echo >&2
	echo "	source tgz files path:" >&2
	echo "	specified your .tgz files path" >&2
	echo >&2
	exit 1
}

function cleanup()
{
	for i in $(seq 0 $[${#LABELS[@]}-1]); do
		if [ -f $RECOVERY_DIR/${LABELS[$i]} ]; then
			rm -f $RECOVERY_DIR/${LABELS[$i]}
		fi
		if mountpoint -q $RECOVERY_DIR/$MOUNT_DIR-$i; then
			sudo umount $RECOVERY_DIR/$MOUNT_DIR-$i
		fi
		rm -rf $RECOVERY_DIR/$MOUNT_DIR-*
	done
}

trap cleanup EXIT ERR SIGHUP SIGINT SIGQUIT SIGTERM

function panic()
{
	if [ $# -gt 0 ]; then
		echo "" >&2
		echo "${PROGNAME}: $@" >&2
		echo "" >&2
	fi

	echo build error, bye.

	exit 1
}

function file_validate()
{
	local file

	file=$(eval echo \$1)
	[ -d ${file} ] || panic "$i file \"$file\" does not exist"
	[ -r ${file} ] || panic "$i \"$file\" is not readable"
	[ -s ${file} ] || panic "$i \"$file\" is empty"
}

function suser() {
	echo
	echo To continue, superuser credentials are required.
	sudo -k || panic "failed to kill superuser privilege"
	sudo -v || panic "failed to get superuser privilege"
}

function compute_round_quotient()
{
	local total_size=$1
	local unit_size=$2

	[ ${unit_size} -gt 0 ] || panic "bad unit_size ${unit_size} in compute_round_quotient()"
	expr \( ${total_size} + ${unit_size} - 1 \) / ${unit_size}
}

function file_bytes() {
	local filename=$1

	stat --dereference --format="%s" ${filename} ||
	panic "unable to stat \"${filename}\""
}

function script_update()
{
	echo "$@" >> ${CURRENT_SCRIPT}
}

function get_current_path()
{
	echo $(cd "$(dirname "$1")" && pwd)
}

function parseargs()
{
	[ $# -lt 1 ] && usage "no update type specified"

	UPTYPE=$1

	if [ "${UPTYPE}" = sdcard -o "${UPTYPE}" = ota ]; then
		LOAD_COMMAND="load \${devtype} \${devnum}:\${distro_bootpart}"
	elif [ "${UPTYPE}" = tftp ]; then
		LOAD_COMMAND=tftp
	else
		usage "no valid update type specified"
	fi

	SOURCE_FILES_PATH=$2
	RECOVERY_DIR=${SOURCE_FILES_PATH}/${UPTYPE}
}

function compile_script() {
	local scr_name=$1
	local description="$1"

	mkimage -A arm64 -O linux -T script -C none -a 0 -e 0 -n "${description}" \
		-d ${CURRENT_SCRIPT} ${RECOVERY_DIR}/$scr_name.scr ||
	panic "failed to compile image for \"${CURRENT_SCRIPT}\""
}

function create_top_script()
{
	CURRENT_SCRIPT=${RECOVERY_DIR}/${TOP_SCRIPT}.cmd
	cp /dev/null ${CURRENT_SCRIPT}

	script_update "# Sophgo ${UPTYPE} update U-Boot script"
	script_update "# Created $(date)"
	script_update ""
	script_update "echo update SPI flash"
	script_update "${LOAD_COMMAND} ${SCRIPT_ADDR} ${OTA_PATH}$(basename ${SPIFCMD_SCRIPT} .cmd).scr"
	script_update "source ${SCRIPT_ADDR}"
	script_update ""
	script_update "while true; do;"
	script_update "echo \"Please remove the installation medium, then reboot\"; sleep 0.5; done;"

	compile_script $(basename ${CURRENT_SCRIPT} .cmd)
}

function create_spif_script()
{
	CURRENT_SCRIPT=${RECOVERY_DIR}/${SPIFCMD_SCRIPT}.cmd
	cp /dev/null ${CURRENT_SCRIPT}

	cp ${SOURCE_FILES_PATH}/fip.bin ${RECOVERY_DIR}
	touch ${RECOVERY_DIR}/BOOT


	if [ ! -e ${SOURCE_FILES_PATH}/spi_flash.bin ]; then
		echo "no SPI flash image"
	else
		cp ${SOURCE_FILES_PATH}/spi_flash*.bin ${RECOVERY_DIR}

		script_update "# SPI flash image"
		script_update ""
		script_update "${LOAD_COMMAND} ${IN_ADDR} ${OTA_PATH}spi_flash.bin"
		script_update "if test \$? -eq 0; then"
		script_update "sf probe"
		script_update "if test \$? -ne 0; then"
		script_update "while true; do; echo \"ERROR: SPI flash not exist\"; sleep 0.5; done; fi;"
		script_update ""
		script_update "sf update ${IN_ADDR} 0x0 0x1000000;"
		script_update ""
		script_update "echo SPI flash update done"
		script_update "while true; do;"
		script_update "echo \"Please remove the installation medium, then reboot\"; sleep 0.5; done; fi;"
	fi

	compile_script $(basename ${CURRENT_SCRIPT} .cmd)
}

function init()
{
	echo generating update files

	if [ -d ${RECOVERY_DIR} ];then
		rm -rf ${RECOVERY_DIR}

	fi

	mkdir -p ${RECOVERY_DIR} || panic "unable to create \"${RECOVERY_DIR}\""

	create_top_script
	create_spif_script
}

parseargs "$@"

echo start building ...
suser
init
# continue to add more command to emmc script
