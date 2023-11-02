/*
 * init.h
 *
 * Created: 4/04/2022 1:08:02 PM
 *  Author: gauld
 */ 
// #ifndef LIBRARIES
// #define LIBRARIES
// 
// #define F_CPU 8000000UL
// #include <avr/io.h>
// #include <util/delay.h>
//#include <avr/interrupt.h>
// #endif

#ifndef LIBRARIES
#define LIBRARIES
#define F_CPU 8000000UL
#include <avr/io.h>
#include <util/delay.h>
#include <avr/interrupt.h>
#endif

#ifndef INIT_H_
#define INIT_H_

volatile int currentMillis;

void ledInit();
void timerInit();
void buttonInit();
void joystickInit();

#define JOYU 7
#define JOYD 0
#define JOYL 7
#define JOYR 6
#define B1 1
#define B2 2
#define B3 3
#define B4 4
#define B5 5
#define BC 4
#define BP 2

#endif /* INIT_H_ */