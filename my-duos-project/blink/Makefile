# Minimal reusable Makefile (cross compile + clangd friendly)
# Usage:
#   make
#   bear -- make
#   make clean

CC := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc
SYSROOT := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/sysroot

APP  ?= blink
SRCS ?= blink.c
OBJS := $(SRCS:.c=.o)

# Keep these flags so bear/clangd learns the target + sysroot.
COMMON := --sysroot=$(SYSROOT) 

CFLAGS  ?= -O2 -Wall $(COMMON)
CFLAGS 	+= -I/home/cybersyn/duos/wiringX/src/
LDFLAGS ?= $(COMMON)
LDLIBS  ?= -L/home/cybersyn/duos/duo-examples/libs/system/musl_riscv64 -lwiringx

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(APP) $(OBJS)
