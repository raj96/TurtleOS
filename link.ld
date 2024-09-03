OUTPUT_ARCH("riscv")
ENTRY(_entry)

SECTIONS {
    . = 0x80000000;
    PROVIDE(mem_start = .);

    .text : {
      *(.entry)
      *(.text .text.*)
    }

    .rodata : {
      . = ALIGN(16);
      *(.srodata .srodata.*) /* do not need to distinguish this from .rodata */
      . = ALIGN(16);
      *(.rodata .rodata.*)
    }

    .data : {
      . = ALIGN(16);
      *(.sdata .sdata.*) /* do not need to distinguish this from .data */
      . = ALIGN(16);
      *(.data .data.*)
    }

    .bss : {
      . = ALIGN(16);
      *(.sbss .sbss.*) /* do not need to distinguish this from .bss */
      . = ALIGN(16);
      *(.bss .bss.*)
    }

  PROVIDE(stack_top = .);
  . += (STACK_SIZE * NUM_CPU);          /* See entry.s for values */
  PROVIDE(stack_end = .);
}