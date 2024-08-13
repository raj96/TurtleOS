#include "drivers/uart.h"
#include "addr_op.h"
#include "kutils/console.h"
#include "kutils/time.h"
#include "drivers/rtc.h"
#include "csr_op.h"
#include "drivers/plic.h"

void intr() __attribute__((aligned(4)));

void intr() {
    // Claim interrupt
    uint32_t claim = plic_claim(1);
    kprintf("Interrupted: %x\n", claim);
    // kprintf("%c\n", uart_read_byte());
    plic_complete(1, claim);
}

void kmain() {
    uint64_t intr_addr = ((uint64_t)intr);
    kprintf("interrupt addr: %x\n", intr_addr);
    CSRW_OP("stvec", intr_addr);
    
    plic_set_intr_priority(0x0a, 7);
    plic_set_intr_threshold(1, 0);
    plic_enable_intr(0x0a, 1);

    uart_init();
    kprintln("UART initialized");
    unsigned long int thresh = 1000000000UL;
    time_set_tz(GMT_PLUS, 5, 30);   // Set timezone to GMT +5:30
    
    while(1) {
        for(unsigned long int i = 0; i < thresh; i++); 
        s_timestamp time = time_now();
        kprintf("time: %d/%d/%d %d:%d:%d\n", time.date, time.month, time.year, time.hours, time.minutes, time.seconds);
    }

    while(1);
}