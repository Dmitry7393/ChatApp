#!/bin/bash

set -eux

echo "Install gtest"
apt-get install -y libgtest-dev
cd /usr/src/gtest
cmake CMakeLists.txt
make
cp *.a /usr/lib
