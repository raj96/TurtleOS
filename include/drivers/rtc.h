// Goldfish RTC driver
#ifndef _RTC_H
#define _RTC_H

#define RTC_ADDR        0x101000
#define RTC_TIME_LOW    RTC_ADDR
#define RTC_TIME_HIGH   (RTC_ADDR + 0x04)
#define RTC_ALARM_LOW   (RTC_ADDR + 0x08)
#define RTC_ALARM_HIGH  (RTC_ADDR + 0x0c)
#define RTC_CLI         (RTC_ADDR + 0x10)

#include <stdint.h>

int64_t rtc_read();

#endif