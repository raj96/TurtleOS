#include "csr_op.h"

uint64_t mstatus_read() {
    CSRR_OP("mstatus", uint64_t);
}

void mstatus_write(uint64_t ms) {
    CSRW_OP("mstatus", ms);
}

uint64_t mie_read() {
    CSRR_OP("mie", uint64_t);
}

void mie_write(uint64_t mie) {
    CSRW_OP("mie", mie);
}

uint64_t mideleg_read() {
    CSRR_OP("mideleg", uint64_t);
}

void mideleg_write(uint64_t mideleg) {
    CSRW_OP("mideleg", mideleg);
}

uint64_t medeleg_read() {
    CSRR_OP("medeleg", uint64_t);
}

void medeleg_write(uint64_t mideleg) {
    CSRW_OP("medeleg", mideleg);
}

uint64_t sie_read() {
    CSRR_OP("sie", uint64_t);
}

void sie_write(uint64_t sie) {
    CSRW_OP("sie", sie);
}

uint64_t sstatus_read() {
    CSRR_OP("sstatus", uint64_t);
}

void sstatus_write(uint64_t ss) {
    CSRW_OP("sstatus", ss);
}

uint64_t sepc_read() {
    CSRR_OP("sepc", uint64_t);
}

void sepc_write(uint64_t sepc) {
    CSRW_OP("sepc", sepc);
}