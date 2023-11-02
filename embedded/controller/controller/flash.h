/*
 * flash.h
 *
 * Created: 12/04/2022 12:01:06 PM
 *  Author: gauld
 */ 

#ifndef LIBRARIES
#define LIBRARIES
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#endif

#ifndef FLASH_H_
#define FLASH_H_

#define FLASHOFFSET 256
int joyMode;
int redFlash;
int blueFlash;
int greenFlash;
int ampFlash;

void eepromWrite(unsigned int uiAddress, unsigned char ucData);
unsigned char eepromRead(unsigned int uiAddress);

#endif /* FLASH_H_ */