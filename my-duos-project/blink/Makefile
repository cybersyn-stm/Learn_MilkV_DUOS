TARGET=blink

CC = /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc
CFLAGS = -I/home/cybersyn/duos/duo-examples/include/system\
		 -I/home/cybersyn/host-tools/gcc/riscv64-linux-x86_64/sysroot/usr/include

LDFLAGS = -L/home/cybersyn/duos/duo-examples/libs/system/musl_riscv64 -lwiringx

SOURCE = $(shell find -name *.c)
OBJS = $(patsubst %.c,%.o,$(SOURCE))

$(TARGET): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $(OBJS) $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -o $@ -c $<

.PHONY: clean debug
clean:
	@rm *.o -rf
	@rm $(OBJS) -rf
	@rm $(TARGET)
debug:
	@echo $(OBJS)
	@echo $(SOURCE)
	@echo $(LDFLAGS)
	@echo $(CC)
	@echo $(CFLAGS)
