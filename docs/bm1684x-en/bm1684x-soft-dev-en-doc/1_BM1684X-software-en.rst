
Preface
========

Document Overview
-------------------

This document provided a detailed introduction of |Product| series Intelligent computing module (development board included), such as: appearance features, application scenarios, device parameters data, electrical characteristics, supporting software and using environment, so that device users and developers could get a full picture of our products ( |Product| series Intelligent computing module).Developers and device users can carry out installation, debugging, deployment, maintenance and other works by following this manual.

Target Readers
---------------


-  FAE engineer, Pre-sales engineer of Sophon

-  Engineer of ecological cooperation partner company

-  R&D engineer of customer enterprise

Convention Symbol, Sign, Terminology Explanation
----------------------------------------------------

Meaning of symbols and sign may appear in this documentation are as follows:

+--------------+--------------------------------------------------------+
| |image1|     | Very dangerous, may cause casualty or serious injury,  |
| Danger       | if not avoided.                                        |
+--------------+--------------------------------------------------------+
| |image2|     | Indicates a moderate or low potential hazard which,    |
| Warning      | if not avoided, could result in minor                  |
|              | or moderate personal injury.                           |
+--------------+--------------------------------------------------------+
| |image3|     |Potential risk, equipment damage, data losing,          |
|              |performance reduction, and unpredictable consequence    |
| Attention    |may happen while ignoring this part of text.            |
+--------------+--------------------------------------------------------+
| |image4|     |Anti-static sign, means electrostatic                   |
| Antistatic   |sensitive equipment or operation.                       |
+--------------+--------------------------------------------------------+
| |image5|     | Electric shock protection sign,                        |
| High Voltage | means high voltage here,                               |
| Risk         | need precaution.                                       |
+--------------+--------------------------------------------------------+
| |image6|     | Resolve your problem or save your time by doing this.  |
| Tricks       |                                                        |
+--------------+--------------------------------------------------------+
| |image7|     | Additional information to make a clear explanation,    |
| Illustration | emphasizes this part.                                  |
+--------------+--------------------------------------------------------+

Abbreviations
--------------

+-----------------+----------------------------+
| JPU             | JPEG Process Unit          |
+-----------------+----------------------------+
| VPP             | Video Post Process         |
+-----------------+----------------------------+
| VPU             | Video Process Unit         |
+-----------------+----------------------------+


Amend Record
-------------

+-------------------+--------------+-------------+--------------------+-------------------+
| Document Version  | Release Date | Amend       | Corresponding      | Corresponding     |
|                   |              | Record      | Hardware Version   | Software Version  |
+-------------------+--------------+-------------+--------------------+-------------------+
| V0.1              | 2022-07-13   | First       | BM1684X EVB:V1.1   | 0.2.3             |
|                   |              | Edition     |                    |                   |
+-------------------+--------------+-------------+--------------------+-------------------+


Legal Declaration
------------------

Copyright ©2022 SOPHGO.

