# User-mode Makefile (cross compile + bear/clangd friendly)

CC := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc
SYSROOT := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/sysroot

APP  ?= ssd1306_misc_user

SRCS := ./src/ssd1306_misc_user.c ./src/ssd1306_8x16.c
OBJS := $(SRCS:.c=.o)

COMMON := --sysroot=$(SYSROOT)

CPPFLAGS ?=
CPPFLAGS += -I./include/               # so "ssd1306_8x16.h" can be found

CFLAGS  ?= -O2 -Wall -Wextra $(COMMON)
LDFLAGS ?= $(COMMON)
LDLIBS  ?=

all: $(APP)
	scp ssd1306_misc_user root@192.168.42.1:/root/

$(APP): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CPPFLAGS) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(APP) $(OBJS)
