
2. 前言
============

2.1. 文档概述
-----------------

本文档详细介绍了 |Product| EVB 开发板的外观特点、应用场景、设备参数、配套软件等，使得该设备的用户及开发者对 |Product| EVB 开发板有比较全面深入的了解。设备用户及开发者可依据此手册，开展对该设备的安装、调试、部署、维护等一系列工作。

2.2. 读者对象
-----------------

本文档主要适用于如下人员：

-  算丰FAE工程师、售前工程师

-  生态合作伙伴的开发人员

-  用户企业研发工程师、售前工程师

2.3. 约定的符号、标志、专用语解释
-------------------------------------

在本文中可能出现如下符号、标志，它们所代表的含义如下：

+--------------+--------------------------------------------------------+
| |image1|     |                                                        |
|              |                                                        |
| 危险         |表示有高度危险，如果不能避免，可能导致人员伤亡或严重伤害|
+--------------+--------------------------------------------------------+
| |image2|     | 表示有中度或低                                         |
|              |                                                        |
| 警告         | 度潜在危险，如果不能避免，可能导致人员轻微或中等伤害   |
+--------------+--------------------------------------------------------+
| |image3|     | 表示有潜在风险，如果忽视这部分文本，可能               |
|              |                                                        |
| 注意         | 导致设备损坏、数据丢失、设备性能降低或不可预知的结果   |
+--------------+--------------------------------------------------------+
| |image4|     | 防静电标识，表示静电敏感的设备或操作                   |
|              |                                                        |
| 防静电       |                                                        |
+--------------+--------------------------------------------------------+
| |image5|     | 电击防护标识，标识高压危险，需做好防护                 |
|              |                                                        |
| 当心触电     |                                                        |
+--------------+--------------------------------------------------------+
| |image6|     | 表示能帮助您解决某个问题或节省您的时间                 |
|              |                                                        |
| 窍门         |                                                        |
+--------------+--------------------------------------------------------+
| |image7|     | 表示是正文的附加信息，是对正文的强调和补充             |
|              |                                                        |
| 说明         |                                                        |
+--------------+--------------------------------------------------------+

2.4. 缩略语
---------------

+-----------------+----------------------------+-----------------------+
| JPU             | JPEG Process Unit          | JPEG处理单元          |
+-----------------+----------------------------+-----------------------+
| VPP             | Video Post Process         | 图像后处理            |
+-----------------+----------------------------+-----------------------+
| VPU             | Video Process Unit         | 视频编解码单元        |
+-----------------+----------------------------+-----------------------+

2.5. 修改记录
-----------------

+-------------+-------------+-------------+-----------------+-------------+
| 文档版本    | 发布日期    | 修订说明    | 对              | 对          |
|             |             |             | 应硬件版本      | 应软件版本  |
+-------------+-------------+-------------+-----------------+-------------+
| V0.1        | 2022-07-13  | 首          | BM1684X EVB:V1.1| 0.2.3       |
|             |             | 次正式发布  |                 |             |
+-------------+-------------+-------------+-----------------+-------------+


2.6. 声明
------------------

Copyright ©️2022 北京算能科技有限公司。

我们对本产品手册及其中的内容具有全部的知识产权。除非特别授权，禁止复制或向第三方分发。凡侵犯本公司版权等知识产权权益的行为，本公司保留依法追究其法律责任的权利。

本产品系列将有不断地更新迭代，我们将定期检查本产品手册中的内容，在后续的版本中将出现不可避免的修正、删减、补充。

我们保留在不事先通知的情况下进行技术改进、文档变更、产品改进升级、增加或减少产品型号和功能的权利。

3. 硬件安装
============

3.1. 板卡准备
---------------

|Product| EVB 开发板仅指包括BM1684X、LPDDR4X、eMMC等核心组件的板卡，如下图：

|Product| EVB 正面

   .. image:: ./_static/image8.png
      :width: 8in
      :height: 4in

|Product| EVB 背面

   .. image:: ./_static/image9.png
      :width: 8in
      :height: 4in

各部件位置指示图如下:

   .. image:: ./_static/image51.jpg
      :width: 12in
      :height: 4in

为方便后面的描述，下文以“核心板”指代这块板卡。

核心板支持SoC模式和Pcie模式，也可以称为RC模式和EP模式，本文档只介绍SoC模式（RC模式）。

3.2. 附件介绍
--------------

为方便调试，建议您准备如下附件：

a. USB转UART线缆一条：核心板引出的UART0(UART for BM1684X)为调试口，TTL电平，波特率115200，8比特数据，1比特停止位，无奇偶校验，无硬件流控。

b. 以太网线缆一条：接以太网口0（eth0），预装系统默认设置为DHCP，所以将 |Product| 通过eth0和您的调试机都部署在同一路由器下比较方便。

c. SD卡一张：刷机或调试时使用，建议8GB/class10或更高规格。

d. |image8|\ 与您的底板设计相匹配的电源：如果您使用我们提供的参考底板，配套直流电源输出为12V/10A，5.5*2.1mm母头，中心为正极。

e. 散热：请安装散热片、风扇等必要的散热设备，以免出现过热关机等异常状况。


3.3. 上电开机
---------------

一切就绪后，您就可以为底板加电了，如果您使用我们提供的参考底板，请先插上电源，然后拨电源键（此时从串口终端应该也应可以看到log打印了），指示灯正常状态如下：

   .. image:: ./_static/image12.png
      :width: 6.27083in
      :height: 4.29167in

请检查您的串口终端，|Product| 对于我们适配的Ubuntu 20.04系统，初始用户名和密码均为linaro（root账户无初始密码，使用前需要先用命令 ``sudo passwd root`` 设置密码）：

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


如果需要手工配置静态IP，可按如下方法修改 ``/etc/netplan/01-netcfg.yaml`` 配置文件，并使能所修改的配置文件，这里给出一个实例，具体netplan工具的使用说明请自行搜索：

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

关机时建议使用 ``sudo poweroff`` 命令，尽量避免直接断电，以免文件系统损坏。\ |image9|


核心板有两个网卡，eth0默认为DHCP，故您需要通过上述方法获取IP。eth1默认配置为静态IP：192.168.150.1。

4. 软件安装
============

4.1. 检查预装版本
-------------------

|Product| 出厂时已经预装系统软件，在Ubuntu下可通过如下命令检查其版本：

a. 查看Linux kernel版本：bm_version

   .. code-block:: bash

      $ bm_version
      SophonSDK version: v23.09 LTS-SP3
      sophon-soc-libsophon : 0.5.1
      sophon-soc-libsophon-dev : 0.5.1
      sophon-mw-soc-sophon-ffmpeg : 0.11.0
      sophon-mw-soc-sophon-opencv : 0.11.0
      BL2 v2.7(release):b0dc29c Built : 10:20:22, Aug 15 2024
      BL31 v2.7(release):b0dc29c Built : 10:20:22, Aug 15 2024
      U-Boot 2022.10 b0dc29c (Aug 15 2024 - 10:20:18 +0800) Sophon BM1684X
      KernelVersion : Linux bm1684 5.4.217-bm1684-g3357dba62ec6 #1 SMP Thu Aug 15 10:20:28 CST 2024 aarch64 aarch64 aarch64 GNU/Linux
      HWVersion: 0x00
      MCUVersion: 0x04

   1. SophonSDK后面的信息为SOPHON SDK的版本号。
   2. sophon-mw-soc-sophon-ffmpeg、sophon-mw-soc-sophon-opencv和sophon-soc-libsophon后面的信息是各个组件的版本号。
   3. BL2、BL31、U-Boot后面的信息分别为bl2、bl31和uboot的bootloader版本号及build时间。
   4. KernelVersion字段即为Kernel版本信息， 5.4.202表示官方Linux Kernel确切版本号， 后半部分的时间戳代表build时间。
   5. MCUVersion字段即为MCU firmware版本号。

