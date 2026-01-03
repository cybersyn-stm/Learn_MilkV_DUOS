CC := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc
CFLAGS := -I/home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/build/sg2000_milkv_duos_musl_riscv64_sd/

TARGET := ssd1306_demo
SRCS := ssd1306.c

all : $(TARGET)
	scp $(TARGET) root@192.168.42.1:/root/

$(TARGET) : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^

clean :
	rm -f $(TARGET)