All intellectual property rights to this product manual and its contents are reserved.Reproduction or distribution to third parties is prohibited unless specifically authorized.For any acts that infringe the company`s copyright and other intellectual property rights, the company reserves the right to pursue its legal responsibility in accordance with the law.

This product line will have constant updates and iterations, and we will periodically review the contents of this product manual for inevitable corrections, deletions, and additions that will occur in subsequent versions.

We reserve the right to make technical improvements, documentation changes, product improvement upgrades, additions or reductions in product models and features without prior notice.


Hardware Cognitive
===================

Board Instructions
------------------------

|Product| The Intelligent computing module refers to a board that includes core components such as: BM1684X, LPDDR4X, eMMC.Shown in the feature below.

|Product| EVB front

   .. image:: ./_static/image8.png
      :width: 8in
      :height: 6in

|Product| EVB back

   .. image:: ./_static/image9.png
      :width: 8in
      :height: 5in

The location of each component is indicated in the following diagram:

   .. image:: ./_static/image93.png
      :width: 12in
      :height: 10in

To facilitate the following description, this board is referred to as "core board".

Accessory Installation
-----------------------


a. One USB to UART cable:The UART0 (UART for BM1684X) from the core board is the debug port, TTL electric level, Baud rate 115200, 8-bits data, 1-bit stop bit, no parity check, no hardware flow control.

b. One Ethernet cable: connect to Ethernet port 0 (eth0), default setting DHCP, so by puting |Product| and your debugger under the same router through eth0 makes it easier to control |Product|.

c. One SD card: for flashing or debugging, 8GB/class10 or larger is recommended.

d. |image8|\ Power supply to match your base board design: if you use the reference baseboard we provide, the matching DC power supply output is 12V/10A, 5.5*2.1mm ferrule with centeral positive pole.

e. One radiator: please install necessary cooling devices such as heat sinks or fans to avoid abnormal conditions like overheating and shutdown.


Power On
------------

After everything is ready, you can power up the base board, if you use the reference base board we provide, please first plug in the power, and then dial the power button (at this time from the serial terminal should also be able to see the log print), the normal state of the indicator is as follows.


   .. image:: ./_static/image12.png
      :width: 6.27083in
      :height: 4.29167in

Please check your serial port, we have pre-installed Ubuntu 20.04 for |Product|, the initial username and password are "linaro" (no initial password for root user, you need to execute this to set password for root account before using:"sudo passwd root").

   .. code-block:: bash

      bm1684 login: linaro
      Password:
      Welcome to Ubuntu 20.04 LTS (GNU/Linux 5.4.202-bm1684 aarch64)

       * Documentation:  https://help.ubuntu.com
       * Management:     https://landscape.canonical.com
       * Support:        https://ubuntu.com/advantage

       * Super-optimized for small spaces - read how we shrank the memory
         footprint of MicroK8s to make it the smallest full K8s around.

         https://ubuntu.com/blog/microk8s-memory-optimisation
      overlay / overlay rw,relatime,lowerdir=/media/root-ro,upperdir=/media/root-rw/overlay,workdir=/media/root-rw/overlay-workdir 0 0
      /dev/mmcblk0p5 /media/root-rw ext4 rw,relatime 0 0
      /dev/mmcblk0p4 /media/root-ro ext4 ro,relatime 0 0

      Last login: Mon Jul 11 11:30:26 CST 2022 from 192.168.0.105 on pts/0
      linaro@bm1684:~$

Use "ifconfig" or "ip a" command to  check IP address:

   .. code-block:: bash

      ifconfig
      ip a


If you need to config ststic IP address manually, you can modify "/etc/netplan/01-netcfg.yaml" configuration file as follows, and enable the modified configuration file:

   .. code-block:: bash

      $ cat /etc/netplan/01-netcfg.yaml
      network:
              version: 2
              renderer: networkd
              ethernets:
                      eth0:
                              dhcp4: no                        # Static IP needs to be changed to "no", dynamic IP is "yes".
                              addresses: [192.168.1.100/24]    # Put IP in the brackets, dynamic IP put blank.
                              optional: yes
                              dhcp-identifier: mac             # If static IP, delete this line.
                      eth1:
                              dhcp4: no
                              addresses: [192.168.150.1/24]
                              optional: yes
                      enp3s0:
                              dhcp4: yes
                              addresses: []
                              dhcp-identifier: mac
                              optional: yes
      $ sudo netplan try      # Testing the configuration can be used.
      $ sudo netplan apply    # Apply the newest config


Once you get the IP address, you can login by using ssh on port 22, username and password are also "linaro".

   .. code-block:: bash

      ssh linaro@your_ip

To avoid file system corruption, it is recommended to use command "sudo power off" when shutting down rather then directly cut the power.\ |image9|


The core board has two NICs, eth0 is DHCP by default, so you need to get the IP by the above method. eth1 is configured as static IP: 192.168.150.1 by default.

Software Installation
======================

Check The Pre-installed Version
---------------------------------

|Product| has pre-installed the system software at the factory and its version can be checked under Ubuntu with the following command:

a. Check Linux kernel version: bm_version

   .. code-block:: bash

      $ bm_version
      sophon-mw-soc-sophon-ffmpeg : 0.2.3
      sophon-mw-soc-sophon-opencv : 0.2.3
      sophon-soc-libsophon : 0.2.3
      KernelVersion : Linux bm1684 5.4.202-bm1684 #2 SMP PREEMPT Wed Jul 6 01:55:57
      UTC 2022 aarch64 aarch64 aarch64 GNU/Linux
      HWVersion: 0x00
      MCUVersion: 0x03

   sophon-mw-soc-sophon-ffmpeg, sophon-mw-soc-sophon-opencv, sophon-soc-libsophon, SOPHON SDK version,KernelVersion is Kernel version information, 5.4.202 means specifica version of Linux Kernel, the timestamp in the second half represents the build time.
   MCUVersion means MCU firmware version。


Software Upgrade
-----------------

|Product| provides three types of updates: SD card flush, file replacement and OTA upgrade. Among them, SD card flush will rewrite the whole eMMC, which means all the data you stored in eMMC will be lost. But it is the cleanest and the most reliable way among them. Theoretically, as long as your |Product| has no hardware damage, you can do the SD card flush. The file replacement  method is to upgrade the bootloader, kernel and other software by replacing the corresponding files under Ubuntu. This method has risks, such as version matching problem between different software components, file corruption, etc. The following describes the operation of each of the three software update methods.

a. SD card flush

Please format the SD card with a size of 1GB or more to FAT32 (if there are multiple partitions on the SD card, only the first one can be used)

Please download the newest flush package of |Product|, see FAQ section for the address:

First, extract the downloaded zip package to the root directory of your SD card. Confirm files are as follows (not necessarily the same number):

   .. image:: ./_static/image18.png
      :width: 4.20625in
      :height: 2.49295in

Then shutdown the |Product|, put SD card in, connect to a serial terminal, power on the |Product|. |Product| will enter the brushing process automatically as you can see:

   .. image:: ./_static/image19.png
      :width: 6.27083in
      :height: 2.69444in

Generally, this process takes about 3 minutes, after that, you can see a notice of "Remove SD card and reboot |Product|", do it as it says:

   .. image:: ./_static/image20.png
      :width: 4.23438in
      :height: 0.83192in

Attention: important actions will be performed at the first time booting the Ubuntu system after flushing was finished, such as initializing the file system. So do not cut off the power casually, execute "sudo poweroff" command to shut down Ubuntu after entering the command line.

b. replacement files

The file replacements are performed under Ubuntu, either using a serial port or an SSH terminal. The following describes how to replace each component separately.

Replace bootloader: upload spi_flash.bin to |Product|, execute "sudo flash_update -i ./spi_flash.bin -b 0x6000000",
you can see the following log after success.

   .. image:: ./_static/image21.png
      :width: 6.26772in
      :height: 2.13889in

Run "flash_update" for help:

   .. image:: ./_static/image90.png
      :width: 8.39in
      :height: 4.04in

Kernel replacement: put emmcboot.itb into /boot to replace document with the same name, then run "sudo reboot".

Replacement of bmnnsdk2 run-time enviorment:bmnnsdk2 run-time enviorment is located under /opt folder, replace the entire update package you got (usually a zip file named opt.tgz), remrmber the relative path when unpacking.

.. warning::

   It may cause files damage, as soon as you cut the power after doing the above,
   do acts like: "sync", "sudo reboot" or "sudo poweroff". \ |image10|

c. OTA upgrade

Follow the steps below to perform an OTA upgrade:

1. Using upgrade package of sdcard as ota upgrade package, copy all files to /data/ota directory.

2. Copy local_update.sh script to |Product| under /data/ota directory.

3. Execute commands below:

   .. code-block:: bash

      sudo -i
      ./local_update.sh md5.txt

   If permission denied while executing local_update.sh, use command below to authorize:

   .. code-block:: bash

      chmod +x local_update.sh

.. code-block:: shell
   :name: local_update

   #!/bin/bash

   if [ $# -lt 1  ] ; then
           echo "need md5 file"
           exit
   fi

   echo ">>>>>start upgrade app package..."

   echo ">>>>>md5sum check ..."

   basepath=$(cd `dirname $0`; pwd)
   echo $basepath
   cd $basepath

   md5sum -c $1 > ota_versino.txt
   ret=$?
   count=$#
   rootpath="/data/ota"
   if [ $ret -ne 0 ]; then
       echo ">>>>> upgrade package is wrong stop upgrade..."
       echo "update failed"
   else
       echo ">>>>>upgrade package starting..."
       # backup user information
       echo ">>>>>backup user information..."
       rm -rf ${rootpath}/public_ota/backup
       mkdir -p ${rootpath}/public_ota/backup

       # update boot-loader
       #sudo flash_update -i spi_flash.bin -b 0x06000000 -f 0x0
       #sudo flash_update -i fip.bin -b 0x6000000 -f 0x40000
       # upgrade mcu
       #sudo mcu-util-aarch64 upgrade 1 0x17 sa5-mcu*.bin

       # private ota :boot-recovery /data/ota/startup.sh\nprivate_update"
       echo -e "boot-recovery\n/DATA/ota" > /dev/mmcblk0p3
       echo "update success"

       reboot
   fi


|image11|\ Replace MCU firmware: There is an MCU on the core board that is responsible for the power-on timing of |Product| and other important tasks, and its firmware can only be upgraded by the following command, not by SD card. If the firmware of this MCU is programmed incorrectly, it will cause |Product| fail to power on, so it can only be repaired by a special programmer, so please operate cautiously and usually it is not necessary to upgrade it.
#Commands:
sudo mcu-util-aarch64 upgrade 1 0x17 bm1686evb-mcu.bin
#Execute this after upgrade finished:
sudo poweroff
(Serial would print NOTICE: "CPU0 bm_system_off", after finishing shutdown action. Suddenly fan of the box would be a little noisy. This sound means box is rebooting.)


System Software Components
===========================

Start-up Process
-----------------

The system software of |Product| is a typical embedded ARM64 Linux,
consis of bootloader、kernel、ramdisk and Ubuntu 20.04,
When booting, execute the following in order:

   .. image:: ./_static/image94.png
      :width: 6.27083in
      :height: 0.90278in

among which boot ROM, bootloader were built based on arm-trusted-firmware and u-boot, kernel was build on Linux 5.4 branch, Ubuntu 20.04 was built based on Ubuntu offical arm64 source,
GUI and its relative modules were not included.

eMMC Partition
---------------

+------------------------+-----------------+-------------+--------------------------+
| Partition device files | Mount           | File System | Contents                 |
+------------------------+-----------------+-------------+--------------------------+
| /dev/mmcblk0p1         | /boot           | FAT32       | Kernel and ramdisk image |
+------------------------+-----------------+-------------+--------------------------+
| /dev/mmcblk0p2         | /recovery       | EXT4        | Recovery mode image      |
+------------------------+-----------------+-------------+--------------------------+
| /dev/mmcblk0p3         | none            | none        | Configuration, not used  |
+------------------------+-----------------+-------------+--------------------------+
|| /dev/mmcblk0p4        || /media/root-ro || EXT4       || Ubuntu 20.04 System`s   |
||                       ||                ||            || read-only section       |
+------------------------+-----------------+-------------+--------------------------+
|| /dev/mmcblk0p5        || /media/root-rw || EXT4       || Ubuntu 20.04 System`s   |
||                       ||                ||            || read-write section      |
+------------------------+-----------------+-------------+--------------------------+
|| /dev/mmcblk0p6        || /opt           || EXT4       || Driver and runtime      |
||                       ||                ||            || enviorment of sdk       |
+------------------------+-----------------+-------------+--------------------------+
|| /dev/mmcblk0p7        || /data          || EXT4       || User data and SOPHON    |
||                       ||                ||            || pre-install software    |
||                       ||                ||            || package, not used yet   |
+------------------------+-----------------+-------------+--------------------------+

A note about partitions 4 and 5:
partition 4 stores Ubuntu 20.04 critical part of the system, mounted as read-only,
partition 5 stores Ubuntu 20.04 files generated during runtime, mounted as readable and writeable.
The two partitions are aggregated via overlayfs and mounted as the root of the system, as shown in the following figure:

   .. image:: ./_static/image23.png
      :width: 3.85833in
      :height: 0.99352in

Users usually do not need to pay attention to this detail, for daily use is transparent, the normal operation of the root directory files can be, but when using commands such as df to view partition utilization and other operations please know here, the following figure:

   .. image:: ./_static/image24.png
      :width: 3.99583in
      :height: 2.18464in

Docker
----------

Core board has pre-installed docker service, you can run "docker info" to check docker status.
Different with default settings, docker root directory was settled to /data/docker.

File System Support
--------------------

If you use a reference backplane, when a USB flash drive or removable hard drive is inserted (USB power capability needs to be considered), the storage device will be recognized as /dev/sdb1 or nodes like this,
the same with PC Linux.
FAT、FAT32、EXT2/3/4、NTFS are supported in this system. |Product| does not support auto-mount, so you need mount it on your own by doing:
"sudo mount /dev/sdb1 /mnt".
Pre-installed kernel only support read action while accessing NTFS formatted storage devices, to make it writeable, you need to install ntfs-3g software package, please refer to \ https://wiki.debian.org/NTFS\.
After writing data, use "sync" or "umount" operation to make sure your data was successfully writing down,
for avoiding data losing, do not power down |Product| violently, use "sudo poweroff" command.

Modify SN And MAC Addresses
----------------------------

SN and MAC addresses of |Product| were stored in EEPROM of MCU, you can modify them by following way:

Unlock MCU EEPROM:

   .. code-block:: bash

      sudo -i
      echo 0 > /sys/devices/platform/5001c000.i2c/i2c-1/1-0017/lock

Write SN:

   .. code-block:: bash

      echo "HQATEVBAIAIAI0001" > sn.txt
      dd if=sn.txt of=/sys/bus/nvmem/devices/1-006a0/nvmem count=17 bs=1

Write MAC (both NICs have there own MAC):

   .. code-block:: bash

      echo "E0A509261417" > mac0.txt
      xxd -p -u -r mac0.txt > mac0.bin
      dd if=mac0.bin of=/sys/bus/nvmem/devices/1-006a0/nvmem count=6 bs=1 seek=32
      echo "E0A509261418" > mac1.txt
      xxd -p -u -r mac1.txt > mac1.bin
      dd if=mac1.bin of=/sys/bus/nvmem/devices/1-006a0/nvmem count=6 bs=1 seek=64

Relock MCU EEPROM, to avoid unexpectable file change:

   .. code-block:: bash

      echo 1 > /sys/devices/platform/5001c000.i2c/i2c-1/1-0017/lock

New MAC address will become effective after rebooting the system.

R&W eFuse
-------------

eFuse Addressing
~~~~~~~~~~~~~~~~~

|Product| has eFuse 4096bit inside, organized by 128*32bit, so the addressing scope is 0~127, each address represents a 32bit memory unit. Each initial value of eFuse is 0, user can change it from 0 to 1, but irreversible. For example: first write 0x1 to address 0 then write 0x2, at last, you will get 0x1|0x2=0x3.

To ensure the reliability of the stored information, the information in eFuse is usually stored in two copies,
called double bit, When either one of the two copies is 1, the corresponding bit is considered to be 1.
means result = copy_a OR copy_b.
There are two kind of storm form:

1. Process double bit in a 32bit mem unit,
   for double bit are made of odd-bit (1、3、5、7……) and even-bit (0、2、4、6……),
   dor instance bit0 and bit1 of the protocol address 0, one of which is 1 to enable secure firewall.
   This form of double bit is used for hardware function control.


2. Some 32bit memory unit and some other memory unit together make double bit.
   Such as: make a statment SN = address[48] OR address[49].
   This kind of double bit is used to define information restore of software.

eFuse Partition
~~~~~~~~~~~~~~~~~

There are some special use of eFuse, just as belows:

   .. list-table::
      :widths: 20 80
      :header-rows: 1

      * - |nbsp| |nbsp| |nbsp| |nbsp| |nbsp| Address
        - |nbsp| |nbsp| |nbsp| |nbsp| |nbsp| Content
      * - | 0
        - | bits[1] | [0]:Enable secure firewall
          | bits[3] | [2]:Prohibit JTAG
          | bits[5] | [4]:Prohibit the use of booting from off-chip SPI flash
          | bits[7] | [6]:Enable secure boot
      * - 1
        - bit[0] | bit[1]:Enable secure key
      * - 2~9
        - 256bit secure key
      * - 10~17
        - 256bit secure key duplicate
      * - 18~25
        - 256bit secure boot used root public key digest
      * - 26~33
        - 256bit secure boot used root public key digest duplicate
      * - 54~57
        - 128bit Customer defined ID
      * - 58~61
        - 128bit Duplicate of customer defined ID
      * - 34~45
        - Chip production test information reserved area
      * - 64~82
        - Chip production test information reserved area

The remaining unspecified areas currently have no specific use and can be used for storage or experimental purposes.

eFuse Tools
~~~~~~~~~~~~~~~

|Product| has a pre-installed eFuse R&W tool, read and write commands are as follows:

sudo efuse -r 0x? -l 0x? #i.e. it is possible to return a number of 32bit values stored starting from that address.

sudo efuse -w 0x? -v 0x? #i.e. specified 32bit value can be written at this address.

Only hexadecimal value are supported above.



Usage Of System API
=====================

Use standerd Linux sysfs, procfs nodes or top tools to get CPU and memory utilize rate of |Product|.
Only some specific interfaces or hardware usage of |Product| will be described below.

Get Core Board`s Serial Number
-------------------------------

