# Makefile


RESET :=\033[0m
BLUE := \033[36m

SRC_DIR := src
OBJ_DIR := obj

SRC := $(shell find src -name led.1.c)
OBJ := $(patsubst $(SRC_DIR)/%.c,$(OBJ_DIR)/%.o,$(SRC))

TARGET := led

cc=/home/cybersyn/duos/duo-examples/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc
var=led.o


$(TARGET) : $(OBJ) #目标led执行文件依赖于OBJ的字符串内容 
	@echo -n "Linking: $(OBJ)\n"
	@$(cc) $^ -o $@ 
	@echo -n "Build complete: $(BLUE)$@$(RESET)\n"
	
$(OBJ) : $(SRC) #目标文件依赖于源文件
	@mkdir -p $(dir $@)
	@$(cc) -c $< -o $@

compile : $(OBJ)
	@echo -n "Compilation complete: $(TARGET).o$(RESET)\n"

send : $(TARGET)
	@echo -n "Send to duos\n"
	scp led root@192.168.42.1:/root/

clean :
	@echo -n "Cleaning project...\n"
	@rm -rf $(OBJ_DIR)
	@rm -f $(TARGET)

debug : 
	@echo $(OBJ)
	@echo $(SRC)

.PHONY : debug debug clean compile
