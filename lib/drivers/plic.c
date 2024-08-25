// Driver for plic-v1.0.0; specs followed: https://github.com/riscv/riscv-plic-spec/blob/master/riscv-plic.adoc
#include "drivers/plic.h"
#include "addr_op.h"
#include "kutils/console.h"

void plic_enable_intr(int source, int ctxt) {
    uint64_t address;
    address = PLIC_INTR_ENABLE(source, ctxt);
    ADDR_WRITE(address, ADDR_READ(address, uint32_t) | 1UL << source, uint32_t);
}

void plic_set_intr_priority(int source, uint32_t priority) {
    ADDR_WRITE(PLIC_INTR_SRC_PRIORITY(source), priority, uint32_t);
}

void plic_set_intr_threshold(int ctxt, uint32_t threshold) {
    ADDR_WRITE(PLIC_THRESH(ctxt), threshold, uint32_t);
}

uint32_t plic_claim(int ctxt) {
    return ADDR_READ(PLIC_CLAIM(ctxt), uint32_t);
}

void plic_complete(int ctxt, uint32_t claim_code) {
    ADDR_WRITE(PLIC_COMPLETION(ctxt), claim_code, uint32_t);
}