b. 对于我们官网发布的包，SDK版本号和小组件版本之间有对应关系，如下：

   .. list-table:: 版本号对应关系
      :widths: 25 25 25
      :header-rows: 1

      * - SDK大版本号
        - libsophon版本
        - 多媒体组件版本
      * - V22.09.02
        - 0.4.1
        - 0.3.1
      * - V22.10.01
        - 0.4.2
        - 0.4.0
      * - V22.11.01
        - 0.4.3
        - 0.5.0
      * - V22.12.01
        - 0.4.4
        - 0.5.1
      * - V23.03.01
        - 0.4.6
        - 0.6.0
      * - V23.05.01
        - 0.4.8
        - 0.6.3
      * - V23.07.01
        - 0.4.9
        - 0.7.0
      * - V23.09 LTS
        - 0.4.9-LTS
        - 0.7.1
      * - V23.09 LTS SP1
        - 0.4.9-LTS
        - 0.8.0
      * - V23.09 LTS SP2
        - 0.4.9-LTS
        - 0.8.0
      * - V23.09 LTS SP3
        - 0.5.1-LTS
        - 0.11.0
      * - V23.10.01
        - 0.5.0
        - 0.7.3
      * - V24.04.01
        - 0.5.1
        - 0.10.0

4.2. 软件更新
---------------

|Product| 目前提供三种更新方式：SD卡刷机、TFTP刷机、文件替换和在线刷机，他们的关系如下

.. list-table:: 刷机方式对比
   :widths: 25 25 25
   :header-rows: 1

   * - 刷机方式
     - 刷机成功依赖
     - 烧录内容
   * - SD卡刷机
     - | 1. 设备硬件功能正常
       | 2. SD卡为MBR+FAT32格式
     - | 1. 设备flash
       | 2. 设备emmc
   * - TFTP刷机
     - | 1. 设备硬件功能正常
       | 2. 设备flash中固件正常
     - | 1. 设备flash
       | 2. 设备emmc
   * - 文件替换
     - | 1. 设备硬件功能正常
       | 2. flash和emmc正常
       | 3. 设备软件系统正常
     - 被替换的部分
   * - 在线刷机
     - | 1. 设备硬件功能正常
       | 2. flash和emmc正常
       | 3. 设备软件系统正常
       | 4. 刷机前后的分区表不能发生变动
     - | 1. 设备flash
       | 2. 设备emmc中除分区表和data分区外的部分

总结如下：

1. 其中SD卡刷机、TFTP刷机和在线刷机会重写整个eMMC，也即您存储在eMMC的数据全部会丢失。
2. SD卡刷机方式最为干净可靠，理论上只要您的没有硬件损坏，都可以进行SD卡刷机。
3. 在线刷机则要求设备至少能够通过串口或网络方式连接进入终端且刷机前后的分区表不能发生变动。
4. 文件替换方式是指在Ubuntu下通过替换对应文件的方式分别升级bootloader、kernel和其它软件。这种方式有一定的风险，如不同软件组件之间的版本匹配、文件损坏等。

以下分别介绍各种软件更新方式的操作：

4.2.1. SD卡刷机
~~~~~~~~~~~~~~~

   1. 请将SD卡格式化为MBR分区表，且第一个分区是FAT32格式的状态，分区大小需要放下整个刷机包。

      1. 如果不方便手动格式化SD卡，则可以通过如下操作制作MBR+FAT32的SD卡：

         1. 下载压缩包 `sdcard_imgs.zip` https://sophon-file.sophon.cn/sophon-prod-s3/drive/23/11/09/18/sdcard_imgs.zip ，解压后文件类似下图，按照TF卡大小和刷机包大小选择合适的img.gz文件

            .. image:: ./_static/image98.png
               :width: 4.5in
               :height: 2in

            比如4GB的TF卡，则选择其中sdcard.3G.img.gz包
         2. 访问balenaEtcher工具官网 https://etcher.balena.io/ ，下载工具将选择的img.gz文件写入TF卡
         3. 格式正确的SD卡制作完毕
   2. 请下载 |Product| 最新的SD卡刷机包，位置在SDK压缩包中 ``sophon-img_<date>_<hash>`` 目录下的sdcard.tgz。
   3. 请将下载的压缩包解压到SD卡根目录。确认文件如下（数量不一定相同）：

      .. image:: ./_static/image18.png
         :width: 4.5in
         :height: 2in

   4. 请将 |Product| 断电，插入SD卡，并连接串口终端，然后给 |Product| 上电。您将看到 |Product| 自动进入刷机流程：

      .. image:: ./_static/image19.png
         :width: 6.27083in
         :height: 2.69444in

   5. 刷入1GB的包通常耗时约3分钟，可以根据这个数据预估刷机时间，结束后，会看到拔掉SD卡并重启 |Product| 的提示，请依照操作即可，（同时在一些SE5或SE7设备上刷机成功后会有一个状态灯一直闪烁）：

      .. image:: ./_static/image20.png
         :width: 4.23438in
         :height: 0.83192in

   6. 请注意：刷机后Ubuntu系统第一次启动时会进行文件系统初始化等关键动作，请勿随意断电，待开机进入命令行后使用sudo poweroff命令关机。

4.2.2. TFTP刷机
~~~~~~~~~~~~~~~

   1. 请下载 |Product| 最新的SD卡刷机包，位置在SDK压缩包中 ``sophon-img_<date>_<hash>`` 目录下的tftp.tgz。
   2. 在PC上安装tftp server，并指定tftp刷机包路径：

      1. Ubuntu系统：运行： apt-get install tftpd-hpa tftp-hpa ，下载tftp工具；然后查看 /etc/default/tftpd-hpa 文件中的 TFTP DIRECTORY 路径，将刷机包拷贝进去（您也可以修改这个路径配置， sudo service tftpd-hpa restart 后即可生效）;
      2. windows系统： 点击链接下载 https://pjo2.github.io/tftpd64/ ，随后打开下载好的 tftpd64.exe 图形界面，并将 Current Directory 设置指向tftp刷机包解压后的文件夹。

      .. warning::
         1. 使用的 PC 推荐尽可能使用 Ubuntu 系统，Windows 下的 tftpd64 对环境比较挑剔，在传输大文件时有时会不稳定，造成升级失败。
         2. tftp server 搭建好后，您可以用另一台 PC 先测试一下，避免网络、防火墙等配置问题。

   3. 搭建基础网络环境：将需要升级的设备和 PC 机放在同一个路由器下（也可以通过设备LAN口直连PC）。
   4. 执行刷机步骤：

      1. 将需要升级的设备接上串口终端，启动盒子，快速按回车，进入uboot指令模式；
      2. 输入如下指令：

         .. code-block:: bash

            setenv serverip 192.168.150.2
            setenv ipaddr 192.168.150.1
            setenv gatewayip 192.168.150.2
            setenv update_all 0
            setenv reset_after 1
            tftp 0x310000000 boot.scr
            source 0x310000000
            set netretry yes

         .. warning::
            指令中的serverip为tftp服务器地址，ipaddr为盒子的ip地址，gatewayip为网关地址，需要根据实际情况进行调整； 在window使用场景下，通常是使用盒子的lan口和PC端进行连接，此时serverip和gatewayip是相同的； 用户可以在执行tftp指令之前先ping一下serverip，确认一下连接状态。

      3. 随后开始刷机，您会看到#号表示的进度。
      4. 由于通过指令配置了环境变量 reset_after 1 ，在刷机完成后系统将会重新启动。同时，指令 set netretry yes 将传输超时后进行重试，而非直接重新启动设备。需要注意的是，如果刷机失败，系统同样会自动重启。请根据执行结束后的提示来判断刷机是否成功完成。

