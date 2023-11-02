/*
 * CFile1.c
 *
 * Created: 19/04/2022 1:00:49 PM
 *  Author: gauld
 */ 

#include "coms.h"

// Initialises the SPI
void spiInit() {
	//set MOSI, SCK and SS as output
	DDRB |= (1 << SS) | (1 << SCK) | (1 << MOSI);
	//set SS to high
	PORTB |= (1 << SS);
	//enable master SPI at clock rate Fck/16
	SPCR = (1 << SPE) | (1 << MSTR) | (1 << SPR0);
	
}

// Sends data over SPI. Address is first argument, data is second
uint8_t spiSend(uint8_t address, uint8_t data) {
	
	PORTB &= ~(1 << SS);
	SPDR = address;
	while (!(SPSR &(1<<SPIF)));
	SPDR = data;
	while (!(SPSR &(1<<SPIF)));
	PORTB |= (1 << SS);
	return SPDR;
}

// ISR for incoming UART signals
ISR(USART_RX_vect){
	
	rxBuffer[rxWritePos] = UDR0;
	rxCount++;
	rxWritePos++;
	if(rxWritePos >= RX_BUFFER_SIZE){
		rxWritePos = 0;
	}
}

// ISR for outgoing UART signals
ISR(USART_TX_vect){
	uartTxBusy = 1;
}

// Initialise the UART
void uartInit(uint32_t baud){
	
	baud = (F_CPU/(16*baud)) - 1;
	
	UBRR0H = (baud & 0x0F00) >> 8;
	UBRR0L = (baud & 0x00FF);
	
	UCSR0B |= (1 << TXEN0) | (1 << RXEN0) | (1 << TXCIE0) | (1 << RXCIE0);
	UCSR0C = 0x06;
	
}

// Send a byte of data over UART
void uartSendByte(uint8_t data){
	while(uartTxBusy == 0);
	uartTxBusy = 0;
	UDR0 = data;
}

// Send an array of bytes over UART
void uartSendArray(uint8_t *data,uint16_t length){
	for(uint16_t i = 0; i < length;i++){
		uartSendByte(data[i]);
	}
}

// Send a string of information over UART
void uartSendString(uint8_t *data){
	uint16_t i = 0;
	do{
		uartSendByte(data[i]);
		i++;
		
	}while(data[i] != '\0');
	uartSendByte(data[i]);
}

// return the readCount for UART
uint16_t uartReadCount(void){
	return rxCount;
}

// Read the next incoming byte over UART
uint8_t uartRead(void){
	static uint16_t rxReadPos = 0;
	uint8_t data = 0;
	
	data = rxBuffer[rxReadPos];
	rxReadPos++;
	rxCount--;
	if(rxReadPos >= RX_BUFFER_SIZE){
		rxReadPos = 0;
	}
	return data;
}