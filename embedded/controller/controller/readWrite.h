/*
 * readWrite.h
 *
 * Created: 4/04/2022 1:41:36 PM
 *  Author: gauld
 */ 

#ifndef LIBRARIES
#define LIBRARIES
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#endif

#ifndef READWRITE_H_
#define READWRITE_H_

int redLed;
int greenLed;
int blueLed;
int dpadAmp;

void writeLed(int red, int blue, int green);
void writeAmp(uint8_t ampVal);
uint8_t buttonStates1();
uint8_t buttonStates2();
uint8_t dpadState();
int joyYState();
int joyXState();

#define DEBOUNCE_TIME 50

#endif /* READWRITE_H_ */