4.2.3. 文件替换
~~~~~~~~~~~~~~~

   文件替换均在Ubuntu下执行，您可以选择使用串口或SSH终端。需要替换的组件包括内核镜像、flash固件、TPU控制模块固件和SophonSDK运行时环境等。以下分别介绍如何替换各个组件。

   1. 首先获取待更新版本的SophonSDK压缩包，获取其sophon-img子文件夹下的bsp_update.tgz和system.tgz压缩包。
      其中bsp_update.tgz主要包含升级脚本（bsp_update.sh）及内核镜像（emmcboot.itb）等内容，解压后的文件如下：

         .. image:: ./_static/image94.jpg


   2. 将两个压缩包拷贝到模组的某一路径如家目录（/home/linaro）下，解压bsp_update.tgz压缩包并进入解压后的目录，执行bsp_update.sh升级脚本。该步骤会替换boot分区的内核镜像、flash固件，并替换TPU控制模块固件，可使用如下命令：

      .. code-block:: bash

         tar zxvf bsp_update.tgz
         cd bsp_update
         sudo ./bsp_update.sh


   3. 替换SophonSDK运行时环境。SophonSDK运行时环境位于/opt目录下，回退至system.tgz所在目录，执行如下命令将system.tgz中的内容解压至/opt/sophon/libsophon-0.5.0目录下：

      .. code-block:: bash

         sudo tar xzf system.tgz -C /opt/sophon/libsophon-0.5.0
         sudo sync


   4. 关机重启检查是否升级成功（可以通过bm_version查看kernel版本及libsophon的版本信息）。以下为升级前后的对比示例：

      .. image:: ./_static/image95.jpg

      .. image:: ./_static/image96.jpg


   5. 如有内核开发的需求，需要升级内核开发软件包。同理，从对应版本的SophonSDK压缩包中获取bsp-debs将其拷贝至家目录（/home/linaro）下并在bsp-debs下创建linux-headers-install.sh脚本，脚本内容如下：

      .. code-block:: bash

         #!/bin/bash

         cur_ver=$(uname -r)
         echo ${cur_ver}
         sudo mkdir -p /lib/modules/${cur_ver}
         if [ -e /home/linaro/bsp-debs/linux-headers-${cur_ver}.deb ]; then
               if [ -d /lib/modules/${cur_ver} ]; then
                        sudo dpkg -i /home/linaro/bsp-debs/linux-headers-${cur_ver}.deb
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

      如果遇到linux-headers-install.sh没有执行权限，使用如下命令增加权限：

      .. code-block:: bash

         chmod +x linux-headers-install.sh.sh

      若脚本执行过程中出现缺少flex等错误，可执行如下命令安装相关环境：

      .. code-block:: bash

         sudo apt install flex bison libssl-dev

   6. 替换libsophon和sophon-mw相关deb包。将相关包放置在当前工作目录，通过以下命令逐个安装。其中x.y.z为要安装的版本号，arch为目标平台架构（x86_64平台对应amd64，arm平台对应aarch64），请根据实际版本和架构进行替换。

      .. code-block:: bash

         sudo dpkg -i sophon-mw-soc-sophon-ffmpeg_x.y.z_arch.deb
         sudo dpkg -i sophon-mw-soc-sophon-ffmpeg-dev_x.y.z_arch.deb
         sudo dpkg -i sophon-mw-soc-sophon-opencv_x.y.z_arch.deb
         sudo dpkg -i sophon-mw-soc-sophon-opencv-dev_x.y.z_arch.deb
         sudo dpkg -i sophon-soc-libsophon_x.y.z_arch.deb
         sudo dpkg -i sophon-soc-libsophon-dev_x.y.z_arch.deb

   .. warning::

      做完上述文件操作后不要马上暴力断电，否则可能会有文件损坏，请执行sync、sudo reboot、sudo poweroff等动作。\ |image10|

