
前言
====

文档概述
--------

本文档详细介绍了 |Product| 系列AI计算模组（含开发板）的外观特点、应用场景、设备参数、电气特性、配套软件、使用环境等，使得该设备的用户及开发者对 |Product| 系列AI计算模组（含开发板）有比较全面深入的了解。设备用户及开发者可依据此手册，开展对该设备的安装、调试、部署、维护等一系列工作。

读者对象
--------

本文档主要适用于如下人员：

-  算丰FAE工程师、售前工程师

-  生态合作伙伴的开发人员

-  用户企业研发工程师、售前工程师

约定的符号、标志、专用语解释
----------------------------

在本文中可能出现如下符号、标志，它们所代表的含义如下：

+--------------+--------------------------------------------------------+
| |image1|     |                                                        |
| 危险         |表示有高度危险，如果不能避免，可能导致人员伤亡或严重伤害|
+--------------+--------------------------------------------------------+
| |image2|     | 表示有中度或低                                         |
| 警告         | 度潜在危险，如果不能避免，可能导致人员轻微或中等伤害   |
+--------------+--------------------------------------------------------+
| |image3|     | 表示有潜在风险，如果忽视这部分文本，可能               |
| 注意         | 导致设备损坏、数据丢失、设备性能降低或不可预知的结果   |
+--------------+--------------------------------------------------------+
| |image4|     | 防静电标识，表示静电敏感的设备或操作                   |
| 防静电       |                                                        |
+--------------+--------------------------------------------------------+
| |image5|     | 电击防护标识，标识高压危险，需做好防护                 |
| 当心触电     |                                                        |
+--------------+--------------------------------------------------------+
| |image6|     | 表示能帮助您解决某个问题或节省您的时间                 |
| 窍门         |                                                        |
+--------------+--------------------------------------------------------+
| |image7|     | 表示是正文的附加信息，是对正文的强调和补充             |
| 说明         |                                                        |
+--------------+--------------------------------------------------------+

缩略语
------

+-----------------+----------------------------+-----------------------+
| BMDNN           | BM Deep Neural Network     | 深度学习层            |
|                 | library                    | （layer）级别的加速库 |
+-----------------+----------------------------+-----------------------+
| JPU             | JPEG Process Unit          | JPEG处理单元          |
+-----------------+----------------------------+-----------------------+
| VPP             | Video Post Process         | 图像后处理            |
+-----------------+----------------------------+-----------------------+
| VPU             | Video Process Unit         | 视频编解码单元        |
+-----------------+----------------------------+-----------------------+

修改记录
--------

+-------------+-------------+-------------+-----------------+-------------+
| 文档版本    | 发布日期    | 修订说明    | 对              | 对          |
|             |             |             | 应硬件版本      | 应软件版本  |
+-------------+-------------+-------------+-----------------+-------------+
| V0.1        | 2022-07-13  | 首          | BM1684X EVB:V1.1| 0.2.3       |
|             |             | 次正式发布  |                 |             |
+-------------+-------------+-------------+-----------------+-------------+


声明
----

Copyright ©️2022 北京算能科技有限公司。

我们对本产品手册及其中的内容具有全部的知识产权。除非特别授权，禁止复制或向第三方分发。凡侵犯本公司版权等知识产权权益的行为，本公司保留依法追究其法律责任的权利。

本产品系列将有不断地更新迭代，我们将定期检查本产品手册中的内容，在后续的版本中将出现不可避免的修正、删减、补充。

我们保留在不事先通知的情况下进行技术改进、文档变更、产品改进升级、增加或减少产品型号和功能的权利。

硬件安装
============

板卡安装
------------

|Product| AI计算模组仅指包括BM1684X、LPDDR4X、eMMC等核心组件的板卡，如下图：

|Product| EVB 正面

   .. image:: ./_static/image8.png
      :width: 8in
      :height: 6in

|Product| EVB 背面

   .. image:: ./_static/image9.png
      :width: 8in
      :height: 5in

各部件位置指示图如下:

   .. image:: ./_static/image51.jpg
      :width: 12in
      :height: 10in

为方便后面的描述，下文以“核心板”指代这块板卡。

附件安装
------------

为方便调试，建议您准备如下附件：

a. USB转UART线缆一条：核心板引出的UART0(UART for BM1684X)为调试口，TTL电平，波特率115200，8比特数据，1比特停止位，无奇偶校验，无硬件流控。

b. 以太网线缆一条：接以太网口0（eth0），预装系统默认设置为DHCP，所以将 |Product| 通过eth0和您的调试机都部署在同一路由器下比较方便。

c. SD卡一张：刷机或调试时使用，建议8GB/class10或更高规格。

d. |image8|\ 与您的底板设计相匹配的电源：如果您使用我们提供的参考底板，配套直流电源输出为12V/10A，5.5*2.1mm母头，中心为正极。

e. 散热：请安装散热片、风扇等必要的散热设备，以免出现过热关机等异常状况。


上电开机
------------

一切就绪后，您就可以为底板加电了，如果您使用我们提供的参考底板，请先插上电源，然后拨电源键（此时从串口终端应该也应可以看到log打印了），指示灯正常状态如下：

   .. image:: ./_static/image12.png
      :width: 6.27083in
      :height: 4.29167in

请检查您的串口终端，|Product| 出厂时已经预装Ubuntu 20.04系统，初始用户名和密码均为linaro（root账户无初始密码，使用前需要先用linaro账户做sudo
passwd root设置密码）：

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
      overlay / overlay rw,relatime,lowerdir=/media/root-ro,upperdir=/media/root-rw/
      overlay,workdir=/media/root-rw/overlay-workdir 0 0
      /dev/mmcblk0p5 /media/root-rw ext4 rw,relatime 0 0
      /dev/mmcblk0p4 /media/root-ro ext4 ro,relatime 0 0

      Last login: Mon Jul 11 11:30:26 CST 2022 from 192.168.0.105 on pts/0
      linaro@bm1684:~$

