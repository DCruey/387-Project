#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>


#define Baud 4800
#define BaudH ((F_CPU / (16UL * Baud)) -1) >> 8
#define BaudL ((F_CPU / (16UL * Baud)) -1)

void initUART();
void initPWM();


int main(){
	initUART();
	initPWM();
	//uint8_t temp = 0x01;
	//UDR0 = temp;
	while(1){
		if(UCSR0A & ( 1<< RXC0)){//if receive complete flag6
			//OCR0A = UDR0;//sets pwm equal to uart reg	
			UDR0 = UDR0;
			/*if(UCSR0A & ( 1<< UDRE0)){//if receive complete flag6
			//OCR0A = UDR0;//sets pwm equal to uart reg	
				UDR0 = temp;
			}*/
		}
		
	}	
	return 0;
}

void initUART(){
	UCSR0A = 0x00;//error, speed, multi processors, and flags we don't need for this
	UCSR0B = (1 << RXEN0) | (1 << TXEN0);//receive complete bit, txen for transmit
	UCSR0C = (1 << UPM01) | (1 << UPM00) | (1 << UCSZ01) | (1 << UCSZ00);//upm enables odd parity, sets character size to 8 bits

	
	UBRR0H = 0;//BaudH;
	UBRR0L = 12; //BaudL;
}

void initPWM(){
    
    DDRD = 0xFF;
    TCCR0A |= 0xFF; //set to fast PWM (timer register)
    TCCR0B &= 0x00;;
    TCCR0B |= (1 << 0);
    OCR0A = 127;

}
