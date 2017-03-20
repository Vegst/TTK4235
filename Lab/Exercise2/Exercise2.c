#include <avr/io.h>

#include "adc.h"
#include "usart.h"

// Interrupt
void onAdcInterrupt(uint16_t v) {
	printf("ADC: %u\n", v);
}

int main(void)
{
	usart_init(get_baud(19200));
	adc_init();
	
	// Interrupt
	adc_initInterrupt(1, &onAdcInterrupt);
	
    while(1)
    {
		// Polling
        /*printf("ADC: %u\n", adc_read(1));*/
    }
}