Command:

   .. code-block:: bash

      cat /sys/bus/i2c/devices/1-0017/information

Return (json format string):

   .. code-block:: json

      {
              "model": "BM1684X EVB",
              "chip": "BM1684X",
              "mcu": "STM32",
              "product sn": "",
              "board type": "0x20",
              "mcu version": "0x03",
              "pcb version": "0x00",
              "reset count": 0
      }

Get |Product| Chip`s Temperature
----------------------------------

Command:

   .. code-block:: bash

      cat /sys/class/thermal/thermal_zone0/temp

Return info(millidegree Celsius):

   .. code-block:: bash

      38745

It is 38.745 Celsius degree.

The thermal framework for Linux will use this temperature for management:

1. Ordinary version module: when the temperature rises to 85 degrees, the NPU frequency will drop to 80% and the CPU frequency will be downconverted to 1.15GHz; when the temperature drops back to 80 degrees, the NPU frequency will return to 100% and the CPU frequency will return to 2.3GHz; when the temperature rises to 90 degrees, the NPU frequency will drop to the lowest gear; when the temperature rises to 95 degrees, it will automatically shut down.

2. Wide temperature version module: when the temperature rises to 95 degrees, the NPU frequency will drop to 80% and the CPU frequency will be downconverted to 1.15GHz; when the temperature drops back to 90 degrees, the NPU frequency will return to 100% and the CPU frequency will return to 2.3GHz; when the temperature rises to 105 degrees, the NPU frequency will drop to the lowest gear; when the temperature rises to 110 degrees, it will automatically shut down.

In addition, the off-chip MCU uses this temperature as a final insurance mechanism:

1. Ordinary version module: forcing shutdown when the chip junction temperature is greater than 95 degrees and the board temperature is greater than 85 degrees.

2. Wide temperature version module: forced shutdown when the chip junction temperature is greater than 120 degrees.

Get Core Board`s Temperature
------------------------------

