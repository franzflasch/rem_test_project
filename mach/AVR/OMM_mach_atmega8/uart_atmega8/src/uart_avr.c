#include <uart_avr.h>
#include <avr/io.h>

#define BAUDRATE 4800UL //Definition als unsigned long, sonst gibt es Fehler in der Berechnung

void uart_init (void)
{
	static FILE mystdout = FDEV_SETUP_STREAM( uart_putchar, NULL, _FDEV_SETUP_WRITE );

    uint16_t ubrr = (uint16_t) ((uint32_t) F_CPU/(16*BAUDRATE) - 1);

    UBRRH = (uint8_t) (ubrr>>8);
    UBRRL = (uint8_t) (ubrr);

    // UART Receiver und Transmitter anschalten
    // Data mode 8N1, asynchron
    //UCSRB = (1 << RXEN) | (1 << TXEN);
    UCSRB = (1 << TXEN);
    UCSRC = (1 << URSEL) | (1 << UCSZ1) | (1 << UCSZ0);

    // Flush Receive-Buffer (entfernen evtl. vorhandener ungültiger Werte)
    do
    {
        UDR;
    }
    while (UCSRA & (1 << RXC));

    stdout = &mystdout;
}

void uart_putc (const uint8_t c)
{
    // Warten, bis UDR bereit ist für einen neuen Wert
    while (!(UCSRA & (1 << UDRE)))
        ;

    // UDR Schreiben startet die Übertragung
    UDR = c;
}

uint8_t uart_getc (void)
{
    // Warten, bis etwas empfangen wird
    while (!(UCSRA & (1 << RXC)))
        ;

    // Das empfangene Zeichen zurückliefern
    return UDR;
}

// c. Definition der Ausgabefunktion
int uart_putchar( char c, FILE *stream )
{
    uart_putc(c);
    return 0;
}
