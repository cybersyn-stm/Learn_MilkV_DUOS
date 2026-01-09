# Minimal reusable Makefile (cross compile + clangd friendly)
# Usage:
#   make
#   bear -- make
#   make clean

CC := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc
SYSROOT := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/sysroot

APP  ?= ssd1306_misc_user
SRCS ?= ssd1306_misc_user.c
OBJS := $(SRCS:.c=.o)

# Keep these flags so bear/clangd learns the target + sysroot.
COMMON := --sysroot=$(SYSROOT)

CFLAGS  ?= -O2 -Wall $(COMMON)
LDFLAGS ?= $(COMMON)
LDLIBS  ?=

all: $(APP)

$(APP): $(OBJS)
	$(CC) $(LDFLAGS) -o $@ $^ $(LDLIBS)

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

clean:
	rm -f $(APP) $(OBJS)
