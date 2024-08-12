TOOLCHAIN=riscv64-unknown-elf-
IFLAGS=-I./include
CFLAGS=-mcmodel=medany -c -ffreestanding -O3

SRC=$(shell find . -name '*.c')	

run: build
	qemu-system-riscv64 -machine virt,aclint=on -m 4G -smp 1 -bios none -kernel kernel.elf

build: clean
	$(TOOLCHAIN)as entry.s -o entry.o
	$(TOOLCHAIN)gcc $(IFLAGS) $(CFLAGS) $(SRC)
	$(TOOLCHAIN)ld -T link.ld *.o -o kernel.elf
	$(MAKE) clean-dist

build-dist: build
	$(TOOLCHAIN)strip kernel.elf

clean:
	rm -f *.o
	rm -f kernel.elf

clean-dist:
	rm -f *.o