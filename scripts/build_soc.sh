#!/bin/bash -x

header_deb=$(ls /linux-header*.deb)
echo "install linux headers : $headers_deb"
dpkg -i ${header_deb}

headers=$(echo ${header_deb} | awk -F .deb '{print $1}')

echo "headers path is $headers"

echo "build headers"
cd /usr/src/${headers}/

rm scripts/mod/modpost
make prepare0
make scripts

echo "build soc start"

cd /libsophon/

#rm -rf build

mkdir build
cd build

cmake -DPLATFORM=soc -DSOC_LINUX_DIR=/usr/src/${headers}/  -DCMAKE_INSTALL_PREFIX=/libsophon/install ..
make
make driver
make vpu_driver
make jpu_driver
make package
