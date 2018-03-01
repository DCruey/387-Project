#define F_CPU 1000000UL
#include <avr/io.h>

#define cent 58 // 58 us per centimeter

void initExtInterrupt0();
void checkDistance0();