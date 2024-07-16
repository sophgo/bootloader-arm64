#!/bin/bash

SECTOR_BYTES=512
CHUNK_SIZE=200704


function suser() {
	sudo -k || panic "failed to kill superuser privilege"
	sudo -v || panic "failed to get superuser privilege"

}

function revert_system() {
	local offset=0
	local name=$1
	local tmp_path="$1_tmp"
	local output_file=$name.ext4

	total=`echo $1.1-of-* | cut -d '-' -f 3 | cut -d '.' -f 1`
	echo "total: $total"

	for i in $(seq 1 $total)
	do
		file_tgz="$name.$i-of-$total.gz"
		if [ -f $file_tgz ];then
			gzip -d $file_tgz
		fi

		file="$name.$i-of-$total"
		size=$(du -b $file | awk '{print $1}')
		echo $size
		dd status=none if=$file of=$output_file bs=$SECTOR_BYTES seek=$offset count=$CHUNK_SIZE
		offset=$(expr $offset + $CHUNK_SIZE)
	done

	if [ -f $tmp_path ];then
		rm -rf $tmp_path
	fi
	mkdir $tmp_path
	sudo mount $output_file $tmp_path
	pushd $tmp_path
	sudo tar zcvSf ../$name.tgz *
	popd
	sudo sync
	sudo umount $tmp_path
    sleep 3
    sudo rm -rf $tmp_path
}

echo "Start"
if [ $# -lt 1   ] ; then
    echo "./revert_package.sh system"
    exit -1
fi
suser
for arg in $*
do
  echo "arg: $index = $arg"
  revert_system "$arg"

done
