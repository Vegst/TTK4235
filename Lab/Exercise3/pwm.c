#include "pwm.h"

#include <avr/io.h>
#include "bit_manipulator.h"

#define F_CPU 16000000UL

void pwm_init() {
	// Configure TIMER1: Fast PWM
	set_bit(TCCR1A, COM1A1); // Set on compare match, clear at TOP
	set_bit(TCCR1A, COM1B1);
	set_bit(TCCR1A, WGM11); // Fast PWM
	set_bit(TCCR1B, WGM12);
	set_bit(TCCR1B, WGM13);
	set_bit(TCCR1B, CS11); // Prescalar: 64 (chosen large enough to fit ICR1 in register: ICR1 < 65536)
	set_bit(TCCR1B, CS10);
	
	TCCR3A =  (1 << WGM31) | (1 << COM3A1);
	TCCR3B = (1 << WGM33) | (1 << WGM32) | (1 << CS31);
	
	// Set F_PWM = 50Hz (Period = 20ms Standard)
	// Chosen from: F_PWM = F_CPU /(N*(1+TOP)), where TOP=ICR1 and N=64 (prescalar)
	ICR1 = 4999;
	
	// Set timer as output
	set_bit(DDRB, PB5);
}

void pwm_set_width(float ms) {
	// F_CPU/64 is the total period
	OCR1A = ms * (F_CPU / 64);
}