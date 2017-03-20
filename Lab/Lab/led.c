#include "led.h"

#include <avr/io.h>
#include "bit_manipulator.h"

void led_init() {
	// Set pins B0, B2, B4, B6 as output
	set_bit(DDRB, DDB0);
	set_bit(DDRB, DDB2);
	set_bit(DDRB, DDB4);
	set_bit(DDRB, DDB6);
	// Clear all leds
	for (int i = 0; i < 4; i++) {
		led_set(i, 0);
	}
}

uint8_t led_set(uint8_t n, uint8_t v) {
	if (v) {
		clear_bit(PORTB, n*2);
	}
	else {
		set_bit(PORTB, n*2);
	}
}