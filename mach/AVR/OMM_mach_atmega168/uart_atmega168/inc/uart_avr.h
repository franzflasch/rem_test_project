#ifndef UART_AVR_H_
#define UART_AVR_H_

#include <stdint.h>
#include <stdio.h>

void uart_init (void);
void uart_putc (const uint8_t c);
uint8_t uart_getc (void);
int uart_putchar(char c, FILE *stream);

#endif /* UART_AVR_H */
