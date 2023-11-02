/*
 * readWrite.c
 *
 * Created: 19/04/2022 1:01:48 PM
 *  Author: gauld
 */

#include "readWrite.h"

// Initialise the priorButtons and dpad for checking
uint8_t priorButtons = 0xFF;
uint8_t priorDpad = 0xFF;

// Write the value to the amplifier (Not yet implemented)
void writeAmp(uint8_t ampVal) {}

// Write the values to each LED
void writeLed(int red, int blue, int green) {
  OCR2B = 255 - green;
  OCR0B = 255 - blue;
  OCR0A = 255 - red;
}

// Reading in the first set states for the buttons
uint8_t buttonStates1() {
  uint8_t buttonBytes = 0x00;
  // [0, BC, BP, B5, B4, B3, B2, B1]
  if ((PINC & (1 << B1)) == 0 && debounceCheck(B1, BUT)) {
    buttonBytes |= 1 << 4;
  }
  if ((PINB & (1 << B2)) == 0 && debounceCheck(B2, BUT)) {
    buttonBytes |= 1 << 1;
  }
  if ((PINC & (1 << B3)) == 0 && debounceCheck(B3, BUT)) {
    buttonBytes |= 1 << 2;
  }
  if ((PINC & (1 << B4)) == 0 && debounceCheck(B4, BUT)) {
    buttonBytes |= 1 << 3;
  }
  if ((PINC & (1 << B5)) == 0 && debounceCheck(B5, BUT)) {
    buttonBytes |= 1 << 0;
  }
  if ((PIND & (1 << BP)) == 0 && debounceCheck(BP, BUT)) {
    buttonBytes |= 1 << 5;
  }
  if ((PINB & (1 << BC)) == 0 && debounceCheck(BC, BUT)) {
    buttonBytes |= 1 << 6;
  }

  return buttonBytes;
}

// Reading in the values for each of the joystick states
uint8_t dpadState() {
  uint8_t dpad = 0;
  // [0, 0, 0, 0, JOYR, JOYL, JOYD, JOYU]
  if ((PINB & (1 << JOYU)) == 0 && debounceCheck(JOYU, JOY)) {
    dpad |= 1 << 0;
  }
  if ((PIND & (1 << JOYD)) == 0 && debounceCheck(JOYD, JOY)) {
    dpad |= 1 << 1;
  }
  if ((PINB & (1 << JOYL)) == 0 && debounceCheck(JOYL, JOY)) {
    dpad |= 1 << 2;
  }
  if ((PIND & (1 << JOYR)) == 0 && debounceCheck(JOYR, JOY)) {
    dpad |= 1 << 3;
  }
  return dpad;
}

// Reading in the value for the y axis of the joystick
int joyYState() {
  int joyY = 0;
  // Set the joystick axis
  if ((PINB & (1 << JOYU)) == 0 && debounceCheck(JOYU, JOY)) {
    joyY = 127;
  } else if ((PIND & (1 << JOYD)) == 0 && debounceCheck(JOYD, JOY)) {
    joyY = -127;
  }
  return joyY;
}

// Reading in the value for the x axis of the joystick
int joyXState() {
  int joyX = 0;
  if ((PINB & (1 << JOYL)) == 0 && debounceCheck(JOYL, JOY)) {
    joyX = 127;
  }
  if ((PIND & (1 << JOYR)) == 0 && debounceCheck(JOYR, JOY)) {
    joyX = -127;
  }

  return joyX;
}

// Used for checking the states of the pushbuttons and joystick for debouncing
int debounceCheck(uint8_t button, int mode) {
  uint8_t priorState;
  int pressed = 0;
  if (mode) {
    priorState = priorDpad;
  } else {
    priorState = priorButtons;
  }

  if (priorState & (1 << button)) {
    pressed = 1;
  }

  return pressed;
}
