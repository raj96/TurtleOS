#include "kutils/console.h"
#include "drivers/uart.h"

#include <stdarg.h>
#include <stdint.h>

char nums[16] = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9', 'A', 'B', 'C', 'D', 'E', 'F'};

void kprint(char *str) {
    uart_write(str);
}

void kprintln(char *str) {
    uart_write(str);
    uart_write_byte('\n');
    uart_write_byte('\r');
}

void _print_num_base(int64_t num, int base) {
    if(num == 0) { return; }

    int digit = num % base;
    _print_num_base(num / base, base);
    uart_write_byte(nums[digit]);
}

void _print_num(uint64_t num, int base, int sign) {
    
    if(num == 0) {
        uart_write_byte('0');
    } else {
        if(sign == 1) {
            int64_t s_num = (int64_t)num;
            if(s_num <  0) { 
                kprint("-");
                num = s_num * -1;
            }
        }
        _print_num_base(num, base);
    }
}
// Supports the following
//  %d - Decimal
//  %x - Hexadecimal
//  %b - Binary
//  %c - Character
//  %s - String
//  %l - signed long decimal
//  %u - unsigned long decimal
void kprintf(char *fmt, ...) {
    va_list ap;

    va_start(ap, fmt);

    while(*fmt != '\0') {
        if(*fmt != '%') {
            uart_write_byte(*fmt);
            if(*fmt == '\n') {
                uart_write_byte('\r');
            }
        } else {
            fmt++;
            switch(*fmt) {
                case '%':
                    uart_write_byte('%');
                    break;
                case 'c':
                    uart_write_byte((char)va_arg(ap, int));
                    break;
                case 's':
                    uart_write(va_arg(ap, char *));
                    break;
                case 'd':
                    _print_num(va_arg(ap, int64_t), 10, 1);
                    break;
                case 'x':
                    uart_write("0x");
                    _print_num(va_arg(ap, uint64_t), 16, 0);
                    break;
                case 'b':
                    uart_write("0b");
                    _print_num(va_arg(ap, uint64_t), 2, 0);
                    break;
                case 'l':
                    _print_num(va_arg(ap, int64_t), 10, 1);
                    break;
                case 'u':
                    _print_num(va_arg(ap, uint64_t), 10, 0);
            }
        }
        fmt++;
    }

    va_end(ap);
}

void kscanf(char *fmt, ...) {
    
}