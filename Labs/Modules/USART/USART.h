#define F_CPU 1000000UL
#include <avr/io.h>

#define Baud 4800
#define BaudH ((F_CPU / (16 * Baud)) -1) >> 8
#define BaudL ((F_CPU / (16 * Baud)) -1)


void initUSART();
uint8_t reciveData();
void sendData(uint8_t data);