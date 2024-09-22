TOOLCHAIN=riscv64-unknown-elf-
IFLAGS=-I./include
CFLAGS=-mcmodel=medany -c -ffreestanding -O3

ASRC=$(shell find . -name '*.s')
CSRC=$(shell find . -name '*.c')

QEMU=qemu-system-riscv64 -m 128M -smp 1 -machine virt

run: build
	$(QEMU) -bios none -kernel kernel.elf

run-debug: build-debug
	$(QEMU) -bios none -kernel kernel.elf -s

build-debug: clean
	$(TOOLCHAIN)as $(IFLAGS) $(ASRC) -o assembly_routines.o
	$(TOOLCHAIN)gcc $(IFLAGS) $(CFLAGS) -g $(CSRC)
	$(TOOLCHAIN)ld -T link.ld *.o -o kernel.elf
	$(MAKE) clean-dist

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

dump-dtb:
	$(QEMU),dumpdtb=machine.dtb
	dtc -O dts -o machine.dts machine.dtb