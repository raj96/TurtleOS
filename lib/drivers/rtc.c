// Driver for goldfish rtc
#include "drivers/rtc.h"
#include "addr_op.h"


int64_t rtc_read() {
    int64_t time;

    time = ADDR_READ(RTC_TIME_LOW, int64_t);
    time |= (ADDR_READ(RTC_TIME_HIGH, int64_t) << 32);

    return time;
}