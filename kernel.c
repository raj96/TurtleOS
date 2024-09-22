#include "csr_op.h"
#include "drivers/syscon.h"
#include "drivers/uart.h"
#include "kutils/console.h"
#include "drivers/clint.h"
#include "addr_op.h"

void kmain();
extern void store_context() __attribute__((aligned(4)));

void kentry() {
    // Set mstatus to drop to supervisor mode when mret is issued and enable supervisor mode interrupts
    uint64_t mstatus = mstatus_read();
    mstatus_write(mstatus | MSTATUS_MIE | MSTATUS_MPIE | (MSTATUS_MPP_S & ~MSTATUS_MPP_M));

    // Enable interrupts in machine mode
    uint16_t mie = mie_read();
    mie_write(mie | MIE_MTIE);

    // Delegate all interrupts to supervisor mode
    mideleg_write(0xffff);
    medeleg_write(0xffff);

    // Set trap to kernel main
    CSRW_OP("mepc", (uint64_t)kmain);

    // Disable paging
    CSRW_OP("satp", 0);

    CSRW_OP("pmpaddr0", 0x3fffffffffffffull);
    CSRW_OP("pmpcfg0", 0xf);

    CSRW_OP("mtvec", (uint64_t)store_context);

    ADDR_WRITE(CLINT_MTIMECMP, 5000000UL, uint64_t);

    // Start kernel
    asm volatile("mret");
    // while(1);
}