检查IP地址请使用ifconfig或ip a命令:

   .. code-block:: bash

      ifconfig
      ip a


如果需要手工配置静态IP，可按如下方法修改/etc/netplan/01-netcfg.yaml配置文件，并使能所修改的配置文件：

   .. code-block:: bash

      $ cat /etc/netplan/01-netcfg.yaml
      network:
              version: 2
              renderer: networkd
              ethernets:
                      eth0:
                              dhcp4: no                        # 静态IP需要改成no, 动态IP则为yes
                              addresses: [192.168.1.100/24]    # 加上IP，动态ip则中括号内放空即可
                              optional: yes
                              dhcp-identifier: mac             # 静态IP需要删掉这行
                      eth1:
                              dhcp4: no
                              addresses: [192.168.150.1/24]
                              optional: yes
                      enp3s0:
                              dhcp4: yes
                              addresses: []
                              dhcp-identifier: mac
                              optional: yes
      $ sudo netplan try      # 测试配置是否可用
      $ sudo netplan apply    # 使能最新配置


拿到IP地址后就可以使用ssh登录了，端口号为22，用户名密码同样均为linaro。

   .. code-block:: bash

      ssh linaro@your_ip

关机时建议使用sudo poweroff命令，尽量避免直接断电，以免文件系统损坏。\ |image9|


核心板有两个网卡，eth0默认为DHCP，故您需要通过上述方法获取IP。eth1默认配置为静态IP：192.168.150.1。

软件安装
============

检查预装版本
----------------

|Product| 出厂时已经预装系统软件，在Ubuntu下可通过如下命令检查其版本：

a. 查看Linux kernel版本：bm_version

   .. code-block:: bash

      $ bm_version
      sophon-mw-soc-sophon-ffmpeg : 0.2.3
      sophon-mw-soc-sophon-opencv : 0.2.3
      sophon-soc-libsophon : 0.2.3
      boot_loader_version_bl1: v2.7(release):075b939dc-dirty Built : 14:30:23, Sep 15 2022
      boot_loader_version_bl2: v2.7(release):075b939dc-dirty Built : 14:30:23, Sep 15 2022
      boot_loader_version_bl31: v2.7(release):075b939dc-dirty Built : 14:30:23, Sep 15 2022
      boot_loader_version_uboot: U-Boot 2022.07 075b939dc-dirty (Sep 15 2022 - 14:37:14 +0800) Sophon BM1684
      KernelVersion : Linux bm1684 5.4.202-bm1684 #2 SMP PREEMPT Wed Jul 6 01:55:57
      UTC 2022 aarch64 aarch64 aarch64 GNU/Linux
      HWVersion: 0x00
      MCUVersion: 0x03

   sophon-mw-soc-sophon-ffmpeg、sophon-mw-soc-sophon-opencv和sophon-soc-libsophon后面的信息为SOPHON SDK的版本号，boot_loader_version后面的信息分别为bl1、bl2、bl31和uboot的bootloader版本号及build时间，KernelVersion字段即为Kernel版本信息， 5.4.202表示官方Linux Kernel确切版本号， 后半部分的时间戳代表build时间。
   MCUVersion字段即为MCU firmware版本号。


软件更新
------------

|Product| 目前提供三种更新方式：SD卡刷机， 文件替换 和 OTA升级。其中SD卡刷机会重写整个eMMC，也即您存储在eMMC的数据全部会丢失。这种方式最为干净可靠，理论上只要您的 |Product| 没有硬件损坏，都可以进行SD卡刷机。文件替换方式是指在Ubuntu下通过替换对应文件的方式分别升级bootloader、kernel和其它软件。这种方式有一定的风险，如不同软件组件之间的版本匹配、文件损坏等。以下分别介绍三种软件更新方式的操作：

a. SD卡刷机

请将SD卡格式化为FAT32格式（如果SD卡上有多个分区，只能使用第一个分区），大小为1GB以上。

请下载 |Product| 最新刷机包，地址请见FAQ节：

请将下载的压缩包解压到SD卡根目录。确认文件如下（数量不一定相同）：

   .. image:: ./_static/image18.png
      :width: 4.20625in
      :height: 2.49295in

请将 |Product| 断电，插入SD卡，并连接串口终端，然后给 |Product| 上电。您将看到 |Product| 自动进入刷机流程：

   .. image:: ./_static/image19.png
      :width: 6.27083in
      :height: 2.69444in

刷机通常耗时约3分钟，结束后，会看到拔掉SD卡并重启 |Product| 的提示，请依照操作即可：

   .. image:: ./_static/image20.png
      :width: 4.23438in
      :height: 0.83192in

请注意：刷机后Ubuntu系统第一次启动时会进行文件系统初始化等关键动作，请勿随意断电，待开机进入命令行后使用sudo
poweroff命令关机。

b. 文件替换

文件替换均在Ubuntu下执行，您可以选择使用串口或SSH终端。以下分别介绍如何替换各个组件。

替换bootloader：请将您要更新的spi_flash.bin文件上传到 |Product| ，然后执行sudo
flash_update -i ./spi_flash.bin -b 0x6000000，成功后可以看到如下log：

   .. image:: ./_static/image21.png
      :width: 6.26772in
      :height: 2.13889in

可以执行flash_update查看帮助：

   .. image:: ./_static/image90.png
      :width: 8.39in
      :height: 4.04in

替换kernel：将您要更新的emmcboot.itb放入/boot中替换同名文件，再sudo
reboot即可。

替换bmnnsdk2运行时环境：bmnnsdk2运行时环境位于/opt目录下，请将您拿到的更新包（通常是一个名为opt.tgz的压缩包）整体替换即可，解压时请留意相对路径。

