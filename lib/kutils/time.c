#include "kutils/time.h"

static int64_t _gmt_adjust;

void time_set_tz(GMT_TYPE type, int hours, int mins) {
    _gmt_adjust = hours * 60 * 60 * 1e9;
    _gmt_adjust += mins * 60 * 1e9;
    if(type == GMT_MINUS) {
        _gmt_adjust *= -1;
    }
}

s_timestamp time_now() {
    int sec_in_min = 60;

    int min_in_hour = 60;
    int sec_in_hour = sec_in_min * min_in_hour;

    int hour_in_day = 24;
    int min_in_day = hour_in_day * min_in_hour;
    int sec_in_day = min_in_day * sec_in_min;

    int sec_in_year = 365 * sec_in_day;



    int days_in_year = 365;
    int days_in_leap_year = days_in_year + 1;

    int64_t ns_in_year = days_in_year * sec_in_day * 1e9;
    int64_t ns_in_leap_year = days_in_leap_year * sec_in_day * 1e9;
    int64_t ns_in_day = sec_in_day * 1e9;
    int64_t ns_in_hour = sec_in_hour * 1e9;
    int64_t ns_in_min = sec_in_min * 1e9;

    int64_t ns_in_month[13] = {     0,
                                    31*ns_in_day,
                                    28*ns_in_day,
                                    31*ns_in_day,
                                    30*ns_in_day,
                                    31*ns_in_day,
                                    30*ns_in_day,
                                    31*ns_in_day,
                                    31*ns_in_day,
                                    30*ns_in_day,
                                    31*ns_in_day,
                                    30*ns_in_day,
                                    31*ns_in_day
                                    };
    int64_t ns_in_month_leap[13] = {    0,
                                        31*ns_in_day,
                                        29*ns_in_day,
                                        31*ns_in_day,
                                        30*ns_in_day,
                                        31*ns_in_day,
                                        30*ns_in_day,
                                        31*ns_in_day,
                                        31*ns_in_day,
                                        30*ns_in_day,
                                        31*ns_in_day,
                                        30*ns_in_day,
                                        31*ns_in_day
                                     };

    
    s_timestamp curr;

    curr.year = EPOCH_YEAR;
    int64_t epoch = rtc_read() + _gmt_adjust;

    while(epoch > ns_in_leap_year) {
        if(IS_LEAP_YEAR(curr.year)) {
            epoch -= ns_in_leap_year;
        } else {
            epoch -= ns_in_year;
        }
        curr.year++;
    }

    curr.month = Jan;

    if IS_LEAP_YEAR(curr.year) {
        while(epoch > ns_in_month_leap[curr.month]) {
            epoch -= ns_in_month_leap[curr.month++];
        }
    } else {
        while(epoch > ns_in_month[curr.month]) {
            epoch -= ns_in_month[curr.month++];
        }
    }

    curr.date = epoch / ns_in_day;
    epoch -= curr.date * (ns_in_day);
    curr.date++;

    curr.hours = epoch / ns_in_hour;
    epoch -= curr.hours * ns_in_hour;

    curr.minutes = epoch / ns_in_min;
    epoch -= curr.minutes * ns_in_min;

    curr.seconds = epoch / 1e9;
    epoch -= curr.seconds * 1e9;

    curr.ns = epoch;

    return curr;
}

char* time_to_string(s_timestamp time) {
    return "";
}

char* time_now_string() {
    return time_to_string(time_now());
}