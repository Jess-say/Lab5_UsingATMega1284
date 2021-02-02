/*	Author: Jessie Lu
 *  Partner(s) Name: 
 *	Lab Section: 23
 *	Assignment: Lab #5  Exercise #1
 *	Exercise Description: Continues from exercise 2. Add extra inputs for key is in ignition, driver is seated, driver's seatbelt is fastened. PC7 should light if key is in ignition, driver is seated but belt isn't fastened.
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char led = 0x00;
	unsigned char button = 0x00;
    	while (1) {
		button = ~PINA & 0x0F;
	 	led = 0x00;

		// fuel tank is 1-2
		if (button == 0x01 || button == 0x02) { 
			led =  0x60; // low fuel tank light (PC6) and PC5
		}
		else if (button == 0x03 || button == 0x04) {
			led = 0x70;
		}
		else if (button == 0x05 || button == 0x06) {
			led = 0x38;
		}
		else if (button == 0x07 || button == 0x08 || button == 0x09) {
			led = 0x3C;
		}
		else if (button == 0x0A || button == 0x0B || button == 0x0C) {
			led = 0x3E;
		}
		else if (button == 0x0D || button == 0x0E || button == 0x0F) {
			led = 0x3F;
		}
		else {
			led = 0x40;
		}

		PORTC = led;
    	}
    	return 0;
}
