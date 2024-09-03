#include "drivers/uart.h"
#include "addr_op.h"
#include "kutils/console.h"
#include "kutils/time.h"
#include "drivers/rtc.h"
#include "csr_op.h"
#include "drivers/plic.h"
#include "drivers/clint.h"
#include "kutils/kmem.h"


void intr() {
    // mstatus_write(mstatus_read() & (~MSTATUS_MIE));

    // ADDR_WRITE(CLINT_MTIMECMP, ADDR_READ(CLINT_MTIME, uint64_t) + 5000000UL, uint64_t);
    // mstatus_write(mstatus_read() | MSTATUS_MIE);
}

void kmain() {
    s_timestamp time = time_now();

    uart_init();
    kprintln("UART initialized");
    kmem_init();

    void *addr = kmalloc(PAGE_SIZE * 6.5);
    kfree(addr);

    time_set_tz(GMT_PLUS, 5, 30);   // Set timezone to GMT +5:30
    kprintf("time: %d/%d/%d %d:%d:%d\n", time.date, time.month, time.year, time.hours, time.minutes, time.seconds);    

    while(1);
}