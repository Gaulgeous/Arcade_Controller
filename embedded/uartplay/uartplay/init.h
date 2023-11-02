/*
 * init.h
 *
 * Created: 19/04/2022 1:01:26 PM
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

#ifndef INIT_H_
#define INIT_H_

volatile int currentMillis;
volatile int previousMillis;

void ledInit();
void timerInit();
void buttonInit();
void joystickInit();

#define BAUDRATE 9600
#define ADDR_BUTTON0 0x00
#define ADDR_BUTTON1 0x01
#define ADDR_JOYSTICK_X 0x02
#define ADDR_JOYSTICK_Y 0x03
#define ADDR_ROT_X 0x04
#define ADDR_ROT_Y 0x05
#define ADDR_ROT_Z 0x06
#define ADDR_DPAD 0x07
#define ADDR_GPO 0x08
#define ADDR_SEND_REPORT 0xFF
#define FIRST_DATA 0
#define SECOND_DATA 1
#define THIRD_DATA 2
#define FOURTH_DATA 3
#define FIFTH_DATA 4
#define UART_INCREMENTS 4
#define SPI_INCREMENTS 5
#define SPI_RESET 100

#endif /* INIT_H_ */