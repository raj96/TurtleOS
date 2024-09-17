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
    for(int i = 0; i < 10; i++) {
        kprint("Test Task 1\n");
    }
}

void test_task2() {
    for(int i = 0; i < 10; i++) {
        kprint("Test Task 2 !!!\n");
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

    ktask_add(&test_task1);
    ktask_add(&test_task2);
    
    ktask_run_scheduler();
}