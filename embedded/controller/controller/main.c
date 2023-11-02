/*
 * controller.c
 *
 * Created: 4/04/2022 10:34:59 AM
 * Author : gauld
 */ 

// #define F_CPU 8000000UL
// 
// #include <avr/io.h>
// #include <util/delay.h>
// #include <avr/interrupt.h>

#include "init.h"
#include "readWrite.h"
#include "flash.h"
#include "communications.h"

#define POLLTIME 60
#define BAUDRATE 9600

void stateInits();

int main(void) {
	currentMillis = 0;
	int previousMillis = 0;
	int uartCounter = 0;
	sei();
	ledInit();
	spiInit();
	uart_init(BAUDRATE);
	buttonInit();
	joystickInit();
	stateInits();
	timerInit();
	
    while (1) {
		
		if(uart_read_count() > 0) {
			if (uartCounter == 0) {
				redLed = uart_read();
				uart_send_byte(redLed);
			} else if (uartCounter == 1) {
				blueLed = uart_read();
			} else if (uartCounter == 2) {
				greenLed = uart_read();
			} else if (uartCounter == 3) {
				dpadAmp = uart_read();
			}
			uartCounter++;
			if (uartCounter == 4) {
				writeLed(redLed, blueLed, greenLed);
				joyMode = dpadAmp & (1 << 7);
				writeAmp(dpadAmp & 0x7F);
				eepromWrite(FLASHOFFSET, dpadAmp);
				eepromWrite(FLASHOFFSET + 1, redLed);
				eepromWrite(FLASHOFFSET + 2, blueLed);
				eepromWrite(FLASHOFFSET + 3, greenLed);
				uart_send_byte(redLed);
				uart_send_byte(blueLed);
				uart_send_byte(greenLed);
				uart_send_byte(dpadAmp);
				uartCounter = 0;
			}
		}
		
		if (currentMillis - previousMillis >= POLLTIME) {
			
			uint8_t buttonBytes1 = buttonStates1();
			uint8_t buttonBytes2 = buttonStates2();
			
			// Address destinations for each of those buttons bytes
			spiSend(0x00, buttonBytes1);
			spiSend(0x01, buttonBytes2);
			
			// If it's in DPAD mode
			if (joyMode) {
				// DPAD needs to send to address 0x07
				uint8_t dpad = dpadState();
				spiSend(0x07, dpad);
			// Or in joystick mode
			} else {
				int joyX = joyXState();
				int joyY = joyYState();	
				// 0x03 for Y axis, 0x02 for X axis
				spiSend(0x03, joyY);
				spiSend(0x02, joyX);
			}
			previousMillis = currentMillis;
		}
    }
}

void stateInits() {
	int dAmp = eepromRead(FLASHOFFSET);
	joyMode = dAmp & (1 << 7);
	ampFlash = dAmp & 0x7F;
	redFlash = eepromRead(FLASHOFFSET + 1);
	blueFlash = eepromRead(FLASHOFFSET + 2);
	greenFlash = eepromRead(FLASHOFFSET + 3);
	writeLed(redFlash, blueFlash, greenFlash);
	writeAmp(ampFlash);
}

