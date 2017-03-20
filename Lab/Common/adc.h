#ifndef ADC_H_
#define ADC_H_

#include <avr/io.h>

void adc_init();
void adc_initInterrupt(uint8_t n, void (*onInterrupt)(uint16_t));
uint16_t adc_read(uint8_t n);


#endif /* ADC_H_ */