/*
 * readWrite.c
 *
 * Created: 4/04/2022 1:39:43 PM
 *  Author: gauld
 */ 

#include "init.h"

// Write the value to the amplifier (Not yet implemented)
void writeAmp(uint8_t ampVal) {
	
}

// Write the values to each LED
void writeLed(int red, int blue, int green) {
	OCR0A = red;
	OCR0B = blue;
	OCR2B = green;
}

// Reading in the first set states for the buttons
uint8_t buttonStates1() {
	uint8_t buttonBytes = 0;
	// [0, BP, BC, B5, B4, B3, B2, B1]
	buttonBytes |= (~(PINC & (1 << B1)) << 0);
	buttonBytes |= (~(PINC & (1 << B2)) << 1);
	buttonBytes |= (~(PINC & (1 << B3)) << 2);
	buttonBytes |= (~(PINC & (1 << B4)) << 3);
	buttonBytes |= (~(PINC & (1 << B5)) << 4);
	buttonBytes |= (~(PIND & (1 << BC)) << 5);
	buttonBytes |= (~(PIND & (1 << BP)) << 6);
	return buttonBytes;
}

// Reading in the second set of states for the buttons
// Is there any use in having these states?
uint8_t buttonStates2() {
	uint8_t buttonBytes = 0;
	// [0, BP, BC, B5, B4, B3, B2, B1]
	buttonBytes |= (~(PINC & (1 << B1)) << 0);
	buttonBytes |= (~(PINC & (1 << B2)) << 1);
	buttonBytes |= (~(PINC & (1 << B3)) << 2);
	buttonBytes |= (~(PINC & (1 << B4)) << 3);
	buttonBytes |= (~(PINC & (1 << B5)) << 4);
	buttonBytes |= (~(PIND & (1 << BC)) << 5);
	buttonBytes |= (~(PIND & (1 << BP)) << 6);
	return buttonBytes;
}

// Reading in the values for each of the joystick states
uint8_t dpadState() {
	uint8_t dpad = 0;
	// [0, 0, 0, 0, JOYU, JOYD, JOYL, JOYR]
	dpad |= ((PIND & (1 << JOYU)) << 0);
	dpad |= ((PINB & (1 << JOYD)) << 1);
	dpad |= ((PINB & (1 << JOYL)) << 2);
	dpad |= ((PINB & (1 << JOYR)) << 3);
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

