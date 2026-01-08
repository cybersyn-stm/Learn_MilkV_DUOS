export ARCH = riscv
export CROSS_COMPILE = /home/cybersyn/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-
KDIR := /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10/build/sg2000_milkv_duos_musl_riscv64_sd

obj-m += src/ssd1306.o
#--------------------------------------------------------------------
# 仅在需要时（例如用 Bear 生成 compile_commands.json）清理不需要的 flags
# 使用方法：
#   DISABLE_SPECIAL_FLAGS=1 bear -- make
# 平时直接 make 不受影响。
#--------------------------------------------------------------------
# 清掉 CFLAGS / KBUILD_CFLAGS / KBUILD_USERCFLAGS 中的这几个选项
CFLAGS           := $(filter-out -mno-ldd -fno-allow-store-data-races -fconserve-stack,$(CFLAGS))
KBUILD_CFLAGS    := $(filter-out -mno-ldd -fno-allow-store-data-races -fconserve-stack,$(KBUILD_CFLAGS))
KBUILD_USERCFLAGS:= $(filter-out -mno-ldd -fno-allow-store-data-races -fconserve-stack,$(KBUILD_USERCFLAGS))
export CFLAGS KBUILD_CFLAGS KBUILD_USERCFLAGS
all :
	@echo "Building ssd1306 module..."
	@$(MAKE) -C $(KDIR) M=$(PWD) modules
	@echo "Copy to..."
	@cp src/ssd1306.ko ./
	@cp src/ssd1306.c ./
	@rm Module.symvers
	@rm modules.order
	@scp src/ssd1306.ko root@192.168.42.1:/root/

clean :
	@echo "Cleaning up..."
	@rm -f *.ko
	@rm -f *.c
	@rm -f src/*.mod.c src/*.o src/*.ko src/*mod
	@rm -f Module.symvers
	@rm -f modules.order