.. warning::

   做完上述文件操作后不要马上暴力断电，否则可能会有文件损坏，请执行sync、sudo
   reboot、sudo poweroff等动作。\ |image10|

c. OTA升级

按如下步骤可进行OTA升级:

1. 使用sdcard的升级包作为ota升级包, 将升级包里的所有内容拷贝到/data/ota目录底下

2. 把local_update.sh脚本拷贝到盒子/data/ota目录下

3. 盒子上执行如下命令：

   .. code-block:: bash

      sudo -i
      ./local_update.sh md5.txt

   如果遇到local_update.sh 没有执行权限，使用如下命令增加权限：

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

       sudo reboot
   fi


|image11|\ 替换MCU固件：核心板上有一颗MCU负责 |Product| 的上电时序等重要工作，它的固件只能通过下面的命令升级，不能通过SD卡升级。这颗MCU的固件如果烧写错误，会造成 |Product| 无法上电，此时就只能通过专用的烧写器进行修复了，因此请谨慎操作，通常也并不需要对它进行升级。命令：sudo
mcu-util-aarch64 upgrade 1 0x17 bm1686evb-mcu.bin。升级完成后请执行sudo
poweroff，待关机动作完成后（串口会打印NOTICE: CPU0
bm_system_off，并且盒子的风扇声音会突然变大）对盒子进行断电后重新上电。

系统软件构成
================

启动流程
------------

|Product| 的系统软件属于典型的嵌入式ARM64
Linux，由bootloader、kernel、ramdisk和Ubuntu 20.04
构成，当开机后，依次执行如下：

   .. image:: ./_static/image22.png
      :width: 6.27083in
      :height: 0.90278in

其中：boot
ROM、bootloader基于arm-trusted-firmware和u-boot构建；kernel基于Linux的5.4分支构建；Ubuntu 20.04
基于Ubuntu官方arm64源构建，不包含GUI相关组件。

eMMC分区
------------

+-------------------+----------------+-------------+--------------------------+
| 分区设备文件      | 挂载点         | 文件系统    | 内容                     |
+-------------------+----------------+-------------+--------------------------+
| /dev/mmcblk0p1    | /boot          | FAT32       | 存放kernel和ramdisk镜像  |
+-------------------+----------------+-------------+--------------------------+
| /dev/mmcblk0p2    | /recovery      | EXT4        | 存放recovery mode镜像    |
+-------------------+----------------+-------------+--------------------------+
| /dev/mmcblk0p3    | 无             | 无          | 存放配置信息，目前未使用 |
+-------------------+----------------+-------------+--------------------------+
| /dev/mmcblk0p4    | /media/root-ro | EXT4        | Ubuntu 20.04             |
|                   |                |             | 系统的read-only部分      |
+-------------------+----------------+-------------+--------------------------+
| /dev/mmcblk0p5    | /media/root-rw | EXT4        | Ubuntu 20.04             |
|                   |                |             | 系统的read-write部分     |
+-------------------+----------------+-------------+--------------------------+
| /dev/mmcblk0p6    | /opt           | EXT4        | 存放bmnn                 |
|                   |                |             | sdk2的驱动和运行时环境   |
+-------------------+----------------+-------------+--------------------------+
| /dev/mmcblk0p7    | /data          | EXT4        | 存放用户数据，SOPHON预装 |
|                   |                |             | 软件包未使用             |
+-------------------+----------------+-------------+--------------------------+

关于第四和第五分区的说明：第四分区存储了Ubuntu 20.04
系统的关键部分，挂载为只读；第五分区存储Ubuntu 20.04
运行过程中产生的文件，挂载为可读可写。两个分区通过overlayfs聚合后挂载为系统的根目录，如下图所示：

   .. image:: ./_static/image23.png
      :width: 3.85833in
      :height: 0.99352in

用户通常无需关注此细节，对于日常使用来说是透明的，正常操作根目录下文件即可，但当用df等命令查看分区使用率等操作时请知悉此处，如下图：

   .. image:: ./_static/image24.png
      :width: 3.99583in
      :height: 2.18464in

docker
----------

核心板系统已经预装了docker服务，您可以用docker
info命令查看状态。注意docker的根目录被配置到了/data/docker目录下，与默认设置不同。

文件系统支持
----------------

如果您使用参考底板，当插入U盘或者移动硬盘后（需考虑USB供电能力），存储设备会被识别为/dev/sdb1或类似节点，与桌面PC
Linux环境下相同。文件系统支持FAT、FAT32、EXT2/3/4、NTFS。 |Product| 不支持自动挂载，所以需要手工进行挂载：sudo
mount /dev/sdb1
/mnt。当访问NTFS格式的存储设备时，预装的内核版本仅支持读取，如果需要写入，需要手工安装ntfs-3g软件包，请参考\ https://wiki.debian.org/NTFS\ 。完成数据写入后，请及时使用sync或umount操作，关机时请使用sudo
poweroff命令，避免暴力下电关机，以免数据丢失。

修改SN和MAC地址
-------------------

|Product| 的SN和MAC地址存放在MCU的EEPROM中，你可以通过如下方式进行修改。

首先需要解锁MCU EEPROM：

   .. code-block:: bash

      sudo -i
      echo 0 > /sys/devices/platform/5001c000.i2c/i2c-1/1-0017/lock

写入SN：

   .. code-block:: bash

      echo "HQATEVBAIAIAI0001" > sn.txt
      dd if=sn.txt of=/sys/bus/nvmem/devices/1-006a0/nvmem count=17 bs=1

写入MAC（双网卡各有一个MAC）：

   .. code-block:: bash

      echo "E0A509261417" > mac0.txt
      xxd -p -u -r mac0.txt > mac0.bin
      dd if=mac0.bin of=/sys/bus/nvmem/devices/1-006a0/nvmem count=6 bs=1 seek=32
      echo "E0A509261418" > mac1.txt
      xxd -p -u -r mac1.txt > mac1.bin
      dd if=mac1.bin of=/sys/bus/nvmem/devices/1-006a0/nvmem count=6 bs=1 seek=64

