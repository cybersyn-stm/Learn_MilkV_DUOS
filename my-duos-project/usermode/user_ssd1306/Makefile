CC := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc
SYSROOT := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/sysroot

CFLAGS := -O2 -Wall --sysroot=$(SYSROOT) -march=rv64gcxthead -mabi=lp64d

all:
	$(CC) $(CFLAGS) -o ssd1306_misc_user ssd1306_misc_user.c
