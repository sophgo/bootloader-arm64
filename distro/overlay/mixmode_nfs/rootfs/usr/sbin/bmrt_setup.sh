#!/bin/bash

cardID_HEX=$(busybox devmem 0x101fb445 8)
cardID=$(printf "%d\n" $cardID_HEX)
echo "card id is ${cardID}"
serverIP1=$(printf "%d" $(busybox devmem 0x101fb447 8))
serverIP2=$(printf "%d" $(busybox devmem 0x101fb446 8))
serverIP3=$(printf "%d" $(busybox devmem 0x101fb445 8))
route add default gw ${serverIP1}.${serverIP2}.${serverIP3}.3