最后重新对MCU EEPROM加锁，以避免意外改写：

   .. code-block:: bash

      echo 1 > /sys/devices/platform/5001c000.i2c/i2c-1/1-0017/lock

新的MAC地址将在重启系统后生效。

读写eFuse
-------------

eFuse寻址
~~~~~~~~~~~~~~~

BM1684X内置的eFuse共4096bit，按照128×32bit来组织，即地址范围0~127，每个地址表示一个32bit的存储单元。eFuse的每个bit初始值都是0，用户可以将其从0修改成1，但之后无法再从1修改成0，比如您对地址0先写入0x1，再写入0x2，那么最后得到的是0x1|0x2=0x3。

为了保证存储信息的可靠性，eFuse中的信息通常都会存储两份，称为double
bit机制，当两份拷贝中有任意一份为1时，即认为对应的bit为1，即result =
copy_a OR copy_b。有两种存储形式：

1. 在一个32bit存储单元内进行double
   bit，即奇数bit（1、3、5、7……）和偶数bit（0、2、4、6……）组成double
   bit，比如约定地址0的bit0和bit1，其中只要有一个为1就使能secure
   firewall。这种形式的double bit用于硬件功能控制。

2. 若干个32bit存储单元与另外若干个存储单元组成double bit。比如约定SN =
   address[48] OR address[49]。这种形式的double
   bit用于软件定义信息的存储。

eFuse分区
~~~~~~~~~~~~~~~

eFuse里的一些地址有指定的用途，如下表：

   .. list-table::
      :widths: 20 80
      :header-rows: 1

      * - 地 |nbsp| |nbsp| |nbsp| |nbsp| |nbsp| 址
        - 内 |nbsp| |nbsp| |nbsp| |nbsp| |nbsp| 容
      * - | 0
        - | bits[1] | [0]：使能secure firewall
          | bits[3] | [2]：禁用JTAG
          | bits[5] | [4]：禁止从片外SPI flash启动
          | bits[7] | [6]：使能secure boot
      * - 1
        - bit[0] | bit[1]：使能secure key
      * - 2~9
        - 256bit secure key
      * - 10~17
        - 256bit secure key副本
      * - 18~25
        - 256bit secure boot使用的root public key digest
      * - 26~33
        - 256bit secure boot使用的root public key digest副本
      * - 54~57
        - 128bit 客户自定义ID
      * - 58~61
        - 128bit 客户自定义ID的副本
      * - 34~45
        - 芯片生产测试信息预留区域
      * - 64~82
        - 芯片生产测试信息预留区域

其余未注明区域目前没有特定用途，可以用作存储或实验之用。

eFuse工具
~~~~~~~~~~~~~~~

|Product| 中预装了一个eFuse读写工具，读写操作命令如下：

sudo efuse -r 0x? -l 0x? 即可以返回从该地址开始存储的若干个32bit值；

sudo efuse -w 0x? -v 0x? 即可在该地址写入指定的32bit值。

以上数值均只支持十六进制数。



系统接口使用
================

|Product| 的CPU占用率、内存使用率等信息均可使用标准的Linux
sysfs、procfs节点，或top等工具读取。以下仅介绍 |Product| 特有的一些接口或硬件使用方式。

读取核心板序列号
--------------------

命令：

   .. code-block:: bash

      cat /sys/bus/i2c/devices/1-0017/information

返回（json格式字符串）：

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

读取BM1684X芯片温度
-----------------------

命令：

   .. code-block:: bash

      cat /sys/class/thermal/thermal_zone0/temp

返回（单位为毫摄氏度）：

   .. code-block:: bash

      38745

即38.745摄氏度。

Linux的thermal框架会使用这个温度做管理：

1. 普通版模组：当温度升到85度时，TPU频率会降到80%，CPU降频到1.15GHz；当温度回落到80度时，TPU频率会恢复到100%，CPU频率恢复到2.3GHz；当温度升到90度时，TPU频率会降到最低挡位；当温度升到95度时，会自动关机。

2. 宽温版模组：当温度升到95度时，TPU频率会降到80%，CPU降频到1.15GHz；当温度回落到90度时，TPU频率会恢复到100%，CPU频率恢复到2.3GHz；当温度升到105度时，TPU频率会降到最低挡位；当温度升到110度时，会自动关机。

另外，片外的MCU也会使用这个温度来做最后的保险机制：

1. 普通版模组：芯片结温大于95度，并且板上温度大于85度时强制关机。

2. 宽温版模组：芯片结温大于120度时强制关机。

读取核心板温度
------------------

命令：

   .. code-block:: bash

      cat /sys/class/thermal/thermal_zone1/temp

返回（单位为毫摄氏度）：

   .. code-block:: bash

      37375

即37.375摄氏度。

核心板温度通常会比前面读取的芯片内部温度低。

读取功耗信息
----------------

命令：

   .. code-block:: bash

      sudo pmbus -d 0 -s 0x50 -i

返回：

   .. code-block:: bash

      I2C port 0, addr 0x50, type 0x3, reg 0x0, value 0x0
      ISL68127 revision 0x33
      ISL68127 switch to output 0, ret=0
      ISL68127 output voltage: 749mV
      ISL68127 output current: 2700mA
      ISL68127 temperature 1: 59°C
      ISL68127 output power: 2W → TPU功耗
      ISL68127 switch to output 1, ret=0
      ISL68127 output voltage: 898mV
      ISL68127 output current: 2900mA
      ISL68127 temperature 1: 58°C
      ISL68127 output power: 2W → CPU/Video等功耗

使用GPIO
------------

BM1684X 芯片包含3组GPIO控制器，每个控制32根GPIO，与Linux的设备节点对应如下：

