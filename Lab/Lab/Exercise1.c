#define F_CPU 16000000UL

#include <avr/io.h>
#include <util/delay.h>
#include "led.h"
#include "switch.h"
#include "usart.h"

int main(void)
{
	led_init();
	switch_init();
	usart_init(get_baud(19200));
	
    while(1)
    {
		// Test blink led
		/*
		for (uint8_t i = 0; i < 4; i++) {
			led_set(i, switch_read(i));
		}
		_delay_ms(500);
		*/
		
		// Test usart printf
		/*printf("Test\n");*/
		
		// Test usart from pc
		char c = usart_getchar();
		if (c > 0) {
			usart_putchar(c);
		}
    }
}