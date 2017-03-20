#include "adc.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include "bit_manipulator.h"

static void (*adc_onInterrupt)(uint16_t v);

void adc_init() {
	
	// Set voltage reference: AREF, internal VREF turned off
	clear_bit(ADMUX, REFS0);
	clear_bit(ADMUX, REFS1);
	
	// ADC works best in range 50-200kHz.
	// As F_CPU = 16MHz, a prescalar of 128 gives a F_ADC = 16MHz/128 = 125kHz, which is a sufficient frequency
	
	// Set prescalar: 128
	set_bit(ADCSRA, ADPS0);
	set_bit(ADCSRA, ADPS1);
	set_bit(ADCSRA, ADPS2);
	
	// Enable ADC
	set_bit(ADCSRA, ADEN);
}

ISR(ADC_vect) {
	(*adc_onInterrupt)(ADC);
	
	// Complete conversion
	set_bit(ADCSRA, ADSC);
}

void adc_initInterrupt(uint8_t n, void (*onInterrupt)(uint16_t)) {
	
	ADMUX = n;
	
	// Enable auto triggering on the ADC
	set_bit(ADCSRA, ADATE);
	
	// Single conversion
	set_bit(ADCSRA, ADSC);
	
	// Enable ADC interrupt
	set_bit(ADCSRA, ADIE);
	
	// Enable global interrupts
	sei();
	
	// Set function handler which will fire at adc interrupt
	adc_onInterrupt = onInterrupt;
}

uint16_t adc_read(uint8_t n) {
	
	ADMUX = n;
	
	// Start single conversion
	set_bit(ADCSRA, ADSC);
	
	// Wait for conversion to complete
	while(test_bit(ADCSRA, ADSC));
	
	// Return ADC value
	return ADC;
}