Command:

   .. code-block:: bash

      cat /sys/class/thermal/thermal_zone1/temp

Return info(millidegree Celsius):

   .. code-block:: bash

      37375

It is 37.375 Celsius degree.

Usually, the core board temperature is lower then chip temperature front readed.

Get Power Consumption Information
----------------------------------

Command:

   .. code-block:: bash

      sudo pmbus -d 0 -s 0x50 -i

Return:

   .. code-block:: bash

      I2C port 0, addr 0x50, type 0x3, reg 0x0, value 0x0
      ISL68127 revision 0x33
      ISL68127 switch to output 0, ret=0
      ISL68127 output voltage: 749mV
      ISL68127 output current: 2700mA
      ISL68127 temperature 1: 59°C
      ISL68127 output power: 2W → NPU power consumption
      ISL68127 switch to output 1, ret=0
      ISL68127 output voltage: 898mV
      ISL68127 output current: 2900mA
      ISL68127 temperature 1: 58°C
      ISL68127 output power: 2W → CPU/Video etc. power consumption

Use GPIO
------------

|Product| chip contains 3 groups of GPIO controller, each controller has 32 GPIOs, corresponding to Linux device nodes are as follows:

+------------+----------------------+--------------+----------------+
| GPIO       | Linux device         | GPIO Physical| GPIO Logic     |
| Controller | Nodes                | Number       | Number         |
+------------+----------------------+--------------+----------------+
| #0         | /sys/class           | 0 to 31      | 480 to 511     |
|            | /gpio/gpiochip480    |              |                |
+------------+----------------------+--------------+----------------+
| #1         | /sys/class           | 32 to 63     | 448 to 479     |
|            | /gpio/gpiochip448    |              |                |
+------------+----------------------+--------------+----------------+
| #2         | /sys/class           | 64 to 95     | 416 to 447     |
|            | /gpio/gpiochip416    |              |                |
+------------+----------------------+--------------+----------------+

