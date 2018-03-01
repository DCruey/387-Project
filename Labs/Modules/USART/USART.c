#include "USART.h"


void initUSART(){
	UCSR0A = 0x00;//error, speed, multi processors, and flags we don't need for this
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);//receive Enable bit
	UCSR0C = (1 << UPM01) | (1 << UPM00) | (1 << UCSZ01) | (1 << UCSZ00);//upm enables odd parity, sets character size to 8 bits
	
	UBRR0H = BaudH;
	UBRR0L = BaudL;
}

uint8_t reciveData(){
	if(UCSR0A & ( 1<< RXC0)){//if receive complete flag
		return UDR0;
	}
}

void sendData(uint8_t data){
	if(UCSR0A & ( 1<< UDRE0)){//if receive complete flag6
		UDR0 = data;
	}	
}
