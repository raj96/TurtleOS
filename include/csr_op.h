#ifndef _CSR_OP
#define _CSR_OP

#include <stdint.h>

#define CSRR_OP(reg, T) T v; asm volatile("csrr %0, " reg: "=r" (v)); return v
#define CSRW_OP(reg, v) asm volatile("csrw " reg ", %0": :"r" (v))

#define MSTATUS_SIE     (1UL << 1)
#define MSTATUS_MIE     (1UL << 3)
#define MSTATUS_SPIE    (1UL << 5)
#define MSTATUS_UBE     (1UL << 6)
#define MSTATUS_MPIE    (1UL << 7)
#define MSTATUS_SPP     (1UL << 8)
#define MSTATUS_MPP_M   (3UL << 11)
#define MSTATUS_MPP_S   (1UL << 11)
#define MSTATUS_MPP_U   (0UL << 11)

static inline uint64_t mstatus_read() {
    CSRR_OP("mstatus", uint64_t);
}
static inline void mstatus_write(uint64_t ms) {
    CSRW_OP("mstatus", ms);
}

#define MIE_USIE    1UL
#define MIE_SSIE    (1UL << 1)
#define MIE_MSIE    (1UL << 3)
#define MIE_UTIE    (1UL << 4)
#define MIE_STIE    (1UL << 5)
#define MIE_MTIE    (1UL << 7)
#define MIE_UEIE    (1UL << 8)
#define MIE_SEIE    (1UL << 9)
#define MIE_MEIE    (1UL << 11)

static inline uint16_t mie_read() {
    CSRR_OP("mie", uint16_t);
}
static inline void mie_write(uint16_t mie) {
    CSRW_OP("mie", mie);
}

#define MCAUSE_SSI  ((1UL << 63) | 1)
#define MCAUSE_MSI  ((1UL << 63) | 3)
#define MCAUSE_STI  ((1UL << 63) | 5)
#define MCAUSE_MTI  ((1UL << 63) | 7)
#define MCAUSE_SEI  ((1UL << 63) | 9)
#define MCAUSE_MEI  ((1UL << 63) | 11)
#define MCAUSE_COI  ((1UL << 63) | 13)
    
#define MCAUSE_ECALLU   8
#define MCAUSE_ECALLS   9
#define MCAUSE_ECALLM   11

static inline uint64_t mideleg_read() {
    CSRR_OP("mideleg", uint64_t);
}
static inline void mideleg_write(uint64_t mideleg) {
    CSRW_OP("mideleg", mideleg);
}

static inline uint64_t medeleg_read() {
    CSRR_OP("medeleg", uint64_t);
}
static inline void medeleg_write(uint64_t medeleg) {
    CSRW_OP("medeleg", medeleg);
}

#define SIE_SSIE    (1 << 1)
#define SIE_STIE    (1 << 5)
#define SIE_SEIE    (1 << 9)
#define SIE_LCOFIE  (1 << 13)

static inline uint64_t sie_read() {
    CSRR_OP("sie", uint64_t);
}
static inline void sie_write(uint64_t sie) {
    CSRW_OP("sie", sie);
}

#define SSTATUS_SIE     (1UL << 1)
#define SSTATUS_SPIE    (1UL << 5)
#define SSTATUS_UBE     (1UL << 6)
#define SSTATUS_SPP     (1UL << 8)

static inline uint64_t sstatus_read() {
    CSRR_OP("sstatus", uint64_t);
}
static inline void sstatus_write(uint64_t ss) {
    CSRW_OP("sstatus", ss);
}

static inline uint64_t sepc_read() {
    CSRR_OP("sepc", uint64_t);
}
static inline void sepc_write(uint64_t sepc) {
    CSRW_OP("sepc", sepc);
}

#endif