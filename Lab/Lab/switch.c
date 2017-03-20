#include "switch.h"
#include "bit_manipulator.h"

void switch_init() {
	// Set pins B1, B3, B5, B7 as output
	clear_bit(DDRB, DDB1);
	clear_bit(DDRB, DDB3);
	clear_bit(DDRB, DDB5);
	clear_bit(DDRB, DDB7);
}

uint8_t switch_read(uint8_t n) {
	if (test_bit(PINB, PB1 + 2*n)) {
		return 0;
	}
	return 1;
}