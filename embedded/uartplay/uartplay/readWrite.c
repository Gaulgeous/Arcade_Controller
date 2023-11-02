/*
 * readWrite.c
 *
 * Created: 19/04/2022 1:01:48 PM
 *  Author: gauld
 */ 

#include "readWrite.h"

// Write the value to the amplifier (Not yet implemented)
void writeAmp(uint8_t ampVal) {
	
}

// Write the values to each LED
void writeLed(int red, int blue, int green) {
	OCR2B = 255 - red;
	OCR0B = 255 - blue;
	OCR0A = 255 - green;
}

// Reading in the first set states for the buttons
uint8_t buttonStates1() {
	uint8_t buttonBytes = 0x00;
	// [0, BP, BC, B5, B4, B3, B2, B1]
	if ((PINC & (1 << B1)) == 0) {
		buttonBytes |= 1 << 0;
	}
	if ((PINB & (1 << B2)) == 0) {
		buttonBytes |= 1 << 1;
	}
	if ((PINC & (1 << B3)) == 0) {
		buttonBytes |= 1 << 2;
	}
	if ((PINC & (1 << B4)) == 0) {
		buttonBytes |= 1 << 3;
	}
	if ((PINC & (1 << B5)) == 0) {
		buttonBytes |= 1 << 4;
	}
	if ((PIND & (1 << BP)) == 0) {
		buttonBytes |= 1 << 5;
	}
	if ((PIND & (1 << BC)) == 0) {
		buttonBytes |= 1 << 6;
	}
	
	return buttonBytes;
}

// Reading in the values for each of the joystick states
uint8_t dpadState() {
	uint8_t dpad = 0;
	// [0, 0, 0, 0, JOYU, JOYD, JOYL, JOYR]
	if ((PIND & (1 << JOYU)) == 0) {
		dpad |= 1 << 0;
	}
	if ((PINB & (1 << JOYD)) == 0) {
		dpad |= 1 << 1;
	}
	if ((PINB & (1 << JOYL)) == 0) {
		dpad |= 1 << 2;
	}
	if ((PINB & (1 << JOYR)) == 0) {
		dpad |= 1 << 3;
	}
	return dpad;
}

// Reading in the value for the y axis of the joystick
int joyYState() {
	int joyY = 0;
	// Set the joystick axis
	if ((PIND & (1 << JOYU)) == 0) {
		joyY = 127;
	} else if ((PINB & (1 << JOYD)) == 0) {
		joyY = -127;
	}
	return joyY;
}

// Reading in the value for the x axis of the joystick
int joyXState() {
	int joyX = 0;
	if ((PINB & (1 << JOYL)) == 0) {
		joyX = 127;
	} else if ((PINB & (1 << JOYR)) == 0) {
		joyX = -127;
	}
	return joyX;
}
