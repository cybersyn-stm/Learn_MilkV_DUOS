CC := /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc
CFLAGS := -I/home/cybersyn/duo-buildroot-sdk-v2/linux_5.10/build/sg2000_milkv_duos_musl_riscv64_sd/

TARGET := vk36n16i_demo
SRCS := vk36n16i.c

$(TARGET) : $(SRCS)
	$(CC) $(CFLAGS) -o $@ $^ #gcc -I/path/to/headers -o vk36n16i vk36n16i.c 
	scp $(TARGET) root@192.168.42.1:/root/vk36n16i

clean :
	rm -f $(TARGET)
	