4.2.4. 在线刷机
~~~~~~~~~~~~~~~~~~~~~

   该方式同样要用到SD卡刷机包sdcard.tgz，并且在完成后会清除eMMC除了/data分区下的所有用户文件。将获取到的压缩文件传输到目标平台，同目录下执行以下命令：

      .. code-block:: bash

         tar -zxvf sdcard.tgz
         sudo mkdir /data/ota
         sudo mv sdcard/* /data/ota
         cd /data/ota
         sudo ./local_update.sh md5.txt

   请注意，以上操作会立即触发设备重启，随后设备将在uboot下自动进行升级，通过串口输出调试信息。升级过程中请不要断电，等待完成即可。

4.2.5. MCU固件在线升级
~~~~~~~~~~~~~~~~~~~~~~~~~~~

   |image11|\ 替换MCU固件：核心板上有一颗MCU负责 |Product| 的上电时序等重要工作，它的固件只能通过下面的命令升级，不能通过SD卡升级。这颗MCU的固件如果烧写错误，会造成 |Product| 无法上电，此时就只能通过专用的烧写器进行修复了，因此请谨慎操作，通常也并不需要对它进行升级。命令：sudo mcu-util-aarch64 upgrade 1 0x17 bm1686evb-mcu.bin。升级完成后请执行sudo poweroff，待关机动作完成后（串口会打印NOTICE: CPU0 bm_system_off，并且盒子的风扇声音会突然变大）对盒子进行断电后重新上电。

5. 系统软件构成
================

5.1. 启动流程
-----------------

|Product| 的系统软件属于典型的嵌入式ARM64
Linux，由bootloader、kernel、ramdisk和Ubuntu 20.04
构成，当开机后，依次执行如下：

   .. image:: ./_static/image22.png
      :width: 6.27083in
      :height: 0.90278in

其中：boot
ROM、bootloader基于arm-trusted-firmware和u-boot构建；kernel基于Linux的5.4分支构建；Ubuntu 20.04
基于Ubuntu官方arm64源构建，不包含GUI相关组件。

5.2. eMMC分区
-----------------

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
| /dev/mmcblk0p6    | /opt           | EXT4        | 存放                     |
|                   |                |             | sdk的驱动和运行时环境    |
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

eMMC的boot0分区的前1M空间被用于存放uboot env数据，使用者存放自定义信息时需要避开该区域。

5.3. docker
---------------

核心板系统默认有docker服务，您可以用docker info命令查看状态。注意docker的根目录被配置到了/data/docker目录下，与默认设置不同。

当前由 `/etc/systemd/system/docker.service.d/docker.conf` 文件进行配置。

5.4. 命令审计
---------------

核心板系统中有一个命令记录的服务，会将在终端执行的所有命令及其返回值记录到文件 `/var/log/prompt-cmd.log` 中。

当前由 `/etc/logrotate.d/prompt-command-log` 、 `/etc/rsyslog.d/90-prompt-command.conf` 文件进行配置。

5.5. 文件系统支持
---------------------

如果您使用参考底板，当插入U盘或者移动硬盘后（需考虑USB供电能力），存储设备会被识别为/dev/sdb1或类似节点，与桌面PC Linux环境下相同。

文件系统支持FAT、FAT32、EXT2/3/4、NTFS。在 |Product| 下，FAT、FAT32、EXT2/3/4支持自动挂载，设备插入后会自动挂载到/media/usb-xxx下。

当访问NTFS格式的存储设备时，预装的内核版本仅支持读取，如果需要写入，需要手工安装ntfs-3g软件包，请参考\ https://wiki.debian.org/NTFS\ 。

完成数据写入后，请及时使用sync或umount操作，关机时请使用sudo poweroff命令，避免暴力下电关机，以免数据丢失。

5.6. 修改SN和MAC地址
------------------------

|Product| 的SN和MAC地址存放在MCU的EEPROM中，你可以通过如下方式进行修改。

首先需要解锁MCU EEPROM：

   .. code-block:: bash

      sudo -i
      echo 0 > /sys/devices/platform/5001c000.i2c/i2c-1/1-0017/lock

写入SN（假设SN为HQATEVBAIAIAI0001）：

   .. code-block:: bash

      echo -en "HQATEVBAIAIAI0001\0" > sn.txt
      dd if=sn.txt of=/sys/bus/nvmem/devices/1-006a0/nvmem count=32 bs=1

count参数最大是32。

读取SN：

   .. code-block:: bash

      sudo -i
      dd if=/sys/bus/nvmem/devices/1-006a0/nvmem count=32 bs=1 2>/dev/null

其中count参数最大为32

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

5.7. 读写eFuse
--------------------

5.7.1. eFuse寻址
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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

5.7.2. eFuse分区
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

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
        - 产品生产测试信息预留区域
      * - 64~82
        - 产品生产测试信息预留区域

其余未注明区域目前没有特定用途，可以用作存储或实验之用。

5.7.3. eFuse工具
~~~~~~~~~~~~~~~~~~~~~~~~

|Product| 中预装了一个eFuse读写工具，读写操作命令如下：

sudo efuse -r 0x? -l 0x? 即可以返回从该地址开始存储的若干个32bit值；

sudo efuse -w 0x? -v 0x? 即可在该地址写入指定的32bit值。

以上数值均只支持十六进制数。

5.7.4. SPACC+eFuse加解密实例
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   .. code-block:: bash

      #include <stdio.h>
      #include <sys/socket.h>
      #include <linux/if_alg.h>
      #include <string.h>
      #include <errno.h>
      #include <stdlib.h>
      #include <unistd.h>

      /*
      要与内核加密API交互，用户空间应用程序必须创建一个套接字socket。用户空间使用send/write系统调用族调用密码操作。密码运算的结果是通过read/recv系统调用获得的。
      */

      #ifndef AF_ALG
      #define AF_ALG 38
      #endif

      #ifndef SOL_ALG
      #define SOL_ALG 279
      #endif

      /* 配置是否使用efuse中的密钥 */
      #define SET_KEY_EFUSE 1
      /* 选择接收的系统调用接口 0-recvmsg 1-read 2-recv */
      #define RECV 1

      extern int errno;

      void print(char* src, int len) {

         int i;
         for (i = 0; i < len; i++) {
            printf("%x", (unsigned char)src[i]);
         }
         putchar('\n');
      }


      int setkey(int fd, char* key, int keylen) {
         /*
         调用应用程序必须使用ALG_SET_KEY的setsockopt()选项。
         如果没有设置该键，则执行HMAC操作时不会因该键导致初始HMAC状态改变。
         */
         int err = setsockopt(fd, SOL_ALG, ALG_SET_KEY, key, keylen);
         if (err) {
            perror("setkey err");
            goto out;
         }
      out:
         err = errno;
         return err;
      }

      int sendmsg_to_crypto(int opfd, int cmsg_type, __u32 cmsg_data, char* plaintext_buf, int buflen) {
         /* 描述发送的消息 */
         struct msghdr msg = {};
         //struct cmsghdr *cmsg = malloc(CMSG_SPACE(sizeof(cmsg_data)));
         struct cmsghdr* cmsg = NULL;
         char buff[CMSG_SPACE(sizeof(cmsg_data))] = { 0 };
         /*
            struct iovec 结构体定义了一个向量元素
            通常这个 iovec 结构体用于一个多元素的数组，对于每一个元素，iovec 结构体的字段 iov_base 指向一个缓冲区，
            这个缓冲区存放的是网络接收的数据（read），或者网络将要发送的数据（write）。
            iovec 结构体的字段 iov_len 存放的是接收数据的最大长度（read），或者实际写入的数据长度（write）。
         */
         struct iovec iov;
         int err;

         /* 配置了socket的消息结构体 */
         msg.msg_iov = &iov;
         msg.msg_iovlen = 1;
         msg.msg_control = buff;
         msg.msg_controllen = sizeof(buff);

         /* 初始化控制消息的实例 */
         cmsg = CMSG_FIRSTHDR(&msg);

         cmsg->cmsg_level = SOL_ALG;
         cmsg->cmsg_type = cmsg_type;
         cmsg->cmsg_len = CMSG_SPACE(sizeof(cmsg_data));
         /*
            传输控制消息的data
            使用下列标志之一的密码操作类型的规范:
            ALG_OP_ENCRYPT 数据加密
            ALG_OP_DECRYPT 数据的解密
            IV信息的规范，标记为ALG_SET_IV标志
         */
         //memcpy(CMSG_DATA(cmsg), &cmsg_data, sizeof(cmsg_data));
         *(__u32*)CMSG_DATA(cmsg) = cmsg_data;

         /* 配置iov */
         iov.iov_base = plaintext_buf;
         iov.iov_len = buflen;

         /* 发送数据 */
         err = sendmsg(opfd, &msg, MSG_MORE);
         if (err == -1) {
            perror("sendmsg err");
            goto out;
         }
         else
            return err;
      out:
         err = errno;
         return err;
      }

      int recvmsg_from_crypto(int opfd, char* src, int len) {
         /* 初始化消息结构体和iov结构体用以接收数据 */
         struct msghdr msg = {};
         struct iovec iov;
         int err;
         msg.msg_iov = &iov;
         msg.msg_iovlen = 1;
         iov.iov_base = src;
         iov.iov_len = len;

         /* 接收数据 */
         err = recvmsg(opfd, &msg, 0);
         if (err == -1) {
            perror("recvmsg err");
            goto out;
         }
         else {
            /* 打印出接收到的加密后的数据 */
            printf("recvmsg_from_crypto hex: ");
            print(src, len);
            return err;
         }


      out:
         err = errno;
         return err;
      }

      char* text_align16(const char* src, long int* len) {
         /* 对字符串进行16字节对齐不足补\0，用于处理AES加密的16字节分组 */
         char* new_str;
         long int new_len = ((*len) / 16 + 1) * 16;
         new_str = malloc((*len) % 16 == 0 ? *len : new_len);
         memcpy(new_str, src, *len);
         if ((*len) % 16 == 0)
            return new_str;
         memset((new_str + (unsigned int)(*len)), 0, new_len - *len - 1);
         *len = new_len;
         return new_str;
      }

      int main(int argc, char** argv) {
         /* 使用带有-secure-key后缀的算法名可以让spacc使用efuse中的密钥 */
         struct sockaddr_alg sa = {
            .salg_family = AF_ALG,
            .salg_type = "skcipher",
      #if SET_KEY_EFUSE == 1
            .salg_name = "cbc(aes-secure-key)",
      #else
            .salg_name = "cbc(aes)",
      #endif
         };
         //char key_buf[16] = { 0xff, 0xd7, 0x40, 0x57, 0x47, 0x68, 0x5e, 0xd6, 0xe0, 0x0b, 0xc6, 0x82, 0xa7, 0x72, 0x86, 0x09 };
         char key_buf[16] = { 0 };
         char* encrypt_buf;
         char* decrypt_buf;
         char* plaintext_buf;
         long int plaintext_buf_len;
         int tfmfd;
         int opfd;
         int opfd2;
         int err;
         /* 实例需要加密的明文数据 */
         if (argc > 1)
            plaintext_buf = argv[1];
         else
            plaintext_buf = "Single block msgSingle block msg";
         plaintext_buf_len = strlen(plaintext_buf);
         /* 根据输入进行内存空间的申请，确保可以处理超大字符串 */
         encrypt_buf = malloc(plaintext_buf_len + 16);
         decrypt_buf = malloc(plaintext_buf_len + 16);
         plaintext_buf = text_align16(plaintext_buf, &plaintext_buf_len);
         printf("src text: %s len: %ld->%ld\n", plaintext_buf, strlen(plaintext_buf), plaintext_buf_len);
         /* 申请socket控制句柄 */
         tfmfd = socket(AF_ALG, SOCK_SEQPACKET, 0);
         err = bind(tfmfd, (struct sockaddr*)&sa, sizeof(sa));
         if (err) {
            perror("bind err");
            goto bind_err;
         }

         err = setkey(tfmfd, key_buf, sizeof(key_buf));
         if (err) {
            goto setkey_err;
         }

         /* 申请一个句柄，用于加密 */
         opfd = accept(tfmfd, NULL, 0);
         if (opfd == -1) {
            perror("accept err");
         }

         /* 申请一个句柄，用于解密 */
         opfd2 = accept(tfmfd, NULL, 0);
         if (opfd2 == -1) {
            perror("accept err");
         }

         /* 发送数据用以加密 */
         err = sendmsg_to_crypto(opfd, ALG_SET_OP, ALG_OP_ENCRYPT, plaintext_buf, plaintext_buf_len);
         if (err == -1) {
            goto sendmsg_err;
         }

         /* 接收加密后的数据 */
         /*
         使用recv()系统调用，应用程序可以从内核加密API读取加密操作的结果。
         输出缓冲区必须至少与保存加密或解密数据的所有块一样大。如果输出数据大小较小，则只返回符合输出缓冲区大小的块。
         */
         err = recvmsg_from_crypto(opfd, encrypt_buf, plaintext_buf_len);
         if (err == -1) {
            goto recv_err;
         }

         /* 发送数据用以解密 */
         err = sendmsg_to_crypto(opfd2, ALG_SET_OP, ALG_OP_DECRYPT, encrypt_buf, plaintext_buf_len);
         if (err == -1) {
            goto sendmsg_err;
         }
         int bytesToRecv = 0;

      #if RECV==0
         /* 接收加密后的数据 */
         err = recvmsg_from_crypto(opfd2, decrypt_buf, plaintext_buf_len);
         if (err == -1) {
            goto recv_err;
         }
         printf("recvmsg_from_crypto txt: %s len: %ld\n\n", decrypt_buf,strlen(decrypt_buf));
         /*下面是两个使用其他接口操作编解码的实例*/
      #elif RECV==1
         read(opfd2, decrypt_buf, plaintext_buf_len);
         printf("read txt: %s len: %ld\n", decrypt_buf,strlen(decrypt_buf));
      #else
         err = recv(opfd2, decrypt_buf, plaintext_buf_len, 0);
         if (err == -1)
            perror("recv error:");
         else
            printf("recv txt: %s len: %ld\n\n", decrypt_buf,strlen(decrypt_buf));
      #endif

      bind_err:
      setkey_err:
      accept_err:
      sendmsg_err:
      recv_err:
         close(tfmfd);
         close(opfd);
         close(opfd2);
         free(plaintext_buf);
         free(encrypt_buf);
         free(decrypt_buf);

         return 0;
      }

