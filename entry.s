.global _entry
.equ STACK_SIZE, 8192

.section .entry
_entry:
    la sp, stack_top
    
    csrr t0, mhartid
    addi t0, t0, 1
    li t1, STACK_SIZE
    mul t0, t0, t1

    add sp, sp, t0

    j kentry
    li a0, 0xf411

    j .
