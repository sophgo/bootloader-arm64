#!/bin/bash

sudo watchdog -t 3 -T 85 /dev/watchdog0
sudo kill -9 $(ps -ef|grep watchdog0|gawk '$0 !~/grep/ {print $2}' |tr -s '\n' )

