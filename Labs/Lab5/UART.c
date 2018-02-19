#define F_CPU 1000000UL
#include <avr/io.h>



#define Baud 9600
#define BaudH ((F_CPU / (16 * Baud)) -1) >> 8
#define BaudL ((F_CPU / (16 * Baud)) -1)

void initUART();


int main(){
	
	return 0;
}

void initUART(){
	UCSR0A = ;
	UCSR0B = ;
	UCSR0C = (1 << UPM01) | (1 << UPM00) | (1 << UCSZ01) | (1 << UCSZ00);
	
	UBRR0H = BaudH;
	UBRR0L = BaudL;
}
