# Makefile

export ARCH=riscv
export CROSS_COMPILE=/home/cybersyn/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-
obj-m +=helloworld.o
kdir=/home/cybersyn/duo-buildroot-sdk-v2/linux_5.10
pwd=$(shell pwd)
all:
	make -C $(kdir) M=$(pwd) modules
