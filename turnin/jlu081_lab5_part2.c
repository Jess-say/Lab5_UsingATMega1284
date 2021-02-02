/*	Author: Jessie Lu
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #5  Exercise #2
 *	Exercise Description: Output for PORTC is initially 7, pressing PA0 increments PORC once and stops at 9. Pressing PA1 decrements PORTC once and stops at 0. If both buttons are depressed PORTC is set to 0. Buttons should be released before additional inc or dec.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

unsigned char C = 0x07; // initially set to 7
unsigned char prev;
unsigned char button;

enum States { Start, Wait, Inc, Dec, Inc_Wait, Dec_Wait, Depress, Reset } State;

void Button() {
	switch(State) { //Transistion
		case Start: // initial transition
			State = Wait;
			break;

		case Wait:
			// if A0 is pressed - increment
			if (button == 0x01) {
				State = Inc_Wait;
			}
			// decrement if A1 is pressed
			else if (button == 0x02) {
				State = Dec_Wait;
			}
			// if both A0 and A1 are pressed - reset
			else if (button == 0x03) {
				State = Reset;
			}
			// if no buttons are pressed
			else {
				State = Wait;
			}
			break;

		case Inc:
			prev = Inc;
			if (button == 0x01) { 
				State = Inc;
			}
			else if (button == 0x02) {
				State = Dec_Wait;
			}
			else if (button == 0x03) {
				State = Reset;
			}
			else {
				State = Depress;
			}
			break;

		case Dec:
			if (button == 0x01) {
				State = Inc_Wait;
			}
			else if (button == 0x02) {
				State = Dec;
			}
			else if (button == 0x03) {
				State = Reset;
			}
			else {
				State = Depress;
			}
			break;

		case Inc_Wait:
			State = Inc;
			break;

		case Dec_Wait:
			State = Dec;
			break;

		case Reset:
			if (button == 0x00) {
				State = Depress;
			}
			else if (button == 0x01) {
				State = Inc_Wait;
			}
			else if (button == 0x02) {
				State = Dec_Wait;
			}

			else {
				State = Wait;
			}
			break;

		case Depress:
			if (button == 0x01) {
				State = Inc_Wait;
			}
			else if (button == 0x02) {
				State = Dec_Wait;
			}
			else if (button == 0x03) {
				State = Reset;
			}
			else {
				State = Depress;
			}
			break;

		default:
			break;
	}

	switch(State) {
		case Start:
			C = 0x07; // Initially
			break;

		case Inc_Wait:
			if (C < 9) {
				C = C + 1;
			}
			break;

		case Dec_Wait:
			if (C > 0) {
				C = C - 1;
			}
			break;

		case Reset:
			C = 0x00;
			break;

		default:
			break;

	}
}

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
 
	State = Start;

	while (1) {
		button = ~PINA & 0x03; // gets PA0 and PA1
		Button();
		PORTC = C;
    	}	

    	return 0;
}
