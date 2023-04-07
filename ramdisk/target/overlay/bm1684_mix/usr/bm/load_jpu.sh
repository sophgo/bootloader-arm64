#!/bin/sh
module="jpu"
device="jpu"
mode="664"

chmod 664 /dev/ion

jpu=`/sbin/lsmod | awk "\\$1==\"$module\" {print \\$1}"`
if [ "$jpu" != "$module" ]; then
  echo "insmod $module.ko"

  # invoke insmod with all arguments we got
  # and use a pathname, as newer modutils don't look in . by default
  /sbin/insmod $module.ko $* || exit -1
  mdev -s

  chmod $mode  /dev/${device}
  chown root /dev/${device}
else
  echo "$module.ko already installed"
fi
