#include "drivers/uart.h"
#include "addr_op.h"
#include "kutils/console.h"
#include "kutils/time.h"
#include "drivers/rtc.h"

void kmain() {
    uart_init();
    println("UART initialized");
    unsigned long int thresh = 1000000000UL;
    time_set_tz(GMT_PLUS, 5, 30);   // Set timezone to GMT+5:30
    
    while(1) {
        for(unsigned long int i = 0; i < thresh; i++); 
        s_timestamp time = time_now();
        printf("time: %d/%d/%d %d:%d:%d\n", time.date, time.month, time.year, time.hours, time.minutes, time.seconds);
    }

    while(1);
}