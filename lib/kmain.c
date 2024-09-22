#include "drivers/uart.h"
#include "addr_op.h"
#include "kutils/console.h"
#include "kutils/time.h"
#include "drivers/rtc.h"
#include "csr_op.h"
#include "drivers/plic.h"
#include "drivers/clint.h"
#include "kutils/kmem.h"
#include "kutils/ktask.h"


void test_task1() {
    for(uint64_t t1 = 0; t1 < 1e9; t1++) {
        asm volatile("addi t5, t5, 1");
    }
}

void test_task2() {
    for(uint64_t t2 = 0; t2 < 1e9; t2++) {
        asm volatile("addi t6, t6, 1");
    }
}

void kmain() {
    s_timestamp time = time_now();

    uart_init();
    kprintln("UART initialized");

    kmem_init();
    ktask_init();

    time_set_tz(GMT_PLUS, 5, 30);   // Set timezone to GMT +5:30
    kprintf("time: %d/%d/%d %d:%d:%d\n", time.date, time.month, time.year, time.hours, time.minutes, time.seconds);    

    asm volatile("xor t5, t5, t5");
    asm volatile("xor t6, t6, t6");

    ktask_add(&test_task1);
    ktask_add(&test_task2);
    
    ktask_run_scheduler();
}