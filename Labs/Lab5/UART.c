#define F_CPU 1000000UL
#include <avr/io.h>



#define Baud 9600
#define BaudH ((F_CPU / (16 * Baud)) -1) >> 8
#define BaudL ((F_CPU / (16 * Baud)) -1)

void initUART();
void initPWM();


int main(){
	initUART();
	initPWM();
	while(1){
		if(UCSR0A & ( 1<< RXC0)){//if receive complete flag
			OCR0A = UDR0;//sets pwm equal to uart reg
		}	
	}
	return 0;
}

void initUART(){
	UCSR0A = 0x00;//error, speed, multi processors, and flags we don't need for this
	UCSR0B = (1 << RXEN0);//receive complete bit
	UCSR0C = (1 << UPM01) | (1 << UPM00) | (1 << UCSZ01) | (1 << UCSZ00);//upm enables odd parity, sets character size to 8 bits
	
	UBRR0H = BaudH;
	UBRR0L = BaudL;
}

void initPWM(){
    
    DDRD = 0xFF;
    TCCR0A |= 0xFF; //set to fast PWM (timer register)

}
