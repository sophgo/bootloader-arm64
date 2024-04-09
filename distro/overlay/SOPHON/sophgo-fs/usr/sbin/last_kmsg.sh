#!/bin/bash

# clear old log

base=/var/log
prefix=last_kmsg_
suffix=\.tar\.gz
limit=9

function clean()
{
    list=`ls -v -r -w1 $base/${prefix}*${suffix} 2>/dev/null`
    total=`echo "$list" | wc -l`
    del=$((total - limit))

IFS=$'
'

    if [ $del -gt 0 ]; then
        dellist=`echo "$list" | head -n $del`
        set -f
        for file in $dellist; do
            rm -rf "$file"
        done
        set +f
    	index=$limit
    else
	index=$total
    fi
    list=`ls -v -r -w1 $base/${prefix}*${suffix} 2>/dev/null`
    for file in $list; do
        if [ "$file" != "$base/${prefix}$((index))${suffix}" ]; then
            mv $file $base/${prefix}$((index))${suffix}
        fi
        index=$((index - 1))
    done
}

# create a new one

if [ -d "/sys/fs/pstore" ]; then
    cd /sys/fs/pstore/
    fileNum=`ls -l |grep "^-"|wc -l`
    if [ "$fileNum" -gt "0" ]; then
        clean
        tar zcPf $base/${prefix}0${suffix} *
        rm -rf /sys/fs/pstore/*
    fi
fi
