#include "csr_op.h"
#include "drivers/syscon.h"
void kmain();

void kentry() {
    // Set mstatus to drop to supervisor mode when mret is issued and enable supervisor mode interrupts
    mstatus_write(mstatus_read() | MSTATUS_MIE | MSTATUS_SIE | MSTATUS_MPIE | MSTATUS_MPP_S);

    // Enable timer interrupt in machine mode
    mie_write(mie_read() | MIE_MTIE | MIE_STIE);

    // Enable interrupts in supervisor mode
    sstatus_write(sstatus_read() | SSTATUS_SIE);

    // Enable timer interrupt in supervisor mode
    sie_write(sie_read() | SIE_STIE);

    // Delegate all interrupts to supervisor mode
    mideleg_write(0xffff);
    medeleg_write(0xffff);

    // Enable interrupts in supervisor mode
    sie_write(sie_read() | SIE_STIE | SIE_SSIE | SIE_SEIE);

    // Set tp to mhartid
    asm volatile("csrr tp, mhartid");

    // Set trap to kernel main
    CSRW_OP("mepc", (uint64_t)kmain);

    // Disable paging
    CSRW_OP("satp", 0);

    CSRW_OP("pmpaddr0", 0x3fffffffffffffull);
    CSRW_OP("pmpcfg0", 0xf);

    // Start kernel
    asm volatile("mret");
    // while(1);
}