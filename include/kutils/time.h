#ifndef _TIME_H
#define _TIME_H

#include "drivers/rtc.h"

#define IS_LEAP_YEAR(x) ((x % 4 == 0 && x % 100 != 0) || (x % 400 == 0))
#define EPOCH_YEAR 1970

typedef enum {
    XXX,
    Jan,
    Feb,
    Mar,
    Apr,
    May,
    Jun,
    Jul,
    Aug,
    Sep,
    Oct,
    Nov,
    Dec
} e_month;

typedef struct {
    e_month month;
    int date, year;
    int hours, minutes, seconds;
    int64_t ns;
} s_timestamp;

s_timestamp time_now();

#endif