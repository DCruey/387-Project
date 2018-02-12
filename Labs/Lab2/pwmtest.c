#define F_CPU 1000000UL
#include <avr/io.h>
#include <stdint.h>



#define pwm_coma1 7
#define pwm_coma0 6
#define pwm_comb1 5
#define pwm_comb0 4

#define pwm_wgm0 0
#define pwm_wgm1 1
#define pwm_wgm2 3

#define pwm_cs0 0
#define pwm_cs1 1
#define pwm_cs2 2



int main (){
    
    DDRD = //Insert your code here
    TCCR0A |= //Insert your code here
    TCCR0B &= //Insert your code here
    TCCR0B |= //Insert your code here
    
    while (1){
        
        OCR0A = //Insert your code here
        OCR0B = //Insert your code here
        
    }
    
    return 0;
    
}
