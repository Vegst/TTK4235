#ifndef BIT_MANIPULATOR_H_
#define BIT_MANIPULATOR_H_


#define set_bit(reg, bit) reg |= (1 << bit)
#define clear_bit(reg, bit) reg &= ~(1 << bit)
#define test_bit(reg, bit) (reg & (1 << bit))

#endif /* BIT_MANIPULATOR_H_ */