#define F_CPU 1000000UL
#include <avr/io.h>

void initPWM();
void setPWMA(uint8_t pmw_divide);
void setPWMB(uint8_t pmw_divide);
