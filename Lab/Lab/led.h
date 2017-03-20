#ifndef LED_H_
#define LED_H_

#include <avr/io.h>

void led_init();
uint8_t led_set(uint8_t n, uint8_t v);


#endif /* LED_H_ */