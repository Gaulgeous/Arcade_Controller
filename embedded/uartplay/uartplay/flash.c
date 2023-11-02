/*
 * CFile1.c
 *
 * Created: 12/04/2022 12:00:40 PM
 *  Author: gauld
 */ 

#include "flash.h"

// Write a value to the selected EEPROM address
void eepromWrite(unsigned int uiAddress, unsigned char ucData) {
	unsigned char previousValue = eepromRead(uiAddress);
	if (ucData != previousValue) {
		/* Wait for completion of previous write */
		while(EECR & (1<<EEPE));
		/* Set up address and Data Registers */
		EEAR = uiAddress;
		EEDR = ucData;
		/* Write logical one to EEMPE */
		EECR |= (1<<EEMPE);
		/* Start eeprom write by setting EEPE */
		EECR |= (1<<EEPE);
	}
}

// Read the information from the given EEPROM address
unsigned char eepromRead(unsigned int uiAddress) {
	/* Wait for completion of previous write */
	while(EECR & (1<<EEPE));
	/* Set up address register */
	EEAR = uiAddress;
	/* Start eeprom read by writing EERE */
	EECR |= (1<<EERE);
	/* Return data from Data Register */
	return EEDR;
}