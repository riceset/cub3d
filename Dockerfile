FROM ubuntu:latest

RUN apt-get update
RUN apt-get install -y \
build-essential \
gdb \
valgrind \
vim

WORKDIR /usr/src/cub3d

COPY . /usr/src/cub3d

RUN make
