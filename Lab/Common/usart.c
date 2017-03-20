#include "usart.h"

#define F_CPU 16000000UL
#include <avr/io.h>
#include <stdio.h>
#include "bit_manipulator.h"

static FILE usart_stdout = FDEV_SETUP_STREAM(usart_putchar, usart_getchar, _FDEV_SETUP_WRITE);

uint8_t usart_init(uint16_t baud) {
	
	// Set baud rate
	UBRR1H = (unsigned char)(baud>>8);
	UBRR1L = (unsigned char)baud;
	
	// Enabled receiver and transmitter
	UCSR1B = 0x00;
	set_bit(UCSR1B, RXEN1);
	set_bit(UCSR1B, TXEN1);
	
	// Set frame format: 2 stop bits, 8 data bits, no parity
	UCSR1C = 0x00;
	set_bit(UCSR1C, USBS1);  // 2 stop bits
	set_bit(UCSR1C, UCSZ10); // 8 data bits
	set_bit(UCSR1C, UCSZ11);
	clear_bit(UCSR1B, UCSZ12);
	clear_bit(UCSR1C, UPM10); // No parity
	clear_bit(UCSR1C, UPM11);
	
	// Enable printf()
	stdout = &usart_stdout;
}

void usart_putchar(char c) {
	
	// Wait for empty transmit buffer
	while (!test_bit(UCSR1A, UDRE1));
	//while ( !( UCSR1A & (1<<UDRE1)))
	//	;
	// Put data into buffer, sends the data
	UDR1 = (uint8_t)c;
}

char usart_getchar() {
	
	// Wait for data to be received
	while (!test_bit(UCSR1A, RXC1));
	
	// Get and return received data from buffer
	return UDR1;
}