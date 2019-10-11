/*	Author: Alberto Bengo
 *  Partner(s) Name: Matthew Choi
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #2
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States { init, wait, increment, decrement, reset } States;

int tick(int);

int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	States state = init;

	while (1) {
    state = tick(state);
	}
	return 1;
}

int tick(int state) {
	static unsigned char b = 0x07;
	unsigned char A0 = PINA & 0x01;
  unsigned char A1 = PINA & 0x02;

	switch (state) { // Transitions
	case init:
		state = wait;
		break;

	case wait:
    if (!A1 && A0) {
      state = increment;
    }
    else if (A1 && !A0) {
      state = decrement;
    }
    else if (A1 && A0) {
      state = reset;
    }
    else {
      state = wait;
    }
		break;

	case increment:
    if (A0 && A1) {
      state = reset;
    }
    else {
      state = wait;
    }
		break;

	case decrement:
    if (A0 && A1) {
      state = reset;
    }
    else {
      state = wait;
    }
		break;

	case reset:
    state = wait;
		break;

	default:
		state = init;
		break;
	}

	switch (state) { // Actions
	case init: break;

	case wait: break;

	case increment:
    if (b < 0x09) {
      b = b + 0x01;
    }
		break;

	case decrement:
    if (b > 0x00) {
      b = b - 0x01;
    }
    break;

	case reset:
		b = 0x00;
		break;
	}

	PORTC = b;
	return state;
}