For example, if you need to operate the pin labeled GPIO29 on the circuit diagram, you need to do:

   .. code-block:: bash

      sudo -i
      echo 509 > /sys/class/gpio/export

Then you can operate the nodes under /sys/class/gpio/gpio509 by the standard way.

Please note that since the pins are multiplexed, not all 96 GPIOs can be used, so please check with the hardware design.

Use UART
------------

144pin BTB interface of |Product| provides
3 groups of UART, of which UART0 has effected on bootloader and Linux console port.

Use I2C
-----------

144pin BTB interface of |Product| provides a group of I2C master,
corresponding to /dev/i2c-2 device node, which could use standard I2C tools and API operations.

On our reference base board, |Product| connects to the RTC chip on the base board via this I2C set.

Use PWM
-----------

.. warning::

   TODO: evb board fan speed can not be controlled, need to replace the hardware, to be updated after the hardware perfect this chapter.

144pin BTB interface of|Product| provides a PWM output pin, corresponding to PWM0:

   .. code-block:: bash

      sudo -i
      echo 0 > /sys/class/pwm/pwmchip0/export
      echo 0 > /sys/class/pwm/pwmchip0/pwm0/enable

Configuration:

   .. code-block:: bash

      echo %d > /sys/class/pwm/pwmchip0/pwm0/period
      echo %d > /sys/class/pwm/pwmchip0/pwm0/duty_cycle

Enable:

   .. code-block:: bash

      echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable

This PWM`s output is used as a fan speed control on our reference backplane, and Linux`s thermal framework would automatically adjust the fan speed according to the chip temperature. So you will see "Device or resource busy" error at the first step export.
You need to modify the device tree to disable the corresponding pwmfan node before you can use it freely.

   .. code-block:: dts

      pwmfan: pwm-fan {
         compatible = "pwm-fan";
         pwms = <&pwm 0 40000>, <&pwm 1 40000>; // period_ns
         pwm-names = "pwm0","pwm1";
         pwm_inuse = "pwm0";
         #cooling-cells = <2>;
         cooling-levels = <255 153 128 77 26 1>; //total 255
      };

Fan Speed Measurement
----------------------

.. warning::

   Replace the fan on EVB board for fan speed control.

144pin BTB interface of |Product| provides a pin to measure fan speed, it can sample the fan speed output square wave frequency, and the actual speed can be calculated by comparing the frequency to speed conversion formula in the fan manual.

Enable:

   .. code-block:: bash

      sudo -i
      echo 1 > /sys/class/bm-tach/bm-tach-0/enable

Reading square wave frequency:

   .. code-block:: bash

      cat /sys/class/bm-tach/bm-tach-0/fan_speed

A netlink event is also provided to alert when the fan stops, sample code can be found in bsp-sdk/linux-bitmain/tools/fan_alert.

Query Memory Usage
--------------------

|Product| carrys 16GB DDR on board, which can be divided into three categories:

1. Part one, managed by kernel, could be called by using normal APIs like: malloc, kmalloc, etc.

2. Part two, managed by ION, reserved for TPU、VPU、VPP, for allocating this part of memort, by using interface ION of ionctl or interfaces provided by bmlib in bmnnsdk2.

3. Part three, reserved for firmware, users can`t alloc anyway.

You can check usage of every part by doing this:

1. System memory:

   .. code-block:: bash

      linaro@bm1684:~$ free -h
                    total        used        free      shared  buff/cache   available
      Mem:          6.6Gi       230Mi       6.2Gi       1.0Mi       230Mi       6.3Gi
      Swap:            0B          0B          0B

2. ION memort

   .. code-block:: bash

      sudo -i
      root@bm1684:~# cat /sys/kernel/debug/ion/bm_npu_heap_dump/summary  | head -2
      Summary:
      [0] npu heap size:4141875200 bytes, used:0 bytes        usage rate:0%, memory usage peak 0 bytes

      root@bm1684:~# cat /sys/kernel/debug/ion/bm_vpu_heap_dump/summary  | head -2
      Summary:
      [2] vpu heap size:2147483648 bytes, used:0 bytes        usage rate:0%, memory usage peak 0 bytes

      root@bm1684:~# cat /sys/kernel/debug/ion/bm_vpp_heap_dump/summary  | head -2
      Summary:
      [1] vpp heap size:3221225472 bytes, used:0 bytes        usage rate:0%, memory usage peak 0 bytes

   As above, there are usually 3 ION
   heaps (i.e., the three reserved memory areas), as the names suggest, are for NPU, VPU, and VPP use. The above example only prints the beginning of each heap usage information
   Address and size information of each piece of buffer would be shown if you concatenate the whole summary file.


System Customize
==================

|Product| base board could be designed on your own, so it is convenient for you to customize kernel, Ubuntu 20.04 system and generate your own SD card or tftp flushing package by using BSP SDK provided by us,

If you just want to deploy your own business software and do not involve hardware modifications, then for decoupling reasons, it is recommended that you package your business software into a deb installer.

For example, you can include your business software executable, dependency libraries, boot-up services, etc.
The deb installer can also include a script that is automatically executed during installation to do some configuration file changes and replacements during installation.

This allows you to install, uninstall, and upgrade your business software separately, avoiding dependency issues with our system package versions, and making it more user-friendly for batch updates after deployment.

Refer to Debian \ `offical document <https://wiki.debian.org/Packaging/Intro>`__\  for more details about creating a deb installer.

