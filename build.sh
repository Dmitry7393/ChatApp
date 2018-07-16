#!/bin/bash

set -eux
ROOTDIR=/app/ChatApp/

echo "Build Server"
cd $ROOTDIR/server
mkdir build
cd build
cmake ../. 
make
cp Server $ROOTDIR

echo "Build Client"
cd $ROOTDIR/client
mkdir build
cd build
cmake ../. 
make
cp ChatApp $ROOTDIR