代码如上，仓库位置：https://github.com/sophgo/sophon-tools/tree/main/source/pspacc_efuse_demo

6. 系统接口使用
================

|Product| 的CPU占用率、内存使用率等信息均可使用标准的Linux
sysfs、procfs节点，或top等工具读取。以下仅介绍 |Product| 特有的一些接口或硬件使用方式。

6.1. 设备基础信息获取工具
----------------------------------

我们准备了一款获取基础信息的工具，它可以一并获取上述大部分信息和大部分linux系统信息，程序打印示例如下：

   .. code-block:: bash

      BOOT_TIME(s)|28236.15|
      DATE_TIME|2024-10-18 18:41:16 CST|
      WORK_MODE|SOC|
      CPU_MODEL|bm1684x|
      SHUTDOWN_REASON|10-17-22-22-23,NO_INFO 10-17-23-05-19,POWER_OFF|
      DDR_SIZE(MiB)|16384|
      EMMC_SIZE(MiB)|59648|
      SYSTEM_MEM(MiB)|3707|
      TPU_MEM(MiB)|7615|
      VPU_MEM(MiB)|1024|
      VPP_MEM(MiB)|3000|
      TPU_MEM_USAGE(%)|99.00|
      VPU_MEM_USAGE(%)|0|
      VPP_MEM_USAGE(%)|0|
      CPU_ALL_USAGE(%)|0.25,0.00,0.25,0.00,0.00|
      CPUS_USAGE(%)|1.96,0.00,1.96,0.00,0.00 0.00,0.00,0.00,0.00,0.00 0.00,0.00,0.00,0.00,0.00 0.00,0.00,0.00,0.00,0.00 1.92,0.00,1.92,0.00,0.00 1.96,0.00,1.96,0.00,0.00 0.00,0.00,0.00,0.00,0.00 0.00,0.00,0.00,0.00,0.00|
      VPU_USAGE(%)|0,0,0|
      VPP_USAGE(%)|0,0|
      SYSTEM_MEM_USAGE(%)|31.88|
      DTS_NAME|bm1684x_se7_v1.dtb|
      DEVICE_MODEL|SE7 V1|
      CPU_CLK(Hz)|1800000000|
      TPU_CLK(Hz)|850000000|
      VPU_CLK(Hz)|500000000|
      CHIP_SN|C1710AC0H24220215|
      DEVICE_SN||
      ETH0_MAC|5c:f8:38:70:6d:7a|
      ETH1_MAC|5c:f8:38:70:6d:7b|
      CHIP_TEMP(degree Celsius)|68|
      BOARD_TEMP(degree Celsius)|68|
      DTS_THERMAL_TEMP(degree Celsius)|85 90 95|
      VTPU_POWER(W)|3|
      VTPU_VOLTAGE(mV)|726|
      VDDC_POWER(W)|3|
      VDDC_VOLTAGE(mV)|877|
      V12_POWER(mW)|17496|
      TPU_USAGE(%)|0|
      BOARD_TYPE|0x33|
      MCU_VERSION|0x02|
      KERNEL_VERSION|5.4.217-bm1684-g27254622663c|
      KERNEL_BUILD_TIME|#1 SMP Mon Jun 24 16:02:21 CST 2024|
      SYSTEM_TYPE|Ubuntu 20.04 LTS|
      DOCKER_VERSION|Docker version 27.3.0, build e85edf8|
      MMC0_CID|9b0100593053303634004d1927d4aa00|
      DISK_INFO|/data:1% /media/root-ro:100% /media/root-rw:13% /opt:14% /recovery:3% /boot:53% /data2:4%|
      SDK_VERSION|v24.04.01|
      LIBSOPHON_VERSION|0.5.1|
      SOPHON_MEDIA_VERSION|0.10.0|

此工具名为 ``get_info`` ，其工程链接如下：https://github.com/sophgo/sophon-tools/tree/main/source/pget_info

6.2. 读取核心板序列号
---------------------------

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

命令：

   .. code-block:: bash

      cat /factory/OEMconfig.ini

返回：

   .. code-block:: bash

      linaro@bm1684:~/bsp-debs$ cat /factory/OEMconfig.ini
      [BASE]
      SN = BJSNS7MBCJGJA00WM
      MAC0 = 58 c4 1e e0 1a 90
      MAC1 = 58 c4 1e e0 1a 95
      PRODUCT_TYPE = 0x01
      AGING_FLAG = 0x01
      DDR_TYPE = 16GB
      BOARD_TYPE = V12
      BOM = V12
      MODULE_TYPE = SE6 DUO
      EX_MODULE_TYPE = SE6 DUO
      PRODUCT = SE6
      VENDER = SOPHGO
      ALGORITHM = 3RDPARTY
      DEVICE_SN =
      DATE_PRODUCTION =
      PASSWORD_SSH = linaro
      USERNAME = admin
      PASSWORD = admin

命令：

   .. code-block:: bash

      bm_get_basic_info

返回：

   .. code-block:: bash

      linaro@bm1684:~/bsp-debs$ bm_get_basic_info
      ------------------------------------------------------------------------
      chip sn: BJSNS7MBCJGJA00WM
      device sn:
      hostname: bm1684
      uptimeInfo: up 14 minutes
      boardtemperature: 41
      coretemperature: 41
      ------------------------------------------------------------------------

6.3. 读取BM1684X片上温度
----------------------------

命令：

   .. code-block:: bash

      cat /sys/class/thermal/thermal_zone0/temp

返回（单位为毫摄氏度）：

   .. code-block:: bash

      38745

即38.745摄氏度。

6.4. 读取核心板温度
----------------------

命令：

   .. code-block:: bash

      cat /sys/class/thermal/thermal_zone1/temp

返回（单位为毫摄氏度）：

   .. code-block:: bash

      37375

即37.375摄氏度。

核心板温度通常会比前面读取的片上结温内部温度低。