File Structure
---------------

The SOPHONSDK contains two parts, please download from https://github.com/sophgo, one part is the source file published on the github website,
and the other part is binary files which will not changed basically.
To avoid affecting git efficiency, is published through Baidu Net Disk.
Merge two parts of files by following the description in README.md of the source file, you will see the following file structure.

   ::

      top
      ├── bootloader-arm64
      │   └── scripts
      │       └── envsetup.sh → Compile Script Entrance
      │   ├── trusted-firmware-a → TF-A Source Code
      │   ├── u-boot → u-boot Source Code
      │   └── ramdisk
      │   │   └── build → cpio file of ramdisk and u-boot script
      │   └── distro → Ubuntu 20.04 customized package
      ├── distro
      │   └── distro_focal.tgz → Ubuntu 20.04 base package
      ├── gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu → Cross-compilation tool chain
      └── linux-arm64 → kernel source code


Cross-compilation
-------------------

Recommend using Ubuntu 20.04 to operate Cross-compilation, architectures other than X86_64 are not supported.
Please set aside at least 10GB of free disk space and please install some necessary tools first:

..

   .. code-block:: bash

      sudo apt install cmake libssl-dev fakeroot dpkg-dev device-tree-compiler u-boot-tools

..

After intering the BSP SDK, execute following commands to build flushing package which is used on SD card and tftp:

   .. code-block:: bash

      source bootloader-arm64/scripts/envsetup.sh
      build_bsp
      # build_update tftp must be executed after build_bsp
      build_update tftp

Because the script uses sudo, you may be prompted to enter the current user password during compilation.
If you encounter any problems when compiling for the first time, please check the compilation log carefully if the result does not meet your expectations, and if you encounter a prompt that a certain tool cannot be found, use "apt install".

Compilation result will be restored at install/soc_bm1684, the following documents (folders) are highlighted.

   ::

      sdcard → SD card flushing package, refers to section 2.2 for usage instructions a:

      tftp → tftp flushing package, refer to section 7.4 for usage instructions:

      emmcboot.itb →  kernel, ramdisk and dtb are packaged together, refer to section 2.2 for usage instructions b:

      spi_flash.bin → bootloader, refers to section 2.2 for usage instructions b:

      rootfs → root file system content:

Use following commands, if you want to update kernel.

   .. code-block:: bash

      build_kernel
      build_ramdisk uclibc emmc

