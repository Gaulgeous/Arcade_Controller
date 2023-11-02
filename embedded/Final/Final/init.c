/*
 * init.c
 *
 * Created: 19/04/2022 1:01:37 PM
 *  Author: gauld
 */

#include "init.h"

// Initalise the LED ports and set them to an off state
void ledInit() {

  // output OCOA, OCOB, OC2B
  DDRD |= (1 << 3) | (1 << 5) | (1 << 6);

  // WGM0 = 011, COM0A = COM0B = 11, CS0 = 001
  TCCR0A = (1 << COM0A0) | (1 << COM0A1) | (1 << COM0B0) | (1 << COM0B1) |
           (1 << WGM00) | (1 << WGM01);
  TCCR0B = (1 << CS00);

  // WGM2 = 011, COM2B = 11, CS2 = 001
  TCCR2A = (1 << COM2B0) | (1 << COM2B1) | (1 << WGM20) | (1 << WGM21);
  TCCR2B = (1 << CS20);

  // Set everything to 0 to start
  OCR0A = 0; // lower starting bound
  OCR0B = 0; // upper starting bound
  OCR2B = 0; // upper starting bound
}

// Initialise timer 1 to run on 1ms timer interrupts
void timerInit() {

  TCCR1B = (1 << WGM12);
  OCR1A = 125;
  TIMSK1 = (1 << OCIE1A);

  TCCR1B |= (1 << CS11) | (1 << CS10);
}

// Initalise each of the buttons to be normally closed inputs, and configured to
// an internal pullup resistor
void buttonInit() {

  DDRD &= ~(1 << BP);
  DDRC &= ~((1 << B1) | (1 << B3) | (1 << B4) | (1 << B5));
  DDRB &= ~((1 << B2) | (1 << BC));

  PORTD |= (1 << BP);
  PORTC |= (1 << B1) | (1 << B3) | (1 << B4) | (1 << B5);
  PORTB |= (1 << B2) | (1 << BC);
}

// Initialise each of the joystick ports to be normally open inputs
void joystickInit() {

  DDRB &= ~((1 << JOYU) | (1 << JOYL));
  DDRD &= ~((1 << JOYD) | (1 << JOYR));

  PORTB |= (1 << JOYU) | (1 << JOYL);
  PORTD |= (1 << JOYD) | (1 << JOYR);
}

// Increases the timer count by 1
ISR(TIMER1_COMPA_vect) { currentMillis++; }
