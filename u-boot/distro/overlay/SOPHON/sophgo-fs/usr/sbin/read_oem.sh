#!/bin/bash

if [ ! -d "/factory/" ];then
    mkdir /factory
fi

OEM_file="/factory/OEMconfig.ini"

echo "[base]" > $OEM_file

echo 0 > /sys/block/mmcblk0boot1/force_ro

dd if=/dev/mmcblk0boot1 of=sn.bin count=17 bs=1 skip=0
sn=$(xxd -p sn.bin | xxd -r -p && echo '')
echo "SN = $sn" >> $OEM_file
rm -f sn.bin

dd if=/dev/mmcblk0boot1 of=dev_sn.bin count=17 bs=1 skip=32
dev_sn=$(xxd -p dev_sn.bin | xxd -r -p && echo '')
echo "DEVICE_SN = $dev_sn" >> $OEM_file
rm -f dev_sn.bin

dd if=/dev/mmcblk0boot1 of=mac0.bin count=6 bs=1 skip=64
mac0=$(xxd -p mac0.bin)
echo "MAC0 = $mac0" >> $OEM_file
rm -f mac0.bin

dd if=/dev/mmcblk0boot1 of=mac1.bin count=6 bs=1 skip=80
mac1=$(xxd -p mac1.bin)
echo "MAC1 = $mac1" >> $OEM_file
rm -f mac1.bin

dd if=/dev/mmcblk0boot1 of=product_type.bin count=1 bs=1 skip=96
product_type=$(xxd -p product_type.bin)
echo "PRODUCT_TYPE = 0x$product_type" >> $OEM_file
rm -f product_type.bin

dd if=/dev/mmcblk0boot1 of=module_type.bin count=16 bs=1 skip=112
module_type=$(xxd -p module_type.bin | xxd -r -p && echo '')
echo "MODULE_TYPE = $module_type" >> $OEM_file
rm -f module_type.bin

dd if=/dev/mmcblk0boot1 of=interface.bin count=1 bs=1 skip=128
interface=$(xxd -p interface.bin)
echo "INTERFACE_FLAG = 0x$interface" >> $OEM_file
rm -f interface.bin

dd if=/dev/mmcblk0boot1 of=aging_flag.bin count=1 bs=1 skip=129
aging_flag=$(xxd -p aging_flag.bin)
echo "AGING_FLAG = 0x$aging_flag" >> $OEM_file
rm -f aging_flag.bin

dd if=/dev/mmcblk0boot1 of=vender.bin count=16 bs=1 skip=144
vender=$(xxd -p vender.bin | xxd -r -p && echo '')
echo "VENDER = $vender" >> $OEM_file
rm -f vender.bin

dd if=/dev/mmcblk0boot1 of=dts_type.bin count=32 bs=1 skip=160
dts_type=$(xxd -p dts_type.bin | xxd -r -p && echo '')
echo "DTS_TYPE = $dts_type" >> $OEM_file
rm -f dts_type.bin

dd if=/dev/mmcblk0boot1 of=hw_version.bin count=16 bs=1 skip=192
hw_version=$(xxd -p hw_version.bin | xxd -r -p && echo '')
echo "HW_VERSION = $hw_version" >> $OEM_file
rm -f hw_version.bin

dd if=/dev/mmcblk0boot1 of=product.bin count=16 bs=1 skip=208
product=$(xxd -p product.bin | xxd -r -p && echo '')
echo "PRODUCT = $product" >> $OEM_file
rm -f product.bin

dd if=/dev/mmcblk0boot1 of=chip.bin count=16 bs=1 skip=224
chip=$(xxd -p chip.bin | xxd -r -p && echo '')
echo "CHIP = $chip" >> $OEM_file
rm -f chip.bin

# dd if=/dev/mmcblk0boot1 of=ddr_type.bin count=16 bs=1 skip=272
# ddr_type=$(xxd -p ddr_type.bin | xxd -r -p && echo '')
# echo "DDR_TYPE = $ddr_type" >> $OEM_file
# rm -f ddr_type.bin

# dd if=/dev/mmcblk0boot1 of=board_type.bin count=16 bs=1 skip=288
# board_type=$(xxd -p board_type.bin | xxd -r -p && echo '')
# echo "BOARD_TYPE = $board_type" >> $OEM_file
# rm -f board_type.bin

# dd if=/dev/mmcblk0boot1 of=bom.bin count=16 bs=1 skip=304
# bom=$(xxd -p bom.bin | xxd -r -p && echo '')
# echo "BOM = $bom" >> $OEM_file
# rm -f bom.bin

# dd if=/dev/mmcblk0boot1 of=ex_module.bin count=16 bs=1 skip=336
# ex_module=$(xxd -p ex_module.bin | xxd -r -p && echo '')
# echo "EX_MODULE_TYPE = $ex_module" >> $OEM_file
# rm -f ex_module.bin

# dd if=/dev/mmcblk0boot1 of=algorithm.bin count=16 bs=1 skip=384
# algorithm=$(xxd -p algorithm.bin | xxd -r -p && echo '')
# echo "ALGORITHM = $algorithm" >> $OEM_file
# rm -f algorithm.bin

# dd if=/dev/mmcblk0boot1 of=date_production.bin count=16 bs=1 skip=400
# date_production=$(xxd -p date_production.bin | xxd -r -p && echo '')
# echo "DATE_PRODUCTION = $date_production" >> $OEM_file
# rm -f date_production.bin

# dd if=/dev/mmcblk0boot1 of=pwd_ssh.bin count=16 bs=1 skip=416
# pwd_ssh=$(xxd -p pwd_ssh.bin | xxd -r -p && echo '')
# echo "PASSWORD_SSH = $pwd_ssh" >> $OEM_file
# rm -f pwd_ssh.bin

# dd if=/dev/mmcblk0boot1 of=username.bin count=16 bs=1 skip=432
# username=$(xxd -p username.bin | xxd -r -p && echo '')
# echo "USERNAME = $username" >> $OEM_file
# rm -f username.bin

# dd if=/dev/mmcblk0boot1 of=password.bin count=16 bs=1 skip=448
# password=$(xxd -p password.bin | xxd -r -p && echo '')
# echo "PASSWORD = $password" >> $OEM_file
# rm -f password.bin

echo 1 > /sys/block/mmcblk0boot1/force_ro
