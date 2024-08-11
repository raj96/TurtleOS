// Driver for ns16550a
#include "drivers/uart.h"
#include "addr_op.h"

void uart_init() {
    // Disable interrupts for UART
    ADDR_WRITE(UART_IER, 0x00, char);

    // Set baud rate to 115.2K
    ADDR_WRITE(UART_LCR, 1UL << 7, char);
    ADDR_WRITE(UART_THR, 0x04, char);
    ADDR_WRITE(UART_IER, 0x00, char);

    // Set Line Control Register to 8 bit words and no parity
    ADDR_WRITE(UART_LCR, 0x03, char);

    // Enable and clear the FIFO
    ADDR_WRITE(UART_FCR, 0x07, char);

    // Enable receiver ready and transmitter empty interrupts
    ADDR_WRITE(UART_IER, 0x03, char);
    
    uart_write("UART initialized...\n\r");
}

void uart_write_byte(char byte) {
    // Spin while THR in LSR is not set
    while((ADDR_READ(UART_LSR, char) & (1 << 5)) == 0);

    ADDR_WRITE(UART_THR, byte, char);

    if(byte == CHR_BACKSPACE) {
        uart_write_byte(' ');
        while((ADDR_READ(UART_LSR, char) & (1 << 5)) == 0);
        ADDR_WRITE(UART_THR, CHR_BACKSPACE, char);
    }
}

char uart_read_byte() {
    while((ADDR_READ(UART_LSR, char) & 0x01) == 0);

    return ADDR_READ(UART_RHR, char);
}

void uart_write(char *bytes) {
    while(*bytes != '\0') {
        uart_write_byte(*bytes);
        bytes++;
    }
}

char* uart_read() {}

void uart_close() {}