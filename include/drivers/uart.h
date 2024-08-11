// NS16550A driver

#ifndef _UART_H
#define _UART_H

#define UART_BASE(x)    (0x10000000UL + x)
#define UART_RHR        UART_BASE(0)    //  Receive Holding Register    (R )
#define UART_THR        UART_BASE(0)    //  Transmit Holding Register   ( W)
#define UART_IER        UART_BASE(1)    //  Interrupt Enable Register   ( W)
#define UART_FCR        UART_BASE(2)    //  FIFO control Register       ( W)
#define UART_ISR        UART_BASE(2)    //  Interrupt Status Register   (R )
#define UART_LCR        UART_BASE(3)    //  Line Control Register       ( W)
#define UART_MCR        UART_BASE(4)    //  Modem Control Register      ( W)
#define UART_LSR        UART_BASE(5)    //  Line Status Register        (R )
#define UART_MSR        UART_BASE(6)    //  Modem Status Register       (R )
#define UART_SPR        UART_BASE(7)    //  Scratchpad Register Read    (RW)

#define CHR_BACKSPACE   0x08

void uart_init();

void uart_write_byte(char byte);
char uart_read_byte();

void uart_write(char* bytes);
char* uart_read();

void uart_close();

#endif