6.5. 读取功耗信息
------------------

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
      ISL68127 output power: 2W → NPU功耗
      ISL68127 switch to output 1, ret=0
      ISL68127 output voltage: 898mV
      ISL68127 output current: 2900mA
      ISL68127 temperature 1: 58°C
      ISL68127 output power: 2W → CPU/Video等功耗

第一组信息为npu，第二组信息为cpu等。

pmbus 读取的是给npu和cpu供电的传感器的温度，所以更接近核心板温度，如果需要读取温度相关，请参考4.2和4.3。

当使用BM1684设备时，命令如下：

   .. code-block:: bash

      sudo pmbus -d 0 -s 0x5c -i

返回结果格式与BM1684X相同。

6.6. 使用GPIO
------------------

BM1684X 包含3组GPIO控制器，每个控制32根GPIO，与Linux的设备节点对应如下：

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

6.7. 使用UART
--------------------

|Product| 的144pin
BTB接口上提供了3组UART，其中UART0已用作bootloader和Linux的console端口。

6.8. 使用I2C
----------------------

|Product| 的144pin BTB接口上提供了1组I2C
master，对应设备节点为/dev/i2c-2，可以使用标准的I2C tools和API操作。

在我们的参考底板上， |Product| 通过这组I2C连接了底板上的RTC设备。

6.9. 使用PWM
----------------------

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

在我们的参考底板上，这个PWM输出被用作风扇调速，Linux的thermal框架会自动根据片上温度调整风扇转速。所以您会在第一步export时看到Device
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

6.10. 风扇测速
-----------------------

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

同时提供了一个netlink事件，当风扇停转时告警，示例代码可以从bsp-sdk/linux-arm64/tools/fan_alert获取。

6.11. 查询内存用量
----------------------------

BM1684X 板载了16GB DDR，可以分为三类：

1. kernel管理的部分，即可以用malloc、kmalloc等常规API分配出来使用。

2. ION管理的部分，预留给NPU、VPU、VPP使用，需要使用ION的ionctl接口，或使用bmnnsdk2中bmlib库提供的接口分配出来使用。

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
   heap（即三块预留的内存区域），如名字所示，分别供NPU、VPU、VPP使用。以上示例中只打印了每个heap使用信息的开头，如果完整地cat
   summary文件，可以看到其中分配的每块buffer的地址和大小信息。

7. 系统定制
============

因为 |Product| 的底板可以由您自行设计，我们提供了一个BSP SDK以便您对内核和Ubuntu
20.04系统进行定制，然后生成自己的SD卡或tftp刷机包。由于从V22.09.02开始我们修改了bootloader的代码，导致无法使用tftp从3.0.0及以前的版本升级到V22.09.02及以后的版本，这种情况下请使用SD卡刷机升级。因为 |Product| 核心板是制成品，故bootloader并未开放，如果需要定制请联系技术支持。

如果您只是希望部署自己的业务软件，并不涉及硬件修改，那么出于解耦的考虑，更推荐您把自己的业务软件打包成一个deb安装包。比如包含您的业务软件执行程序、依赖库、开机自启动服务等等，deb安装包里还可以放一个安装时自动执行的脚本，在安装时做一些配置文件修改替换之类的操作。这样您可以单独安装、卸载、升级您的业务软件，避免与我们系统包版本的依赖问题，对产品部署后的批量更新等操作也更友好。deb安装包的制作可以参考Debian\ `官方文档 <https://wiki.debian.org/Packaging/Intro>`__\ ，或其他网上资料。

7.1. 基于镜像方式自定义刷机包
------------------------------------------------

如果有一个设备已经把定制化的文件配置完毕了，可以使用 `socbak` 工具对该设备进行镜像操作，生成的刷机包可以用于其他同种设备。仓库链接：https://github.com/sophgo/sophon-tools

最新版本可以从网址：https://github.com/sophgo/sophon-tools/releases/latest 位置下载

如下是使用说明：

1. 确定使用条件

   1. 芯片：BM1684、BM1684X
   2. SDK版本： `v23.03.01` 之后版本
   3. 外置存储分区格式尽量保证ext4，且可用空间至少是当前emmc使用总量的2.5倍以上

2. 将外置存储插入目标设备，然后执行如下操作

   .. code-block:: bash

      sudo su
      cd /
      mkdir socrepack
      # 这一步需要根据你的外置存储选择挂载设备路径，但是目标路径必须是/socrepack
      mount /dev/sda1 /socrepack
      chmod 777 /socrepack
      cd /socrepack

3. 然后将从GitHub上下载的 `socbak.zip` 传输到 `/socrepack` 目录下，执行如下命令进行打包

   .. code-block:: bash

      unzip socbak.zip
      cd socbak
      export SOC_BAK_ALL_IN_ONE=1
      bash socbak.sh

4. 等待一段时间，执行成功后会生成如下文件

   .. code-block:: bash

      root@sophon:/socrepack/socbak# tree -L 1
      .
      ├── binTools
      ├── output
      ├── script
      ├── socbak.sh
      ├── socbak_log.log
      └── socbak_md5.txt

      3 directories, 3 files

5. 新的刷机包在 `output/sdcard` 下


7.2. 基于源码自定义刷机包
------------------------------------------------

7.2.1. 源码文件获取方式
~~~~~~~~~~~~~~~~~~~~~~~~~

1. bootloader-arm64仓库 https://github.com/sophgo/bootloader-arm64 编译刷机包的流程文件、ATF源码、UBOOT源码
2. linux-kernel源码仓库 https://github.com/sophgo/linux-arm64 编译刷机包使用的kernel源码
3. libsophon源码仓库 https://github.com/sophgo/libsophon 编译刷机包中算法加速驱动和中间件源码
4. mcu源码仓库 https://github.com/sophgo/mcu 核心板MCU固件源码
5. BSP_SDK二进制文件，该包中包含了ubuntu系统底包、交叉编译工具链等二进制文件，使用dfss工具下载

   .. code-block:: bash

      pip3 install dfss --upgrade
      python3 -m dfss --url=open@sophgo.com:/sophon-bsp/BSP_SDK.zip

7.2.2. 源码文件结构
~~~~~~~~~~~~~~~~~~~~

BSP
SDK包含两部分：一部分为github网站（https://github.com/sophgo）上发布的源码文件，bootloarder-arm64和linux-arm64；另一部分基本不会改动的二进制文件，为避免影响git效率，是通过NAS发布的。请参考bootloarder-arm64源码文件的README中的描述将两部分合并，将看到如下文件：

   .. code-block:: bash

      top
      ├── bootloader-arm64
      │   ├── scripts
      │   │    └── envsetup.sh → 编译脚本入口
      │   ├── trusted-firmware-a → TF-A源代码
      │   ├── u-boot → u-boot源代码
      │   ├── ramdisk
      │   │   └── build → ramdisk的cpio文件和u-boot启动脚本文件
      │   └── distro → Ubuntu 20.04的定制部分
      ├── distro
      │   └── distro_focal.tgz → Ubuntu 20.04的原始底包
      ├── gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu → 交叉编译工具链
      └── linux-arm64 → kernel源代码

7.2.3. 实机交叉编译
~~~~~~~~~~~~~~~~~~~~

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

即可得到新的emmcboot.itb。不建议您直接到linux-arm64目录下手敲make，除非您非常清楚如何操作。

内核的编译结果在如下路径：

   ::

      linux-arm64/build/bm1684/normal

编译出的ko可以在如下路径找到：

   ::

      linux-arm64/build/bm1684/normal/modules/lib/modules/5.4.202-bm1684/kernel

两个路径下的内容是一样的，默认已经打进刷机包。

编译出的linux-header安装包（用于在板卡上编译kernel
module）可以在如下路径找到：

   ::

      linux-arm64/build/bm1684/normal/debs

默认已经打进刷机包，即板卡上的/home/linaro/bsp-debs目录。

7.2.4. docker环境交叉编译
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

7.2.4.1. docker镜像的获取方式1: docker image
:::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