Up to now you can get a new emmcboot.itb. Unless you know exactly how to operate it, otherwise we don`t recommend you enter linux-bitmain directory and input make commands.

The compiled results of the kernel are in the following path:

   ::

      linux-arm64/build/bm1684/normal

The compiled ko can be found at the following path:

   ::

      linux-arm64/build/bm1684/normal/modules/lib/modules/5.4.202-bm1684/kernel

Contents are identical in two different path, and has wrapped into flushing package.

The compiled linux-header installation package which is used to compile the kernel module on the board, could be found in the following path:
   ::

      linux-arm64/build/bm1684/normal/bm1684_asic/linux-dev

The default is already typed into the refresh package, i.e. the /home/linaro/linux-dev directory on the board.

Modify Kernel
--------------

Kernel configuration file located at:

   linux-arm64/arch/arm64/configs/bitmain_bm1684_normal_defconfig

Attention:  Modifying the kernel config may cause your kernel to be incompatible with the driver files we distributed via binary way, such as: bmtpu.ko, vpu.ko and jpu.ko at /opt/sophon/libsophon-current/data/.

Standard |Product| uses device tree file in:

   linux-arm64/arch/arm64/boot/dts/bitmain/bm1684x_evb_v0.0.dts

Execute after modification:

   .. code-block:: bash

      build_kernel
      build_ramdisk uclibc emmc

Includes all modifications of kernel code and device tree, in iemmcboot.itb you have got.
Put it into /boot directory on board card and reboot.
All modifications would be effective.

Be aware that if you deploy your own emmcboot.itb to the board, it may cause the pre-installed content on the board to be inconsistent with your current kernel image version.

Put two directories which is on compile host install/soc_bm1684/rootfs/: /home/linaro/linux-dev and /lib/module to board card, if you encounter compatibility issues.

There will be no issue if using tftp or SD card flushing package, because of the synchronization update of these files while flushing package is built.

If you use some kind variable of |Product|, you can find a corresponding device tree file by the following way:

   Observe the log printed by u-boot in the UART log after booting:

      .. code-block:: bash

         ...
         ...
         NOTICE:  BL31: Built : 07:47:33, Jun 29 2022
         INFO:    ARM GICv2 driver initialized
         INFO:    BL31: Initializing runtime services
         INFO:    BL31: Preparing for EL3 exit to normal world
         INFO:    Entry point address = 0x308000000
         INFO:    SPSR = 0x3c9
         found dtb@130: bitmain-bm1684x-evb-v0.0
         Selecting config 'bitmain-bm1684x-evb-v0.0'
         ...
         ...

   Look at the line with "Selecting config",
   would know device tree source file is **bm1684x_evb_v0.0.dts** at linux-bitmain/arch/arm64/boot/dts/bitmain/.

Modify Ubuntu 20.04
--------------------

The genertion process of Ubuntu 20.04 system is as follow:

1. distro/distro_focal.tgz is a pure base package from Ubuntu offical website, debian/distro_focal_20220328.tgz is the base package modified by us.

2. bootloader-arm64/distro/overlay includes |Product| changes to base package, will overwrite the path of the same name to the base package.

3. Update ko and other files into it while compiling kernel.

4. If there is an opt.tgz file in the install/soc_bm1684 directory, it will be used as the contents of the /opt directory during the flash package generation.

5. If there is a data.tgz file in the install/soc_bm1684 directory, it will be used as the contents of the /data directory during the brush package generation.

So you can add your own changes to overlay/soc_bm1684_asic_newos, such as putting in some tools and software, modifying the Ethernet configuration file, etc., and then regenerate the package.
If you got one or more deb package want to pre-install into Ubuntu 20.04, here are two measurements:

a. If the deb package is simple, you can just extract it and copy the files inside to the corresponding directory under overlay/soc_bm1684_asic_newos

b. Put the deb package directly into the overlay/soc_bm1684_asic_newos/root/post_install/debs directory, then |Product| will install all these deb packages when you boot up your computer for the first time after flushing.


Compile Kernel Module On |Product|
------------------------------------

You can also choose to compile the kernel module directly on the |Product| board,
which can save the trouble of building a cross-compiler environment as described above. The steps are as follows:

1. "uname -r" get versiuon of kernel, match with version information in /home/linaro/linux-dev and /lib/modules, make sure the consistency of them.

2. You need to do extra work, because of the disadvantage of kernel doing make bindeb-pkg in cross-compiling enviorment:

   a. Use the date command to check the current system time. If it is too different from the actual time, please set it to the current time, such as:

      .. code-block:: bash

         sudo date -s "01:01:01 2021-03-01"

   b. Check whether exists /home/linaro/linux-dev/debs/install.sh, if yes, execute it,

   c. If not, do opera below on your own:

      .. code-block:: bash

         sudo dpkg -i /home/linaro/linux-dev/linux-headers-*.deb
         sudo mkdir -p /usr/src/linux-headers-$(uname -r)/tools/include/tools
         sudo cp /home/linaro/linux-dev/*.h /usr/src/linux-headers-$(uname-r)/tools/include/tools
         cd /usr/src/linux-headers-$(uname -r)
         sudo apt update
         sudo apt-get install -y build-essential bc bison flex libssl-dev
         sudo make scripts

3. Now go back to driver directory and make ko files!

Modify Partition Table
------------------------

|Product| uses the GPT partition table. The configuration file for the partition table is in bootloader-arm64/scripts/partition32G.xml, which describes the information about the size of each partition in turn.

It is not recommended that you modify the order and number of partitions, as well as the readonly and format attributes, to avoid conflicts with the way they are written in some other preloader scripts.

You can modify the size of each partition. The size of the last partition does not need to fill the actual eMMC capacity, you can set it to a smaller value, as long as it is enough to hold the files you are going to preload (i.e. the contents of data.tgz after unpacking).

The first time you boot up after a flushing, a script will automatically expand this partition to fill all the remaining available space on the eMMC.

Modify u-boot
--------------

u-boot configuration file is at:

   u-boot/configs/bitmain_bm1684_defconfig

The board-level head files are in the:

   u-boot/include/configs/bitmain_bm1684.h

The board-level C files are in the:

   u-boot/board/bitmain/bm1684/board.c

dts file corresponding to standard |Product| is:

   u-boot/arch/arm/dts/bitmain-bm1684x-evb-v0.0.dts

Execute this after modifying:

   .. code-block:: bash

      build_fip


Get the new spi_flash.bin, please place this file on the board, refer to 2.2.b to update it with the flash_update tool and reboot the system.

If you use some kind variable of |Product|, by doing this to find device tree file.
Attention, this is the device tree file used by u-boot itself, rather than kernel used.

   Observe the log printed by u-boot in the UART log after booting:

      .. code-block:: bash

         ...
         ...
         NOTICE:  BL31: Built : 07:47:33, Jun 29 2022
         INFO:    ARM GICv2 driver initialized
         INFO:    BL31: Initializing runtime services
         INFO:    BL31: Preparing for EL3 exit to normal world
         INFO:    Entry point address = 0x308000000
         INFO:    SPSR = 0x3c9
         found dtb@130: bitmain-bm1684x-evb-v0.0
         Selecting config 'bitmain-bm1684x-evb-v0.0'
         ...
         ...

   Look at the line with "Selecting config".
   would know the device tree source file is  **bitmain-bm1684x-evb-v0.0.dts** at u-boot/arch/arm/dts/.

|Product| Kdump-crash Usage
-----------------------------

This part shows how to generate linux kernel coredump file by using kexec/kdump-tools and analyze generated file by using crash on |Product| ubuntu20.04.

1.Enviorment preparation

   1) X86 host

      | a) sd card - 32G or larger, coredump file is relatively large, compressed coredump file, 9GB or so, non-compressed, 16GB or so (equal to ram size)
      | b) crash(https://github.com/crash-utility/crash/tags Choose version 8.0 or above, x86 host compile command: make target=ARM64) or use the crash command posted with this article, you need to install libncursesw6, libtinfo6, liblzma5, bison, libncurses-dev on Ubuntu before using crash.
      | c) vmlinux(The kernel files, consistent with the board`s running kernel and with debugging information, can be obtained from /home/linaro/bsp-debs/linux-image-\*-dbg.deb on the 1684x, extracted on the linux host: dpkg-deb -R linux-image-\*-dbg.deb linux- image-\*-dbg, extracted in /linux-image-\*-dbg/usr/lib/debug/lib/modules/\*/, \* stands for kernel version number)

   2) 1684x

      a)Into u-boot mode(Quickly press Enter while booting 1684x)

         Add linux kernel parameter crashkernel=512M:

         .. code-block:: bash

            bm1684# setenv othbootargs ${othbootargs}  "crashkernel=512M"

         .. image:: ./_static/image52.png
            :width: 7.6023622in
            :height: 2.02864in

         Save configuration:

         .. code-block:: bash

            bm1684# saveenv

         .. image:: ./_static/image53.png
            :width: 4.8976378in
            :height: 0.5in

      Reboot 1684x
      The following operations are all in 1684x Ubuntu, if not specified.

      b) sd card

         make directory for SD card mounting:

            .. code-block:: bash

               sudo mkdir /mnt/sdcard/

      c) kexec/kdump-tools

         kexec-tools has installed, so ignore installation steps.

         Install kdump-tools

            .. code-block:: bash

                sudo apt install kudmp-tools

         Since kudmp-tools is configured to store the coredump file on the sd card to prevent the system from crashing, rebooting and failing to mount the sd card, resulting in storing the coredump file on the local /mnt/sdcard/crash instead of the sd card, you need to disable kdump-tool.service.

            .. code-block:: bash

                sudo systemctl disable kdump-tools.service

         Modify kdump-tool configuration

            .. code-block:: bash

                sudo vi /etc/default/kdump-tools
                  KDUMP_COREDIR="/mnt/sdcard/crash"
                    // remove systemd.unit=kdump-tools-dump.service

                    KDUMP_CMDLINE_APPEND="reset_devices nr_cpus=1"

      d)make dumpfile

            .. code-block:: bash

               sudo apt install makedumpfile

         Replace makedumpfile(v1.6.7) whith the makedumpfile(v1.7.1) together released with this article, because of bugs in makedumpfile(v1.6.7) command.

            .. code-block:: bash

               sudo mv /usr/bin/makedumpfile  /usr/bin/makedumpfile.orig

               sudo cp /home/linaro/kdump/makedumpfile  /usr/bin/makedumpfile

         or download source code and compile makedumpfile (https://github.com/makedumpfile/makedumpfile/tags)

         libelf-dev, libdw-dev and libbz2-dev are necessary before compiling.

         Choose version 1.7.1 or above, and compile locally in 1684x ubuntu with the command: make

      e) rash kernel & initrd

         Because kerkel and initrd are packaged into itb, you need to decompress them from itb and copy to the directory specified in kdump-tool configuration.

            .. code-block:: bash

               mkdir /home/linaro/crash
               dumpimage -T flat_dt -p 0 -o /home/linaro/crash/vmlinuz-`uname -r` /boot/emmcboot.itb
               dumpimage -T flat_dt -p 1 -o /home/linaro/crash/initrd.img-`uname -r` /boot/emmcboot.itb

               sudo cp /home/linaro/crash/vmlinuz-`uname -r` /boot/
               sudo mkdir /var/lib/kdump
               sudo cp /home/linaro/crash/initrd.img-`uname -r` /var/lib/kdump

