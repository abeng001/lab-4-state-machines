/*	Author: Alberto Bengo
 *  Partner(s) Name: Matthew Choi
 *	Lab Section: 23
 *	Assignment: Lab #4  Exercise #3
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

typedef enum States { start, wait, PA2_press, PA2_release, Y_press, Y_release, Lock_press } States;

int tick(int);

int main(void) {

	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;

	States state = start;
	while (1) {
		state = tick(state);
	}
	return 1;
}

int tick(int state) {
	static unsigned char pb0;
	//static unsigned char A0 = 0x01; //used in later exercises
	static unsigned char A1 = 0x02;
	static unsigned char A2 = 0x04;
	static unsigned char A7 = 0x80;
	unsigned char input = PINA & 0xFF;

	switch (state) { // Transitions
	case start:
		state = wait;
		break;
	case wait:
		state = (input == A2) ? PA2_press : wait;
		break;
	case PA2_press:
		if (input == A2) {
			state = PA2_press;
		}
		else if (input == 0x00) {
			state = PA2_release;
		}
		else {
			state = wait;
		}
		break;
	case PA2_release:
		if (input == A1) {
			state = Y_press;
		}
		else if (input == 0x00) {
			state = PA2_release;
		}
		else {
			state = wait;
		}
		break;
	case Y_press:
		if (input == A1) {
			state = Y_press;
		}
		else if (input == 0x00) {
			state = Y_release;
		}
		else {
			state = wait;
		}
		break;
	case Y_release:
		if (input == A7) {
			state = Lock_press;
		}
		else {
			state = Y_release;
		}
		break;
	case Lock_press:
		if (input == 0x00) {
			state = wait;
		}
		else {
			state = Lock_press;
		}
		break;
	default:
		state = start;
		break;
	}
	switch (state) { // Actions
	case start: break;
	case wait:
		pb0 = 0x00;
		break;
	case PA2_press: break;
	case PA2_release: break;
	case Y_press: break;
	case Y_release:
		pb0 = 0x01;
		break;
	case Lock_press: break;
	}
	PORTB = pb0;
	PORTC = state;
	return state;
}
