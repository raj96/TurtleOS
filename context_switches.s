.global store_context
.global load_context

.equ KTASK_RUNNING,     1
.equ KTASK_COMPLETED,   3

.section .text

# void store_context(ktask_node *ktask)
store_context:
    # don't store if ktask is NULL
    beq a0, zero, ret_from_store_context
    
    # don't store if ktask is completed
    ld t0, 256(a0)
    li t1, KTASK_COMPLETED
    beq t0, t1, ret_from_store_context
    
    add t0, zero, a0

    sd x1, 8(t0)
    sd x2, 16(t0)
    # sd x3, 24(a0)
    # sd x4, 32(a0)
    # sd x5, 40(a0)
    # sd x6, 48(a0)
    sd x7, 56(t0)
    sd x8, 64(t0)
    sd x9, 72(t0)
    sd x10, 80(t0)
    sd x11, 88(t0)
    sd x12, 96(t0)
    sd x13, 104(t0)
    sd x14, 112(t0)
    sd x15, 120(t0)
    sd x16, 128(t0)
    sd x17, 136(t0)
    sd x18, 144(t0)
    sd x19, 152(t0)
    sd x20, 160(t0)
    sd x21, 168(t0)
    sd x22, 176(t0)
    sd x23, 184(t0)
    sd x24, 192(t0)
    sd x25, 200(t0)
    sd x26, 208(t0)
    sd x27, 216(t0)
    sd x28, 224(t0)
    sd x29, 232(t0)
    sd x30, 240(t0)
    sd x31, 248(t0)
ret_from_store_context:
    ret

#void load_context(ktask_node *task)
load_context:
    add t0, zero, a0

    li t1, KTASK_RUNNING
    sd t1, 256(t0)

    ld t1, 16(t0)
    beq t1, zero, load_without_sp
    add x2, zero, t1
    
load_without_sp:
    ld x1, 8(t0)    # ra
    # ld x3, 24(a1)
    # ld x4, 32(a1)
    # ld x5, 40(a1)
    # ld x6, 48(a1)
    ld x7, 56(t0)
    ld x8, 64(t0)
    ld x9, 72(t0)
    ld x10, 80(t0)
    ld x11, 88(t0)
    ld x12, 96(t0)
    ld x13, 104(t0)
    ld x14, 112(t0)
    ld x15, 120(t0)
    ld x16, 128(t0)
    ld x17, 136(t0)
    ld x18, 144(t0)
    ld x19, 152(t0)
    ld x20, 160(t0)
    ld x21, 168(t0)
    ld x22, 176(t0)
    ld x23, 184(t0)
    ld x24, 192(t0)
    ld x25, 200(t0)
    ld x26, 208(t0)
    ld x27, 216(t0)
    ld x28, 224(t0)
    ld x29, 232(t0)
    ld x30, 240(t0)
    ld x31, 248(t0)

    jalr ra

    li t1, KTASK_COMPLETED
    sd t1, 256(t0)

    wfi
