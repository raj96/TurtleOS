#include "drivers/uart.h"
#include "addr_op.h"
#include "kutils/console.h"
#include "kutils/time.h"
#include "drivers/rtc.h"
#include "csr_op.h"
#include "drivers/plic.h"
#include "drivers/clint.h"


s_timestamp time;

void intr() {
    mstatus_write(mstatus_read() & (~MSTATUS_MIE));
    time = time_now();

    kprintf("time: %d/%d/%d %d:%d:%d\n", time.date, time.month, time.year, time.hours, time.minutes, time.seconds);

    ADDR_WRITE(CLINT_MTIMECMP, ADDR_READ(CLINT_MTIME, uint64_t) + 5000000UL, uint64_t);
    mstatus_write(mstatus_read() | MSTATUS_MIE);
}

void kmain() {
    uart_init();
    kprintln("UART initialized");

    time_set_tz(GMT_PLUS, 5, 30);   // Set timezone to GMT +5:30

    while(1);
}