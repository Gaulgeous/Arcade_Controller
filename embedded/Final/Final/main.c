/*
 * Final.c
 *
 * Created: 11/05/2022 10:49:23 AM
 * Author : gauld
 */

/*
 * uartplay.c
 *
 * Created: 19/04/2022 10:31:18 AM
 * Author : gauld
 */
#ifndef SETUP
#define SETUP
#define F_CPU 8000000UL

#include <avr/interrupt.h>
#include <avr/io.h>
#include <stdint.h>
#include <util/delay.h>
#endif

#include "coms.h"
#include "flash.h"
#include "init.h"
#include "readWrite.h"

void stateInit();
void handleUart();
void handleSpi();
void variableInit();

int main(void) {

  // Initialise each of the internal firmwares
  variableInit();
  i2cInit();
  uartInit(BAUDRATE);
  spiInit();
  ledInit();
  buttonInit();
  joystickInit();
  timerInit();
  stateInit();

  // Enable interrupts
  sei();

  // Main loop
  while (1) {
    // Check for UART input
    handleUart();
    // Send button states over SPI
    handleSpi();
  }
  return 0;
}

// Controls the initialisation of the system's peripherals
void stateInit() {
  // Read the states of the LEDs, amp and dpad
  redLed = eepromRead(FLASH_OFFSET_RED);
  blueLed = eepromRead(FLASH_OFFSET_BLUE);
  greenLed = eepromRead(FLASH_OFFSET_GREEN);
  dpadAmp = eepromRead(FLASH_OFFSET_DPAD);
  int amp = dpadAmp & 0x7F;
  joyMode = dpadAmp & (1 << 7);

  // Write each of the values into their corresponding peripheral
  writeLed(redLed, blueLed, greenLed);
  i2cSendVolume(amp);
}

// Initialise variables that will be used
void variableInit() {

  previousMillis = 0;
  uartCounter = 0;
  redLed = 0;
  blueLed = 0;
  greenLed = 0;
  dpadAmp = 0;
  spiCounter = 0;
}

// Handles the incoming UART signals, as well as sending the pushbutton states
// In response
void handleUart() {
  // Check if there's input
  if (uartReadCount() > 0) {
    if (uartCounter == FIRST_DATA) {
      redLed = uartRead();
      uartCounter++;

    } else if (uartCounter == SECOND_DATA) {
      blueLed = uartRead();
      uartCounter++;

    } else if (uartCounter == THIRD_DATA) {
      greenLed = uartRead();
      uartCounter++;

    } else if (uartCounter == FOURTH_DATA) {
      dpadAmp = uartRead();
      uartCounter++;
    }

    // When all the input is received, write it into the registers and send back
    // button states
    if (uartCounter == UART_INCREMENTS) {
      writeLed(redLed, blueLed, greenLed);
      int amp = dpadAmp & 0x7F;
      joyMode = dpadAmp & (1 << 7);
      i2cSendVolume(amp);
      // todo implement the change in the pot!
      eepromWrite(FLASH_OFFSET_RED, redLed);
      eepromWrite(FLASH_OFFSET_BLUE, blueLed);
      eepromWrite(FLASH_OFFSET_GREEN, greenLed);
      eepromWrite(FLASH_OFFSET_DPAD, dpadAmp);

      uint8_t buttonByte = buttonStates1();
      uint8_t dpad = dpadState();

      uartSendByte(buttonByte);
      uartSendByte(dpad);

      uartCounter = 0;
    }
  }
}

// Sends out the SPI signal to be read by the USB HID system
void handleSpi() {
  // Ready to read states
  if (currentMillis - previousMillis >= POLL_TIME) {
    // Reset phantom button presses
    if (spiCounter % SPI_RESET == 0) {
      uint8_t addresses[FIFTH_DATA] = {ADDR_ROT_X, ADDR_ROT_Y, ADDR_ROT_Z,
                                       ADDR_GPO};

      for (int i = 0; i < FIFTH_DATA; i++) {
        while (currentMillis - previousMillis < POLL_TIME)
          ;
        spiSend(addresses[i], 0x00);
        previousMillis = currentMillis;
      }
      // Send off useful information
    } else if (spiCounter % SPI_INCREMENTS == FIRST_DATA) {
      uint8_t buttonByte = buttonStates1();
      spiSend(ADDR_BUTTON0, buttonByte);

    } else if (spiCounter % SPI_INCREMENTS == SECOND_DATA) {
      if (joyMode) {
        int joyX = joyXState();
        spiSend(ADDR_JOYSTICK_X, joyX);

      } else {
        spiSend(ADDR_JOYSTICK_X, 0x00);
      }
    } else if (spiCounter % SPI_INCREMENTS == THIRD_DATA) {
      if (joyMode) {
        spiSend(ADDR_DPAD, 0x00);
      } else {
        uint8_t dpad = dpadState();
        spiSend(ADDR_DPAD, dpad);
      }
    } else if (spiCounter % SPI_INCREMENTS == FOURTH_DATA) {
      if (joyMode) {
        int joyY = joyYState();
        spiSend(ADDR_JOYSTICK_Y, joyY);

      } else {
        spiSend(ADDR_JOYSTICK_Y, 0x00);
      }
    } else if (spiCounter % SPI_INCREMENTS == FIFTH_DATA) {
      spiSend(ADDR_SEND_REPORT, 0x01);
    }
    // Increment and extend timer counters
    spiCounter++;
    previousMillis = currentMillis;
  }
}
