CC = avr-gcc
MCU = atmega328
F_CPU = 1000000
CCOPTS=  -Wall -O1 -DF_CPU=$(F_CPU) -mmcu=$(MCU) 


default: main

main:main.c ExtInterrupts.o
	 $(CC) $(CCOPTS) main.c ExtInterrupts.o -o main

ExtInterrupts.o: ExtInterrupts.c ExtInterrupts.h
	 $(CC) $(CCOPTS) -c ExtInterrupts.h ExtInterrupts.c

/*
motor.o: motor.c motor.h
	 $(CC) $(CCOPTS) -c motor.h motor.c
*/

program: main
	avr-objcopy -R .eeprom -O ihex main main.hex
	avrdude -c usbtiny -p atmega328 -U flash:w:main.hex


clean:
	rm main main.hex ExtInterrupts.o ExtInterrupts.h.gch
