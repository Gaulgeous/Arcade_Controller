/*
 * flash.h
 *
 * Created: 23/04/2022 3:16:52 PM
 *  Author: gauld
 */ 

#ifndef SETUP
#define SETUP
#define F_CPU 8000000UL

#include <stdint.h>
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#endif

#ifndef FLASH_H_
#define FLASH_H_

#define FLASH_OFFSET_RED 256
#define FLASH_OFFSET_BLUE FLASH_OFFSET_RED + 8
#define FLASH_OFFSET_GREEN FLASH_OFFSET_RED + 16
#define FLASH_OFFSET_DPAD FLASH_OFFSET_RED + 24

int joyMode;
int redFlash;
int blueFlash;
int greenFlash;
int ampFlash;

void eepromWrite(unsigned int uiAddress, unsigned char ucData);
unsigned char eepromRead(unsigned int uiAddress);



#endif /* FLASH_H_ */