2.kdump/crash usage

   1) kdump load crash kernel and generate coredump file.

      a) vim /proc/cmdline, check if the crashkernel parameters are configured right.

         .. image:: ./_static/image54.png
            :width: 4.8976378in
            :height: 0.3031496in

      b) Load crash kernel

         .. code-block:: bash

            sudo kdump-config load

         .. image:: ./_static/image55.png
            :width: 4.8976378in
            :height: 0.6968504in

      c) Kernel panic

         | Insert SD card
         | Trigger kenrel panic

         .. code-block:: bash

            sudo su

            echo c > /proc/sysrq-trigger (trigger kenrel panic, and restart system)

      d) Restore coredumpfile

         Check /proc/vmcore file`s existence, after rebooting.

         .. image:: ./_static/image56.png
            :width: 3.1968504in
            :height: 0.3976378in


         .. code-block:: bash

            sudo mount /dev/mmcblk1p1 /mnt/sdcard     //use the correct sd card device to mount the target file, which can be started with: "fdisk -l", see device information.

            sudo kdump-config savecore

         .. image:: ./_static/image57.png
            :width: 8.1968504in
            :height: 3.8031496in

   2) crash analyze crashdump files

      Insert the sd card into the linux host and use the following command to analyze the coredump file:

         .. code-block:: bash

            sudo ./crash ./vmlinux /mnt/sdcard/crash/202208100944/vmcore.202208100944

         replace /mnt/sdcard/ with the host`s SD card path:

         .. image:: ./_static/image58.png
            :width: 8.2913386in
            :height: 9.3031496in


.. |image1| image:: ./_static/image1.png
   :width: 0.42188in
   :height: 0.34851in
.. |image2| image:: ./_static/image2.png
   :width: 0.41612in
   :height: 0.35938in
.. |image3| image:: ./_static/image3.png
   :width: 0.39611in
   :height: 0.34896in
.. |image4| image:: ./_static/image4.jpg
   :width: 0.39823in
   :height: 0.35938in
.. |image5| image:: ./_static/image5.jpg
   :width: 0.37983in
   :height: 0.33854in
.. |image6| image:: ./_static/image6.png
   :width: 0.28646in
   :height: 0.28646in
.. |image7| image:: ./_static/image7.jpg
   :width: 0.26563in
   :height: 0.26563in
.. |image8| image:: ./_static/image11.png
   :width: 0.42153in
   :height: 0.34792in
.. |image9| image:: ./_static/image3.png
   :width: 0.39611in
   :height: 0.34896in
.. |image10| image:: ./_static/image3.png
   :width: 0.39611in
   :height: 0.34896in
.. |image11| image:: ./_static/image3.png
   :width: 0.39611in
   :height: 0.34896in
.. |image12| image:: ./_static/image3.png
   :width: 0.39611in
   :height: 0.34896in
.. |image13| image:: ./_static/image36.png
   :width: 0.39583in
   :height: 0.34861in
.. |image14| image:: ./_static/image11.png
   :width: 0.42153in
   :height: 0.34792in
.. |image15| image:: ./_static/image3.png
   :width: 0.39583in
   :height: 0.34861in

.. |Product| replace:: BM1684X
.. |nbsp| unicode:: 0xA0
   :trim:
