/*
 * coms.h
 *
 * Created: 19/04/2022 1:01:09 PM
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

#ifndef COMS_H_
#define COMS_H_

// Defined values
#define MOSI 3
#define SCK 5
#define SS 2
#define RX_BUFFER_SIZE 128
#define START 0x08
#define ADDRESS 0x2C
#define ADDRESS_ACK 0x18
#define DATA_ACK 0x28

// Variables
volatile static uint8_t rxBuffer[RX_BUFFER_SIZE] = {0};
volatile static uint16_t rxCount = 0;
volatile static uint8_t uartTxBusy = 1;
volatile static uint16_t rxWritePos = 0;
volatile static int uartCounter;
volatile static int spiCounter;

// Functions
void spiInit();
uint8_t spiSend(uint8_t address, uint8_t data);
void uartInit(uint32_t baud);
void uartSendByte(uint8_t data);
void uartSendArray(uint8_t *data, uint16_t length);
void uartSendString(uint8_t *data);
uint16_t uartReadCount(void);
uint8_t uartRead(void);
void i2cInit();
void i2cSendVolume(uint8_t volume);
void i2cSendAddress();
void i2cSendStart();
void i2cSendStop();
void ERROR();

#endif /* COMS_H_ */
