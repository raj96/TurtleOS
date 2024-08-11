# TurtleOS

# Intent
Learn about OS development and RISC-V architecture

# Drivers implemented
* UART  [ns16550a]
* RTC   [goldfish-rtc]

# Code Structure
* Machine mode code in entry.s and kernel.c
* Supervisor mode entry point in kmain.c (kmain())
* Low-level drivers under directory `drivers` [under directiry include and lib]
* Utility function that interract with drivers under directory `kutils` [under directiry include and lib]

# If you want to try it out
* Install the following
    * QEMU (riscv)
    * GCC Toolchain for riscv
    * Make
* Run `make` in the root of the project
