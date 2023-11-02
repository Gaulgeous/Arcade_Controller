/*
 * readWrite.h
 *
 * Created: 19/04/2022 1:02:01 PM
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

#ifndef BUTTONS
#define BUTTONS

#define JOYU 2
#define JOYD 0
#define JOYL 7
#define JOYR 6
#define B1 3
#define B2 1
#define B3 0
#define B4 2
#define B5 1
#define BC 7
#define BP 4

#endif

#ifndef READWRITE_H_
#define READWRITE_H_

#define POLL_TIME 10

uint8_t redLed;
uint8_t greenLed;
uint8_t blueLed;
uint8_t dpadAmp;

void writeLed(int red, int blue, int green);
void writeAmp(uint8_t ampVal);
uint8_t buttonStates1();
uint8_t dpadState();
int joyYState();
int joyXState();

#endif /* READWRITE_H_ */