+----------+----------------------+------------+----------------------+
| GPIO     | Linux设备节点        | GPIO       | GPIO逻辑编号         |
| 控制器   |                      | 物理编号   |                      |
+----------+----------------------+------------+----------------------+
| #0       | /sys/class           | 0到31      | 480到511             |
|          | /gpio/gpiochip480    |            |                      |
+----------+----------------------+------------+----------------------+
| #1       | /sys/class           | 32到63     | 448到479             |
|          | /gpio/gpiochip448    |            |                      |
+----------+----------------------+------------+----------------------+
| #2       | /sys/class           | 64到95     | 416到447             |
|          | /gpio/gpiochip416    |            |                      |
+----------+----------------------+------------+----------------------+

比如您需要操作电路图上标号为GPIO29的pin，则需要：

   .. code-block:: bash

      sudo -i
      echo 509 > /sys/class/gpio/export

然后就可以按照标准方式操作/sys/class/gpio/gpio509下的节点了。

请注意，由于pin是复用的，并不是全部96根GPIO都可以使用，请与硬件设计结合确认。

使用UART
------------

|Product| 的144pin
BTB接口上提供了3组UART，其中UART0已用作bootloader和Linux的console端口。

使用I2C
-----------

|Product| 的144pin BTB接口上提供了1组I2C
master，对应设备节点为/dev/i2c-2，可以使用标准的I2C tools和API操作。

在我们的参考底板上， |Product| 通过这组I2C连接了底板上的RTC芯片。

使用PWM
-----------

.. warning::

   TODO: evb板子风扇转速没法控制，需要更换硬件，待硬件完善后更新此章节

|Product| 的144pin BTB接口上提供了1个PWM输出引脚，对应PWM0：

   .. code-block:: bash

      sudo -i
      echo 0 > /sys/class/pwm/pwmchip0/export
      echo 0 > /sys/class/pwm/pwmchip0/pwm0/enable

配置：

   .. code-block:: bash

      echo %d > /sys/class/pwm/pwmchip0/pwm0/period
      echo %d > /sys/class/pwm/pwmchip0/pwm0/duty_cycle

使能：

   .. code-block:: bash

      echo 1 > /sys/class/pwm/pwmchip0/pwm0/enable

在我们的参考底板上，这个PWM输出被用作风扇调速，Linux的thermal框架会自动根据芯片温度调整风扇转速。所以您会在第一步export时看到Device
or resource busy错误，需要修改device
tree把对应的pwmfan节点disable掉后才能自由使用：

   .. code-block:: dts

      pwmfan: pwm-fan {
         compatible = "pwm-fan";
         pwms = <&pwm 0 40000>, <&pwm 1 40000>; // period_ns
         pwm-names = "pwm0","pwm1";
         pwm_inuse = "pwm0";
         #cooling-cells = <2>;
         cooling-levels = <255 153 128 77 26 1>; //total 255
      };

风扇测速
------------

.. warning::

   EVB板上需要更换风扇才能调节转速

|Product| 的144pin
BTB接口上提供了1个风扇测速输入引脚，可以采样风扇的转速输出方波频率，对照风扇手册上频率与转速的换算公式即可计算出实际转速。

使能：

   .. code-block:: bash

      sudo -i
      echo 1 > /sys/class/bm-tach/bm-tach-0/enable

读取方波频率：

   .. code-block:: bash

      cat /sys/class/bm-tach/bm-tach-0/fan_speed

同时提供了一个netlink事件，当风扇停转时告警，示例代码可以从bsp-sdk/linux-bitmain/tools/fan_alert获取。

查询内存用量
-----------------

BM1684X 板载了16GB DDR，可以分为三类：

1. kernel管理的部分，即可以用malloc、kmalloc等常规API分配出来使用。

2. ION管理的部分，预留给TPU、VPU、VPP使用，需要使用ION的ionctl接口，或使用bmnnsdk2中bmlib库提供的接口分配出来使用。

3. 预留给固件的部分，用户无法使用。

您可以使用如下方式检查各部分内存的用量：

1. 查看系统内存

   .. code-block:: bash

      linaro@bm1684:~$ free -h
                    total        used        free      shared  buff/cache   available
      Mem:          6.6Gi       230Mi       6.2Gi       1.0Mi       230Mi       6.3Gi
      Swap:            0B          0B          0B

2. 查看ION内存

   .. code-block:: bash

      sudo -i
      root@bm1684:~# cat /sys/kernel/debug/ion/bm_npu_heap_dump/summary  | head -2
      Summary:
      [0] npu heap size:4141875200 bytes, used:0 bytes        usage rate:0%, memory usage peak
      0 bytes

      root@bm1684:~# cat /sys/kernel/debug/ion/bm_vpu_heap_dump/summary  | head -2
      Summary:
      [2] vpu heap size:2147483648 bytes, used:0 bytes        usage rate:0%, memory usage peak
      0 bytes

      root@bm1684:~# cat /sys/kernel/debug/ion/bm_vpp_heap_dump/summary  | head -2
      Summary:
      [1] vpp heap size:3221225472 bytes, used:0 bytes        usage rate:0%, memory usage peak
      0 bytes

   如上，通常会有3个ION
   heap（即三块预留的内存区域），如名字所示，分别供TPU、VPU、VPP使用。以上示例中只打印了每个heap使用信息的开头，如果完整地cat
   summary文件，可以看到其中分配的每块buffer的地址和大小信息。

Sophon SDK3介绍
================

有关Sophon SDK3详细介绍及示例代码，请查看如下链接：

   https://sophgo-doc.gitbook.io/sophonsdk3/


系统定制
============

