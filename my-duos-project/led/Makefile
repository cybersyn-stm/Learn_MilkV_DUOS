# Makefile




cc=/home/cybersyn/duos/duo-examples/host-tools/gcc/riscv64-linux-musl-x86_64/bin/riscv64-unknown-linux-musl-gcc
var=led.o

led:$(var)
	$(cc) $^ -o led 
%.o: %.c
	$(cc) -c $< -o $@
clean:
	rm -rf *.o
