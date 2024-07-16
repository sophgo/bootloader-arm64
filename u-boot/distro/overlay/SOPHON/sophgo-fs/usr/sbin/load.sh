#!/bin/bash

func(){
    echo "This is a scripts to modify permission of driver, "
    echo "parameters are as follows: "
    echo "  help: \t show help"
    echo "  -o: \t owner(default linaro.linaro)"
    echo "  -p: \t the absolute path of driver(default /dev/)"
    echo "  -d: \t driver name(such as cvi-vpss)"
    echo "  -r: \t mode,(default 664)"
    echo "Example1: ./load.sh help"
    echo "Example2: ./load.sh -o linaro.linaro -p /dev/ -m cvi-vpss -r 664"
    exit 1
}

if [ $# -eq 0 -o "$1" = "help" ]; then
    func
fi

owner=linaro.linaro
path=/dev/
device=
mode=664
while getopts "o:p:d:r" opt
do
    case $opt in
    o) owner=$OPTARG;;
    p) path=$OPTARG;;
    d) device=$OPTARG;;
    r) mode=$OPTARG;;
    ?) func;;
esac done
if [ "$device" = "" ]; then
    echo "Warning: Please input driver name using -d"
    exit 1
fi

mm=`sudo find $path -name $device | wc -l`
if [ "$mm" == 1 ]; then
    echo "modify permission"
    sudo chmod $mode ${path}/${device}
    sudo chown $owner ${path}/${device}
else
    echo "Warning: $path $driver not found"
fi

exit 0
