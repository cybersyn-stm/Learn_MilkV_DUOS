# 极简 Makefile：只编译 tm1650_demo.c

TARGET  = tm1650_demo
SRCS    = tm1650_demo.c

# 默认编译器，用你自己的交叉链覆盖
CC =/home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc

# 你可以在命令行覆盖 CFLAGS / LDFLAGS / LIBS
CFLAGS  = -I/home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/build/sg2000_milkv_duos_musl_riscv64_sd/
LDFLAGS =
LIBS    =

all: $(TARGET)
	scp $(TARGET) root@192.168.42.1:/root/

$(TARGET): $(SRCS)
	$(CC) $(CFLAGS) $(LDFLAGS) -o $@ $^ $(LIBS)

clean:
	rm -f $(TARGET)

send: 
	scp $(TARGET) root@192.168.42.1:/root/
