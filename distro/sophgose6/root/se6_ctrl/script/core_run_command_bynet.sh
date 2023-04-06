#!/bin/bash



if [ $# -lt 3  ] ; then
    echo "-------------------------------------------------------------------- "
    echo "this script used by run command for all cores or one core"
    echo "run for all cores"
    echo "      eg: ./core_run_command_bynet.sh bm_version linaro linaro"
    echo "-------------------------------------------------------------------- "
    echo "run for one core"
    echo "      eg: ./core_run_command_bynet.sh bm_version linaro linaro 5"

    exit -1
fi

pushd $(dirname $(realpath $0))


lan1ip=$(ifconfig eth0 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d.\n", $1,$2,$3)}' )
lan2ip=$(ifconfig eth1 | grep "inet "|awk '{print $2}'|awk -F . '{printf("%d.%d.%d.\n", $1,$2,$3)}' )

if [ "$4" = "" ]; then
        echo "do all"
        for ((i=1; i<=6; i++))
        do
                ./ssh_anycmd.exp "${lan1ip}1${i}" $2 $3 "$1"
				echo "run command finish"
        done
        for ((i=1; i<=6; i++))
        do
                ./ssh_anycmd.exp "${lan2ip}1${i}" $2 $3 "$1"
				echo "run command finish"
        done
else
        echo "do $4"
        if [ $4 -gt 12 ];then
                echo "input id is more than max id"
        elif [ $4 -gt  6 ];then
                id=$(expr $4 \- 6)
                ./ssh_anycmd.exp "${lan2ip}1${id}" $2 $3 "$1"
        else
                id=$4
                ./ssh_anycmd.exp "${lan1ip}1${id}" $2 $3 "$1"
        fi
		echo "run command finish"
fi
popd
echo "run all command finish"
