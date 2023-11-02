/*
 * eepromplay.c
 *
 * Created: 5/04/2022 12:25:50 PM
 * Author : gauld
 */ 
#define F_CPU 8000000UL

#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>

unsigned int redAddress = 64;
unsigned int blueAddress = 65;
unsigned int greenAddress = 66;

/*
 * CFile1.c
 *
 * Created: 4/04/2022 1:07:47 PM
 *  Author: gauld
 */ 

void ledInit() {
	
	// output OCOA, OCOB, OC2B
	DDRD |= (1 << 3) | (1 << 5) | (1 << 6);
	
	// WGM0 = 011, COM0A = COM0B = 11, CS0 = 001
	TCCR0A = (1<<COM0A0) | (1<<COM0A1) | (1<<COM0B0) | (1<<COM0B1) | (1<<WGM00) | (1<<WGM01);
	TCCR0B = (1<<CS00);
	
	// WGM2 = 011, COM2B = 11, CS2 = 001
	TCCR2A = (1<<COM2B0) | (1<<COM2B1) | (1<<WGM20) | (1<<WGM21);
	TCCR2B = (1<<CS20);
	
	// Set everything to 0 to start
	OCR0A = 0; //lower starting bound
	OCR0B = 0; //upper starting bound
	OCR2B = 0; //upper starting bound
	
}

void timerInit() {
	TCCR1B = (1 << WGM12);
	OCR1A = 125;
	TIMSK1 = (1 << OCIE1A);
	
	sei();
	
	TCCR1B |= (1 << CS11) | (1 << CS10);
}

void writeLED(int red, int blue, int green) {
	OCR0A = red;
	OCR0B = blue;
	OCR2B = green;
}

unsigned char EEPROM_read(unsigned int uiAddress) {
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}

void EEPROM_write(unsigned int uiAddress, unsigned char ucData) {
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE))
	;
	/* Set up address and Data Registers */
	EEAR = uiAddress;
	EEDR = ucData;
	/* Write logical one to EEMPE */
	EECR |= (1<<EEMPE);
	/* Start eeprom write by setting EEPE */
	EECR |= (1<<EEPE);
}

int main(void) {
	ledInit();
	timerInit();
	
	unsigned char redVal = EEPROM_read(redAddress);
	unsigned char blueVal = EEPROM_read(blueAddress);
	unsigned char greenVal = EEPROM_read(greenAddress);
	
	writeLED((unsigned int)redVal, (unsigned int)blueVal, (unsigned int)greenVal);
	
	//writeLED(0,0,0);
	
	//_delay_ms(2000);
	
	//writeLED(100, 100, 100);
	
	EEPROM_write(redAddress, (unsigned char)255);
	EEPROM_write(blueAddress, (unsigned char)255);
	EEPROM_write(greenAddress, (unsigned char)255);
	
	
    /* Replace with your application code */
    while (1) {
		
    }
}

