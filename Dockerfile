FROM ubuntu:16.04
MAINTAINER buksha <dmitry7393@gmail.com>

RUN apt-get update
RUN apt-get install -y cmake libblkid-dev e2fslibs-dev libboost-all-dev libaudit-dev g++ pkg-config libjsoncpp-dev qt4-default
