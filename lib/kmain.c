#include "drivers/uart.h"
#include "addr_op.h"
#include "kutils/console.h"
#include "kutils/time.h"
#include "drivers/rtc.h"

void kmain() {
    uart_init();
    println("Dropped to supervisor mode...");
    printf("My name is %s\n", "Raj");
    printf("Roll number: %d\n", 48);
    printf("num: %d\thex: %x\tbinary: %b\n", 67, 67, 67);

    unsigned long int thresh = 100000000UL;
    // while(1) {
        for(unsigned long int i = 0; i < thresh; i++); 
        s_timestamp time = time_now();
        printf("time: %d/%d/%d %d:%d:%d\n", time.date, time.month, time.year, time.hours, time.minutes, time.seconds);
    // }

    while(1);
}