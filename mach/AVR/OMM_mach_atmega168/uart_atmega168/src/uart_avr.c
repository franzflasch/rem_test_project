#include <uart_avr.h>

#include <avr/io.h>

#define BAUDRATE 4800UL //Definition als unsigned long, sonst gibt es Fehler in der Berechnung

void uart_init(void)
{
	static FILE mystdout = FDEV_SETUP_STREAM( uart_putchar, NULL, _FDEV_SETUP_WRITE );
	uint16_t ubrr = (((F_CPU / (BAUDRATE * 16UL))) - 1);

	UBRR0H = (unsigned char)(ubrr>>8);
	UBRR0L = (unsigned char)ubrr;

	//UCSR0B = (1<<RXEN0)|(1<<TXEN0);
	UCSR0B = (1<<TXEN0);
	UCSR0C = (1<<USBS0)|(3<<UCSZ00);

	stdout = &mystdout;
}

void uart_putc (const uint8_t c)
{
    // Warten, bis UDR bereit ist für einen neuen Wert
	while ( !( UCSR0A & (1<<UDRE0)) );

    // UDR Schreiben startet die Übertragung
    UDR0 = c;
}

// c. Definition der Ausgabefunktion
int uart_putchar( char c, FILE *stream )
{
    uart_putc(c);
    return 0;
}
