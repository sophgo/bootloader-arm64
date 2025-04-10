#!/bin/bash

sudo busybox watchdog -t 3 -T 5 /dev/watchdog0
sudo kill -9 $(ps -ef|grep watchdog0|gawk '$0 !~/grep/ {print $2}' |tr -s '\n' )