考虑到国内dockerfile可能编译不方便，这里提供一个docker image的下载方式

   .. code-block:: bash

      python3 -m pip install dfss --upgrade
      python3 -m dfss --dflag=cross_build_sophon_docker

7.2.4.2. docker镜像的获取方式2: Dockerfile
::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::::

1. dockerfile内容如下

   .. code-block:: bash

      # from ubuntu 20.04
      FROM ubuntu:20.04

      SHELL ["/bin/bash", "-c"]

      # Add apt sources
      RUN cp -a /etc/apt/sources.list /etc/apt/sources.list.bak \
      && sed -i 's@//.*archive.ubuntu.com@//mirrors.ustc.edu.cn@g' /etc/apt/sources.list

      # install pack
      RUN export DEBIAN_FRONTEND=noninteractive \
      && apt-get update \
      && apt-get upgrade -y \
      && apt-get install -y --no-install-recommends \
      wget curl rsync ca-certificates bc bison byobu cmake cpio debootstrap \
      device-tree-compiler dosfstools dpkg-dev exfat-utils fakeroot flex gcc kmod kpartx \
      language-pack-en language-pack-zh-hans git libssl-dev libxml2 libxml2-dev qemu-user \
      qemu-user-static rsync sudo u-boot-tools util-linux uuid uuid-dev lrzsz openssh-server \
      vim nano python3-dev python3-pip gdb g++ build-essential p7zip-full bsdmainutils \
      && apt-get autoclean
      RUN python3 -m pip install --upgrade pip -i https://pypi.tuna.tsinghua.edu.cn/simple \
      && python3 -m pip install setuptools --upgrade -i https://pypi.tuna.tsinghua.edu.cn/simple \
      && python3 -m pip install setuptools_rust --upgrade -i https://pypi.tuna.tsinghua.edu.cn/simple \
      && python3 -m pip install dfss --upgrade -i https://pypi.tuna.tsinghua.edu.cn/simple

      # set work dir
      WORKDIR /workspace

      # download build files
      RUN mkdir /env && pushd /env/ \
      && python3 -m dfss --url=open@sophgo.com:/sophon-bsp/BSP_SDK.zip \
      && 7z x BSP_SDK.zip \
      && mv 'BSP SDK'/* ./ \
      && rm -rf 'BSP SDK' \
      && rm -rf BSP_SDK.zip \
      && rm -rf memory_layout_modification_tool \
      && tar -xaf gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu.tar.xz \
      && mkdir qt_fl2000 && pushd qt_fl2000 \
      && python3 -m dfss --dflag=sophgo-bsp-qt5-fl2000fb-toolchain \
      && tar -xaf qt-5.14-amd64-aarch64-fl2000fb_v1.1.0.tar.xz \
      && popd \
      && mkdir qt_ms9132 && pushd qt_ms9132 \
      && python3 -m dfss --dflag=sophgo-bsp-qt5-ms9132-toolchain \
      && tar -xaf qt-5.14-amd64-aarch64-ms9132_v1.1.0.tar.xz \
      && popd \
      && popd

      RUN ulimit -n 1024

      # add path
      ENV PATH "$PATH:/env/gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu/bin"

      # Set the locale
      RUN locale-gen en_US.UTF-8
      ENV LANG en_US.UTF-8
      ENV LANGUAGE en_US:en
      ENV LC_ALL en_US.UTF-8

2. 使用如下命令生成编译用的docker镜像和进入容器

   .. code-block:: bash

      docker build -t sophon_bsp_build:v1 .

      docker run \
      -td \
      --privileged=true \
      -v /workspace:/workspace \
      --name sophon_bsp_container sophon_bsp_build:v1 /bin/bash

      docker exec -it sophon_bsp_container bash

7.2.5. docekr镜像使用
~~~~~~~~~~~~~~~~~~~~~~~~~~

1. 导出、导入镜像相关命令

   .. code-block:: bash

      docker save sophon_bsp_build:v1 | pv | gzip > sophon_bsp_build-v1.tar.gz
      docker load -i sophon_bsp_build-v1.tar.gz

2. 该docker镜像的使用注意事项:

   1. 需要amd64架构的宿主机
   2. docker中的系统是Ubuntu20.04
   3. docker中的交叉编译工具链是gcc-linaro-6.3.1-2017.05-x86_64_aarch64-linux-gnu，在/env/下，环境变量已经配置完毕
   4. docker中的定制化qt交叉编译工具链是qmake，在/env/qt_fl2000/install下，环境变量已经配置完毕
   5. docker中/env下有交叉编译工具链和ubuntu底包
   6. docker中安装了dfss文件下载工具

7.2.6. 默认参数编译一个刷机包（SE5&7）
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

1. 执行 `build_bsp_without_package` 命令编译fip、uboot、kernel以及一些相关deb包，并且准备好打包刷机包的环境
2. 拷贝 `sophon-soc-libsophon*.deb` 、 `sophon-mw-soc-sophon-ffmpeg*.deb` 和 `sophon-mw-soc-sophon-opencv*.deb` 这些中间件包到 `install/soc_bm1684/bsp-debs` 下

   1. `sophon-soc-libsophon*.deb` 是算法推理驱动和runtime包，需要编译kernel生成的header文件+libsophon源码进行编译出包
   2. `sophon-mw-soc-sophon-ffmpeg*.deb` 和 `sophon-mw-soc-sophon-opencv*.deb` 是多媒体相关的runtime包，由于只依赖系统，所以可以选择与SophonSDK版本对应的版本，无需重新编译。可以从SophonSDK包中image下bsp-debs下获取

3. 执行 `build_package` 命令打包刷机包，执行成功后会在 `install/soc_bm1684/bsp-debs` 下生成sdcard目录和tftp目录，对应sd卡刷机包和tftp刷机包

7.2.7. 编译流程解析
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

   .. image:: ./_static/image97.png
      :width: 8in
      :height: 3in

如上图，是刷机包编译流程的图形化说明，整体流程如下：

1. 编译uboot
2. 编译tfa
3. 编译spi_flash生成工具
4. 使用uboot固件和tfa固件生成flash固件
5. 编译kernel
6. 编译ramdisk

   1. 编译emmc启动ramdisk
   2. 编译恢复模式remdisk

7. 生成emmc上boot分区内容
8. 编译相关deb包
9. 生成根文件系统（使用qemu）
10. 生成其他分区压缩包
11. 生成sd卡刷机包
12. 生成tgz升级补丁包
13. 生成tftp刷机包

7.2.8. 源码修改说明
~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

7.2.8.1. 修改kernel
:::::::::::::::::::::::::::::::::::::::::::::

kernel的配置文件在：

   linux-arm64/arch/arm64/configs/bitmain_bm1684_normal_defconfig

请注意修改kernel
config可能会造成您的kernel与我们通过二进制发布的驱动文件（板上/opt/sophon/libsophon-current/data/下的bmtpu.ko、vpu.ko、jpu.ko）无法兼容。

标准版 |Product| 使用的设备树文件在：

   linux-arm64/arch/arm64/boot/dts/bitmain/bm1684x_evb_v0.0.dts

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
   即可知道这块板子对应的device tree源文件是在linux-arm64/arch/arm64/boot/dts/bitmain/目录下的**bm1684x_evb_v0.0.dts**。

7.2.8.2. 修改Ubuntu 20.04
:::::::::::::::::::::::::::::::::::::::::::::

方式一：利用Ubuntu系统源码包进行修改

Ubuntu 20.04系统的生成过程是这样：

1. distro/distro_focal.tgz是Ubuntu官方纯净版底包。

2. bootloader-arm64/distro/overlay下包含了 |Product| 对底包的修改，会覆盖到底包的同名路径。

3. kernel编译的过程中也会把ko等文件更新进去。

4. 如果install/soc_bm1684目录下有system.tgz文件，则刷机包生成过程中会把它作为/system目录下的内容。

5. install/soc_bm1684目录下有data.tgz文件，则刷机包生成过程中会把它作为/data目录下的内容。

所以您可以在overlay/bm1684加入您自己的改动，比如放入一些工具软件，修改以太网配置文件等等，然后重新生成刷机包。

如果您有一个或多个deb想要预装到Ubuntu 20.04，那么有两种做法：

a. 如果deb包比较简单，您可以直接将它解压缩后把里面的文件copy到bootloader-arm64/distro/overlay/bm1684/rootfs下的对应目录。

b. 将deb包直接放到bootloader-arm64/distro/sophgo-fs/root/post_install/debs目录，则 |Product| 在刷机后第一次开机时会把这些deb包都安装上。

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


7.2.8.3. 定制化软件包
:::::::::::::::::::::::::::::::::::::::::::::

您可以通过以下操作获取您所需要的特定的软件包:

1. 从官网获取sdcard.tgz基础软件包。

2. 您需要参考文件结构一节准备相关文件，将sdcard.tgz软件包复制到install/soc_bm1684目录下，如果没有该目录，可以先执行以下命令

   .. code-block:: bash

      mkdir -p install/soc_bm1684
      cp -rf {your_path}/sdcard.tgz install/soc_bm1684/  // {your_path}是您获取的sdcard.tgz基础软件包的本地路径

      source bootloader-arm64/scripts/envsetup.sh
      revert_package


3. 执行完命令之后会在install/soc_bm1684/下生成boot.tgz，data.tgz，opt.tgz，recovery.tgz，rootfs.tgz，rootfs_rw.tgz六个软件包，并且在install/soc_bm1684/package_update/目录下生成sdcard和update两个文件夹，这里的sdcard文件夹是sdcard.tgz软件包解压出来的文件，update文件夹保存了执行revert_package命令之后初始打包的六个软件包。

   boot.tgz软件包主要用于kernel。

   data.tgz软件包主要用于data分区。

   opt.tgz软件包包括运行时的lib库。

   recovery.tgz软件包主要用于用户恢复出厂设置。

   rootfs.tgz软件包可以用来制作您所需要的文件系统，参照修改Ubuntu 20.04 一节中的利用qemu虚拟机方式进行修改部分的环境准备第4步及其之后的操作更新rootfs.tgz包，注意使用的rootfs.tgz原始包是install/soc_bm1684/下的rootfs.tgz。

   rootfs_rw.tgz软件包文件系统overlay区，包括了所有系统安装的 app，lib，脚本，服务，/etc下的设置， 更新后都会清除。

4. 如果您要修改分区信息，您需要修改bootloader-arm64/scripts/下的partition32G.xml文件。

5. 将修改后的*.tgz包替换掉install/soc_bm1684/下的同名*.tgz包，然后根据需要重新编译刷机包。

   .. code-block:: bash

      build_update sdcard  // 重新编译sdcard刷机包
      build_update tftp    // 重新编译tftp刷机包

7.2.8.4. 修改分区表
:::::::::::::::::::::::::::::::::::::::::::::

|Product| 使用GPT分区表。分区表的配置文件在bootloader-arm64/scripts/partition32G.xml，其中依次描述了每个分区的大小信息。

不建议您修改分区的顺序和个数，以及readonly和format属性，以免与其它一些预装脚本中的写法发生冲突。

您可以修改每个分区的大小。最后一个分区的大小不需要凑满eMMC实际容量，可以把它设成一个比较小的值，只要足够存放您准备预装的文件（即data.tgz解开后的内容）就可以。

刷机后第一次开机时，会有一个脚本将这个分区自动扩大到填满eMMC的全部剩余可用空间。

内容解析如下：

   .. code-block:: xml

      <physical_partition size_in_kb="20971520">
            <partition label="BOOT"       size_in_kb="131072"  readonly="false"  format="1" />
            <partition label="RECOVERY"   size_in_kb="3145728"  readonly="false" format="2" />
            <partition label="MISC"       size_in_kb="10240"  readonly="false"   format="0" />
            <partition label="ROOTFS"     size_in_kb="2621440" readonly="true"   format="2" />
            <partition label="ROOTFS_RW"  size_in_kb="6291456" readonly="false"  format="2" />
            <partition label="OPT"        size_in_kb="2097152" readonly="false"  format="2" />
            <partition label="DATA"       size_in_kb="4194304" readonly="false"  format="2" />
      </physical_partition>

1. 其中第一行代表总分区表大小，对于32GB emmc设备，推荐最大30000000，对于64GB emmc设备，推荐最大55000000。

2. 然后修改下面的各个分区大小到需求大小

3. 注： 不要轻易将某一个分区大小缩小，可能会导致某个分区打刷机包时出现问题


7.2.8.5. 修改u-boot
:::::::::::::::::::::::::::::::::::::::::::::

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

7.3. 在 |Product| 上编译内核模块
------------------------------------

您也可以选择直接在 |Product| 板卡上直接编译kernel
module，可以省去上述搭建交叉编译环境的麻烦。步骤如下：

1. uname
   -r得到kernel版本号，与/home/linaro/bsp-debs和/lib/modules里面的文件名比较，确保一致

2. 因为kernel在交叉编译环境下做make
   bindeb-pkg的缺陷，需要再额外做如下处理：

   a. 用date命令检查当前系统时间，如果跟实际时间相差太多，请设置为当前时间，如

      .. code-block:: bash

         sudo date -s "01:01:01 2021-03-01"

   b. 检查是否存在/home/linaro/bsp-debs/install.sh，如果有的话，执行它即可

   c. 如果没有的话，需要手工操作：

      .. code-block:: bash

         sudo dpkg -i /home/linaro/bsp-debs/linux-headers-*.deb
         sudo mkdir -p /usr/src/linux-headers-$(uname -r)/tools/include/tools
         sudo cp /home/linaro/linux-dev/*.h /usr/src/linux-headers-$(uname-r)/tools/include/tools
         cd /usr/src/linux-headers-$(uname -r)
         sudo apt update
         sudo apt-get install -y build-essential bc bison flex libssl-dev
         sudo make scripts

3. 回到您的driver目录，make ko吧

7.4. 1684x kdump-crash使用说明
----------------------------------

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

7.5. 开机自启动服务
-----------------------------

本段说明如何使用systemd在SOC模式下配置一个最简单的开机自启动服务用于算法业务：

1. 新建文件/etc/systemd/system/user-auto-start.service，内容如下：

   .. code-block:: bash

      [Unit]
      Description=user auto setup
      After=network.target bmrt_setup.service # 表明该服务在网络启动后，并且bmrt_setup服务结束后启动

      [Service]
      User=root
      ExecStart=/data/user_auto_setup.sh # 指定服务启动执行的命令
      Type=simple # 服务类型是最简单的前台模式
      Restart=on-failure # 只有错误退出才会重启
      RestartSec=10 # 重启服务会等待10s

      [Install]
      WantedBy=multi-user.target

   配置文件内容解析：

   1. 描述：user auto setup
   2. 启动时间：在network.target和bmrt_setup.service之后，在multi-user.target之前
   3. 命令执行账户：root
   4. 命令：/data/user_auto_setup.sh
   5. 服务类型：simple
   6. 是否自动重启：是，仅在命令执行失败10s后重启

2. 配置执行脚本（本文为/data/user_auto_setup.sh），切记需要赋予其运行权限
3. 执行命令sudo systemctl daemon-reload​​​​重载配置文件
4. 执行命令sudo systemctl status user-auto-start.service​​​​查看该服务是否配置完成
5. 执行命令sudo systemctl enable user-auto-start.service​​​​使能其开机自启

注意事项：

1. 默认运行的log会存放在/var/log/syslog文件中
2. 该示例只适用于简单的业务，复杂的环境配置等需要参考systemd的说明文档
3. 该示例的服务类型是simple，切记不要在脚本中使其自动放置后台执行，这会导致systemd无法监控前台任务导致直接杀死进程
4. 可以使用命令sudo systemd-analyze plot > plot.svg​​生成本次启动的服务清单（svg格式）用于分析服务的启动时间和运行时间
