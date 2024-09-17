TOOLCHAIN=riscv64-unknown-elf-
IFLAGS=-I./include
CFLAGS=-mcmodel=medany -c -ffreestanding -O3

ASRC=$(shell find . -name '*.s')
CSRC=$(shell find . -name '*.c')	

run: build
	qemu-system-riscv64 -machine virt -m 128M -smp 1 -bios none -kernel kernel.elf

build: clean
	$(TOOLCHAIN)as $(ASRC) -o assembly_routines.o
	$(TOOLCHAIN)gcc $(IFLAGS) $(CFLAGS) $(CSRC)
	$(TOOLCHAIN)ld -T link.ld *.o -o kernel.elf
	$(MAKE) clean-dist

build-dist: build
	$(TOOLCHAIN)strip kernel.elf

clean:
	rm -f *.o
	rm -f kernel.elf

clean-dist:
	rm -f *.o