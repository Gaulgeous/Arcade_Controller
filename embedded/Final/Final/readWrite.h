/*
 * readWrite.h
 *
 * Created: 19/04/2022 1:02:01 PM
 *  Author: gauld
 */

#ifndef SETUP
#define SETUP
#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#endif

// Button definitions
#ifndef BUTTONS
#define BUTTONS

#define JOYU 0
#define JOYD 2
#define JOYL 6
#define JOYR 7
#define B1 1
#define B2 1
#define B3 0
#define B4 2
#define B5 3
#define BC 7
#define BP 4

#endif

#ifndef READWRITE_H_
#define READWRITE_H_

// Time for polling
#define POLL_TIME 5
#define BUT 0
#define JOY 1

// Storing values
uint8_t redLed;
uint8_t greenLed;
uint8_t blueLed;
uint8_t dpadAmp;

// Functions
void writeLed(int red, int blue, int green);
void writeAmp(uint8_t ampVal);
uint8_t buttonStates1();
uint8_t dpadState();
int joyYState();
int joyXState();
int debounceCheck(uint8_t button, int mode);

#endif /* READWRITE_H_ */