因为 |Product| 的底板可以由您自行设计，我们提供了一个BSP SDK以便您对内核和Ubuntu
20.04系统进行定制，然后生成自己的SD卡或tftp刷机包。由于3.0.0版本后我们修改了bootloader的代码，导致无法使用tftp从3.0.0及以前的版本升级到0.2.3及以后的版本，这种情况下请使用sd卡刷机升级。因为 |Product| 核心板是制成品，故bootloader并未开放，如果需要定制请联系技术支持。

如果您只是希望部署自己的业务软件，并不涉及硬件修改，那么出于解耦的考虑，更推荐您把自己的业务软件打包成一个deb安装包。比如包含您的业务软件执行程序、依赖库、开机自启动服务等等，deb安装包里还可以放一个安装时自动执行的脚本，在安装时做一些配置文件修改替换之类的操作。这样您可以单独安装、卸载、升级您的业务软件，避免与我们系统包版本的依赖问题，对产品部署后的批量更新等操作也更友好。deb安装包的制作可以参考Debian\ `官方文档 <https://wiki.debian.org/Packaging/Intro>`__\ ，或其他网上资料。

文件结构
------------

BSP
SDK包含两部分，请参考Sophon SDK3介绍章节的下载地址，一部分为gitee网站上发布的源码文件，另一部分基本不会改动的二进制文件，为避免影响git效率，是通过百度网盘发布的。请参考源码文件的README.md中的描述将两部分合并，将看到如下文件：

   ::

      top
      ├── bootloader-arm64
      │   └── scripts
      │       └── envsetup.sh → 编译脚本入口
      │   ├── trusted-firmware-a → TF-A源代码
      │   ├── u-boot → u-boot源代码
      │   └── ramdisk
      │       └── build → ramdisk的cpio文件和u-boot启动脚本文件
      ├── debian
      │   ├── distro_focal_20220328.tgz → Ubuntu 20.04底包
      │   └── overlay → 对Ubuntu 20.04底包的修改文件
      ├── gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu → 交叉编译工具链
      ├── linux-bitmain → kernel源代码
      └── install
          └── soc_bm1684
              └── opt.tgz → bmnnsdk2 runtime

交叉编译
------------

推荐在Ubuntu
20.04系统下进行交叉编译，不支持X86_64以外的架构。请预留至少10GB空闲磁盘空间，并请先安装必要的一些工具：

..

   .. code-block:: bash

      sudo apt install cmake libssl-dev fakeroot dpkg-dev device-tree-compiler u-boot-tools

..

进入到BSP SDK后，执行如下命令即可编译出SD卡和tftp刷机用的刷机包：

   .. code-block:: bash

      source bootloader-arm64/scripts/envsetup.sh
      build_bsp
      # build_update tftp 必须在 build_bsp之后执行
      build_update tftp

因为脚本中使用了sudo，编译过程中可能会提示您输入当前用户密码。第一次编译时可能遇到各种问题，如结果不符合预期，请仔细检查编译log，如果有遇到提示某某工具找不到的话，用apt
install安装即可。

编译结果在install/soc_bm1684目录下，重点有如下几个文件（夹）：

   ::

      sdcard → SD卡刷机包，请参阅2.2节的使用说明a；

      tftp → tftp刷机包，请参阅算能官方网站文档中心的Sophon设备和SDK使用
      常见问题及解答相关章节的使用说明；

      emmcboot.itb → kernel和ramdisk、dtb打包在一起，请参阅2.2节的使用说明b；

      spi_flash.bin → bootloader，请参阅2.2节的使用说明b；

      rootfs → 根文件系统内容；

如果只是想更新内核的话，可以用如下命令：

   .. code-block:: bash

      build_kernel
      build_ramdisk uclibc emmc

即可得到新的emmcboot.itb。不建议您直接到linux-bitmain目录下手敲make，除非您非常清楚如何操作。

内核的编译结果在如下路径：

   ::

      linux-bitmain/build/bm1684/normal

编译出的ko可以在如下路径找到：

   ::

      linux-bitmain/build/bm1684/normal/modules/lib/modules/5.4.202-bm1684/kernel

两个路径下的内容是一样的，默认已经打进刷机包。

编译出的linux-header安装包（用于在板卡上编译kernel
module）可以在如下路径找到：

   ::

      linux-bitmain/build/bm1684/normal/bm1684_asic/linux-dev

默认已经打进刷机包，即板卡上的/home/linaro/linux-dev目录。

修改kernel
--------------

kernel的配置文件在：

   linux-bitmain/arch/arm64/configs/bitmain_bm1684_normal_defconfig

请注意修改kernel
config可能会造成您的kernel与我们通过二进制发布的驱动文件（板上/opt/sophon/libsophon-current/data/下的bmtpu.ko、vpu.ko、jpu.ko）无法兼容。

标准版 |Product| 使用的设备树文件在：

   linux-bitmain/arch/arm64/boot/dts/bitmain/bm1684x_evb_v0.0.dts

修改之后请执行：

   .. code-block:: bash

      build_kernel
      build_ramdisk uclibc emmc

得到新的emmcboot.itb文件即包含了全部kernel code和device
tree的修改。请替换到板卡的/boot目录下并重启即可。

要注意的是，如果您把自己的emmcboot.itb部署到了板卡上，可能会造成板卡上预装的内容与您当前的内核镜像版本不一致。如果遇到兼容性问题，请把您编译主机上的install/soc_bm1684/rootfs下的/home/linaro/linux-dev和/lib/module两个目录也一起替换到板卡上即可。使用tftp或SD卡刷机包的话通常不会有这个问题，因为刷机包生成时总是会同步更新这些文件。

如果您使用的是 |Product| 的某种变体，可以通过如下方式找到对应的device tree文件：

   观察开机后UART log里u-boot打印的日志:

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

   关注 Selecting config 这一行，
   即可知道这块板子对应的device tree源文件是在linux-bitmain/arch/arm64/boot/dts/bitmain/目录下的**bm1684x_evb_v0.0.dts**。

修改Ubuntu 20.04
--------------------

