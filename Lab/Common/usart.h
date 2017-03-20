#include <avr/io.h>

#ifndef USART_H_
#define USART_H_

#define F_CPU 16000000UL
#define get_baud(baudrate) F_CPU/(16UL*baudrate)-1

uint8_t usart_init(uint16_t baud);
void usart_putchar(char c);
char usart_getchar();


#endif /* USART_H_ */