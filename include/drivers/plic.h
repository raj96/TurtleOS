#ifndef _PLIC_H
#define _PLIC_H

#define PLIC_ADDR                           0xC000000UL
#define PLIC_INTR_SRC_PRIORITY(src)         (PLIC_ADDR + src * 4)
#define PLIC_INTR_ENABLE(src, ctxt)         (PLIC_ADDR + 0x002000 + (0x80 * ctxt) + (src / 32))
#define PLIC_THRESH(ctxt)                   (PLIC_ADDR + 0x00200000 + (0x1000 * ctxt))
#define PLIC_CLAIM(ctxt)                    (PLIC_ADDR + 0x201000 + (4 * ctxt)) 
#define PLIC_COMPLETION(ctxt)               (PLIC_ADDR + 0x200004 + (0x1000 * (ctxt-1)))

#include <stdint.h>

void plic_enable_intr(int source, int ctxt);
void plic_set_intr_priority(int source, uint32_t priority);
void plic_set_intr_threshold(int ctxt, uint32_t threshold);
uint32_t plic_claim(int ctxt);
void plic_complete(int ctxt, uint32_t claim_code);

#endif