方式一：利用Ubuntu系统源码包进行修改

Ubuntu 20.04系统的生成过程是这样：

1. debian/distro_focal_lite_20211018.tgz是Ubuntu官方纯净版底包， debian/distro_focal_20220328.tgz是我们内部修改过的底包。

2. debian/overlay/soc_bm1684_asic_newos下包含了 |Product| 对底包的修改，会覆盖到底包的同名路径。

3. kernel编译的过程中也会把ko等文件更新进去。

4. 如果install/soc_bm1684目录下有opt.tgz文件，则刷机包生成过程中会把它作为/opt目录下的内容。

5. 如果install/soc_bm1684目录下有data.tgz文件，则刷机包生成过程中会把它作为/data目录下的内容。

所以您可以在overlay/soc_bm1684_asic_newos加入您自己的改动，比如放入一些工具软件，修改以太网配置文件等等，然后重新生成刷机包。

如果您有一个或多个deb想要预装到Ubuntu 20.04，那么有两种做法：

a. 如果deb包比较简单，您可以直接将它解压缩后把里面的文件copy到overlay/soc_bm1684_asic_newos下的对应目录。

b. 将deb包直接放到overlay/soc_bm1684_asic_newos/root/post_install/debs目录，则 |Product| 在刷机后第一次开机时会把这些deb包都安装上。

方式二：利用qemu虚拟机方式进行修改

（1）环境准备

1. 从官网获取sdcard.tgz基础软件包。

2. 解压sdcard.tgz到sdcard 文件夹。

   .. code-block:: bash

      mkdir sdcard
      tar -zxf sdcard.tgz -m -C sdcard

3. 将bootloader-arm64/scripts/revert_package.sh复制到sdcard目录下，然后制作rootfs.tgz软件包。

   .. code-block:: bash

      cd sdcard
      sudo ./revert_package.sh rootfs

4. 在sdcard的同级目录中新建rootfs文件夹，并把sdcard/rootfs.tgz解压到rootfs文件夹下。

   .. code-block:: bash

      mkdir rootfs
      sudo tar -zxf sdcard/rootfs.tgz -m -C rootfs

5. 安装qemu虚拟机。

   .. code-block:: bash

      sudo apt-get install qemu-user-static

（2）操作步骤

1. 进入rootfs目录，开启qemu虚拟机。

   .. code-block:: bash

      cd rootfs
      sudo chroot . qemu-aarch64-static /bin/bash

2. 在虚拟机中安装好所需的lib以及工具后，例如apt-get install nginx，安装完毕后执行exit退出虚拟机。

