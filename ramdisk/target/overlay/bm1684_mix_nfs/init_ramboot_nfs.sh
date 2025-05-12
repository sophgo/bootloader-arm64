#!/bin/bash -x

# Copyright (c) 2015, ARM Limited and Contributors. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# Redistributions of source code must retain the above copyright notice, this
# list of conditions and the following disclaimer.
#
# Redistributions in binary form must reproduce the above copyright notice,
# this list of conditions and the following disclaimer in the documentation
# and/or other materials provided with the distribution.
#
# Neither the name of ARM nor the names of its contributors may be used
# to endorse or promote products derived from this software without specific
# prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

#Mount filesystems needed by mount and mdev
/bin/busybox mount -t proc proc /proc
/bin/busybox mount -t sysfs sysfs /sys
/bin/busybox mount -t debugfs none /sys/kernel/debug
echo "************init.sh"

#Create all the symlinks to /bin/busybox
/bin/busybox --install -s
chown root:root /bin/busybox
chown root:root /bin/su
chmod 4755 /bin/su

#Create things under /dev
mdev -s

#Redirect output
exec 0</dev/console
exec 1>/dev/console
exec 2>/dev/console

echo "insmod ko start ..." > /init.log
insmod /usr/bm/bmtpu.ko
cd /usr/bm
./load.sh
/bin/bash ./load_jpu.sh
cd /
echo "bmcpu start ..." > /init.log
/usr/bm/bmcpu &
echo "sleep start ..." >> /init.log
sleep 30
echo "mount start ..." >> /init.log
cardID_HEX=$(busybox devmem 0x101fb445 8)
cardID=$(printf "%d\n" $cardID_HEX)
echo "card id is ${cardID}"
serverIP1=$(printf "%d" $(busybox devmem 0x101fb447 8))
serverIP2=$(printf "%d" $(busybox devmem 0x101fb446 8))
serverIP3=$(printf "%d" $(busybox devmem 0x101fb445 8))
mount -t nfs -o vers=3,port=2049,proto=tcp,async,nolock,hard,rsize=131072,wsize=131072 \
${serverIP1}.${serverIP2}.${serverIP3}.3:/sophgo_mix_nfs/${cardID} /mnt
if [ $? -eq 0 ]; then
        if [ ! -f /mnt/init ]; then
                echo "/sbin/init start ..." >> /init.log
                exec /sbin/init $*
        fi
        exec switch_root /mnt /init
        if [ ! $? -eq 0 ]; then
                echo "/sbin/init start ..." >> /init.log
                exec /sbin/init $*
        fi
fi
printenv >> /init.log
ip a >> /init.log
ifconfig >> /init.log
route -n >> /init.log

echo "/sbin/init start ..." >> /init.log
exec /sbin/init $*
