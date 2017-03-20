#include <avr/io.h>

#define F_CPU 16000000UL
#include <avr/delay.h>
#include "usart.h"
#include "adc.h"
#include "pwm.h"

void onAdcInterrupt(uint16_t v) {
	printf("ADC: %u\n", v);
	pwm_set_width(0.001f + v*0.001f / 1024);
}

int main(void)
{
	usart_init(get_baud(19200));
	adc_init();
	pwm_init();
	
	adc_initInterrupt(1, &onAdcInterrupt);
	
    while(1)
    {
		_delay_ms(100);
    }
}