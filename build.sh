#!/bin/bash

set -eux
ROOTDIR=/app/ChatApp/

cd $ROOTDIR
./install_gtest.sh

echo "Build Server"
cd $ROOTDIR/server
mkdir build
cd build
cmake ../. 
make

echo "Copy Server binary to root folder "
cd $ROOTDIR/server/build/ChatAppServer
cp Server $ROOTDIR

echo "Run unit tests"
cd $ROOTDIR/server/build/UnitTests
./UnitTests

echo "Build Client"
cd $ROOTDIR/client
mkdir build
cd build
cmake ../. 
make
cp ChatApp $ROOTDIR

