# 编译器配置
export ARCH=riscv
export CROSS_COMPILE=/home/cybersyn/duos/duo-buildroot-sdk-v2/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-

# 模块名称
obj-m := platform_led.o

# 目录设置
SRC_DIR := src
OBJ_DIR := obj

# 内核源码目录
kdir := /home/cybersyn/duos/duo-buildroot-sdk-v2/linux_5.10

# 启用详细输出（这有助于bear捕获命令）
V ?= 0
ifeq ($(V),1)
    Q =
    quiet =
else
    Q = @
    quiet = quiet_
endif

.PHONY: all clean bear-all

# 默认目标
all: prepare-src
	$(Q)echo "正在构建内核模块..."
	$(Q)$(MAKE) -C $(kdir) M=$(shell pwd) modules
	$(Q)# 移动中间文件
	$(Q)mv -f *.o *.mod.c *.mod *.order *.symvers .*.cmd .tmp_versions $(OBJ_DIR)/ 2>/dev/null || true
	$(Q)if [ -f $(OBJ_DIR)/platform_led.ko ]; then mv -f $(OBJ_DIR)/platform_led.ko ./; fi
	$(Q)echo "构建完成！"

# 用于bear的目标（强制详细输出）
bear-all:
	@echo "使用bear记录编译命令..."
	@$(MAKE) V=1 prepare-src
	@bear --output compile_commands.json -- $(MAKE) -C $(kdir) M=$(shell pwd) V=1 modules
	@# 移动中间文件
	@mv -f *.o *.mod.c *.mod *.order *.symvers .*.cmd .tmp_versions $(OBJ_DIR)/ 2>/dev/null || true
	@if [ -f $(OBJ_DIR)/platform_led.ko ]; then mv -f $(OBJ_DIR)/platform_led.ko ./; fi
	@echo "编译数据库生成完成: compile_commands.json"

# 准备源文件
prepare-src:
	@mkdir -p $(OBJ_DIR)
	@if [ -f $(SRC_DIR)/platform_led.c ]; then \
		cp -f $(SRC_DIR)/platform_led.c ./; \
	fi

# 清理
send: 
	@echo "正在发送 platform_led.ko 到目标设备..."
	@scp platform_led.ko root@192.168.42.1:/root/
# 清理 - 完全控制清理过程
clean:
	@echo "开始清理..."
	
	@# 清理构建产物
	@rm -rf $(OBJ_DIR)
	@rm -f platform_led.c platform_led.ko
	
	@# 只清理内核构建相关的特定文件
	@rm -f .platform_led*.cmd platform_led.mod.c modules.order Module.symvers 2>/dev/null || true
	@rm -rf .tmp_versions 2>/dev/null || true
	
	@echo "清理完成！（保留 compile_commands.json）"

# 完整清理（包括JSON文件）
distclean: clean
	@rm -f compile_commands.json compile_commands.json.backup
	@echo "完全清理完成！"
