/*	Author: Alberto Bengo
 *  Partner(s) Name: Matthew Choi
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #1
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States { start, wait, PB1_On, release_PB1_On, PB0_On } States;

int tick(int);

int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;

	States state = start;
	while (1) {
    state = tick(state);
	}
	return 1;
}

int tick(int state) {
	static unsigned char b;
	unsigned char A0 = PINA & 0x01;
	switch (state) { // Transitions
	case start:
		state = wait;
		break;
	case wait:
		state = A0 ? PB1_On : wait;
		break;
	case PB1_On:
		state = A0 ? PB1_On : release_PB1_On;
		break;
	case release_PB1_On:
		state = A0 ? PB0_On : release_PB1_On;
		break;
	case PB0_On:
		state = A0 ? PB0_On : wait;
		break;
	default:
		state = start;
		break;
	}
	switch (state) { // Actions
	case start: break;
	case wait:
		b = 0x01;
		break;
	case PB1_On:
		b = 0x02;
		break;
	case release_PB1_On: break;
	case PB0_On:
		b = 0x01;
		break;
	}
	PORTB = b;
	return state;
}
