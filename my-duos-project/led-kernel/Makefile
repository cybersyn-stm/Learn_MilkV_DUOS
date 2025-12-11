# Makefile
export ARCH=riscv
export CROSS_COMPILE=/home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-
obj-m +=led_kernel.o
kdir=/home/cybersyn/duo-buildroot-sdk-v2/linux_5.10
all:
	make -C $(kdir) M=$(shell pwd) modules

clean:
	rm -rf *.o *.ko