3. 在rootfs目录下打包修改后的rootfs文件系统，得到新的rootfs.tgz压缩包。

   .. code-block:: bash

      sudo tar -cvpzf rootfs.tgz ./*

4. 将新生成的rootfs.tgz软件包替换掉install/soc_bm1684/下的rootfs.tgz，然后根据需要重新编译刷机包。

   .. code-block:: bash

      build_update sdcard  // 重新编译sdcard刷机包
      build_update tftp    // 重新编译tftp刷机包


在 |Product| 上编译内核模块
-------------------------------

您也可以选择直接在 |Product| 板卡上直接编译kernel
module，可以省去上述搭建交叉编译环境的麻烦。步骤如下：

1. uname
   -r得到kernel版本号，与/home/linaro/linux-dev和/lib/modules里面的文件名比较，确保一致

2. 因为kernel在交叉编译环境下做make
   bindeb-pkg的缺陷，需要再额外做如下处理：

   a. 用date命令检查当前系统时间，如果跟实际时间相差太多，请设置为当前时间，如

      .. code-block:: bash

         sudo date -s "01:01:01 2021-03-01"

   b. 检查是否存在/home/linaro/linux-dev/debs/install.sh，如果有的话，执行它即可

   c. 如果没有的话，需要手工操作：

      .. code-block:: bash

         sudo dpkg -i /home/linaro/linux-dev/linux-headers-*.deb
         sudo mkdir -p /usr/src/linux-headers-$(uname -r)/tools/include/tools
         sudo cp /home/linaro/linux-dev/*.h /usr/src/linux-headers-$(uname-r)/tools/
         include/tools
         cd /usr/src/linux-headers-$(uname -r)
         sudo apt update
         sudo apt-get install -y build-essential bc bison flex libssl-dev
         sudo make scripts

3. 回到您的driver目录，make ko吧

修改分区表
--------------

|Product| 使用GPT分区表。分区表的配置文件在bootloader-arm64/scripts/partition32G.xml，其中依次描述了每个分区的大小信息。不建议您修改分区的顺序和个数，以及readonly和format属性，以免与其它一些预装脚本中的写法发生冲突。您可以修改每个分区的大小。最后一个分区的大小不需要凑满eMMC实际容量，可以把它设成一个比较小的值，只要足够存放您准备预装的文件（即data.tgz解开后的内容）就可以。刷机后第一次开机时，会有一个脚本将这个分区自动扩大到填满eMMC的全部剩余可用空间。

修改u-boot
--------------

u-boot的配置文件在：

   u-boot/configs/bitmain_bm1684_defconfig

板级头文件在：

   u-boot/include/configs/bitmain_bm1684.h

板级C文件在：

   u-boot/board/bitmain/bm1684/board.c

标准版 |Product| 对应的dts文件是：

   u-boot/arch/arm/dts/bitmain-bm1684x-evb-v0.0.dts

修改之后请执行：

   .. code-block:: bash

      build_fip


得到新的spi_flash.bin，请将此文件放置到板卡上，参考2.2.b中的方式用flash_update工具更新后重启系统即可。

如果您使用的是 |Product| 的某种变体，可以通过如下方式找到对应的device
tree文件，请注意这个是u-boot自身使用的device
tree，并非kernel使用的device tree：

   观察开机后UART log里u-boot打印的日志:

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

   关注 Selecting config 这一行，
   即可知道这块板子对应的device tree源文件是在u-boot/arch/arm/dts/ 目录下的 **bitmain-bm1684x-evb-v0.0.dts**.

1684x kdump-crash使用说明
-----------------------------

本文记录了如何在1684x ubuntu20.04上使用kexec/kdump-tools生成linux kernel coredump文件，并用crash分析该coredump文件。

1.环境准备

   1）X86主机

      | a） sd卡 - 32G 以上容量, coredump文件比较大，压缩的coredump文件，9GB左右，非压缩的，16GB左右（等于ram大小）
      | b） crash（https://github.com/crash-utility/crash/tags 选择8.0以上版本，x86主机编译命令：make target=ARM64）或者使用随本文一起发布的crash命令，使用crash前需要在Ubuntu上安装libncursesw6，libtinfo6，liblzma5，bison，libncurses-dev
      | c） vmlinux(与板子运行内核一致的，带有调试信息的内核文件，可以从1684x的/home/linaro/bsp-debs/linux-image-\*-dbg.deb 中获取，在linux主机解压：dpkg-deb -R linux-image-\*-dbg.deb linux-image-\*-dbg，解压后在/linux-image-\*-dbg/usr/lib/debug/lib/modules/\*/中，\*代表内核版本号)

   2）1684x

      a）进入u-boot模式（1684x开机迅速点击回车键）

         添加linux kernel参数crashkernel=512M；

         .. code-block:: bash

            bm1684# setenv othbootargs ${othbootargs}  "crashkernel=512M"

         .. image:: ./_static/image52.png
            :width: 7.6023622in
            :height: 2.02864in

         保存配置：

         .. code-block:: bash

            bm1684# saveenv

         .. image:: ./_static/image53.png
            :width: 4.8976378in
            :height: 0.5in

      重启1684x
      以下操作无特别说明，均是在1684x ubuntu环境。

      b）sd card

         创建sd卡mount目录

            .. code-block:: bash

               sudo mkdir /mnt/sdcard/

      c）kexec/kdump-tools

         系统已经安装kexec-tools，本文忽略它的安装

         安装kdump-tools

            .. code-block:: bash

                sudo apt install kudmp-tools

         由于kudmp-tools配置存储coredump文件在sd卡上，防止系统crash重启后，挂载sd卡失败，导致存储coredump文件到本地/mnt/sdcard/crash而非sd卡上，需要disable kdump-tool.service

            .. code-block:: bash

                sudo systemctl disable kdump-tools.service

         修改kdump-tool配置

            .. code-block:: bash

                sudo vi /etc/default/kdump-tools
                  KDUMP_COREDIR="/mnt/sdcard/crash"
                    //去掉systemd.unit=kdump-tools-dump.service

                  KDUMP_CMDLINE_APPEND="reset_devices
                  nr_cpus=1"

      d）makedumpfile

            .. code-block:: bash

               sudo apt install makedumpfile

         由于该包中的makedumpfile（v1.6.7）命令有bug，需要使用随本文一起发布的 makedumpfile（v1.7.1）替换

            .. code-block:: bash

               sudo mv /usr/bin/makedumpfile  /usr/bin/makedumpfile
               .orig

               sudo cp /home/linaro/kdump/makedumpfile  /usr/bin/
               makedumpfile

         或者下载源码编译makedumpfile（https://github.com/makedumpfile/makedumpfile/tags）

         编译前需要安装libelf-dev libdw-dev libbz2-dev

         选择1.7.1以上版本，在1684x ubuntu本地编译命令：make

      e）crash kernel & initrd

         由于kernel和initrd是被打包到itb中，所以需要从itb中解出，并拷贝到kdump-tool配置文件中指定的目录

            .. code-block:: bash

               mkdir /home/linaro/crash
               dumpimage -T flat_dt -p 0 -o /home/linaro/crash/
               vmlinuz-`uname -r` /boot/emmcboot.itb
               dumpimage -T flat_dt -p 1 -o /home/linaro/crash/
               initrd.img-`uname -r` /boot/emmcboot.itb

               sudo cp /home/linaro/crash/vmlinuz-`uname -r` /boot/
               sudo mkdir /var/lib/kdump
               sudo cp /home/linaro/crash/initrd.img-`uname -r` /var/
               lib/kdump

2.kdump/crash使用

   1）kdump加载crash kernel并生成coredump文件

      a）查看/proc/cmdline，查看crashkernel参数是否配置正确

         .. image:: ./_static/image54.png
            :width: 4.8976378in
            :height: 0.3031496in

      b）加载crash kernel

         .. code-block:: bash

            sudo kdump-config load

         .. image:: ./_static/image55.png
            :width: 4.8976378in
            :height: 0.6968504in

      c）kernel panic

         | 插入SD卡
         | 触发kenrel panic

         .. code-block:: bash

            sudo su

            echo c > /proc/sysrq-trigger （触发kenrel panic，并重启系统）

      d）存储coredump文件

         系统重启后, 查看是否存在/proc/vmcore文件

         .. image:: ./_static/image56.png
            :width: 3.1968504in
            :height: 0.3976378in


         .. code-block:: bash

            sudo mount /dev/mmcblk1p1 /mnt/sdcard
            //根据实际情况，使用正确的sd卡设备挂载目标文件
            //可先用：fdisk -l 命令查看设备信息

            sudo kdump-config savecore

         .. image:: ./_static/image57.png
            :width: 8.1968504in
            :height: 3.8031496in

   2）crash 分析 crashdump文件

      把sd卡插入linux主机，使用如下命令分析coredump文件

         .. code-block:: bash

            sudo ./crash ./vmlinux /mnt/sdcard/crash/202208100944/
            vmcore.202208100944

         您需要将/mnt/sdcard/替换成主机的SD卡路径

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
