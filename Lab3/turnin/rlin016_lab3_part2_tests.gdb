/*	Author: rlin016
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#endif

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0x00; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below 
 */	while(1){
	unsigned tempA;
	tempA = PINA & 0x0F;
	PORTC = 0x00;
	switch(tempA){
		case 15: 
		case 14:
		case 13:
			PORTC = PORTC | 0x01;
		case 12:
		case 11:
		case 10:
			PORTC = PORTC | 0x02;
		case 9:
		case 8:
		case 7:
			PORTC = PORTC | 0x04;
		case 6:
		case 5:
			PORTC = PORTC | 0x08;
		case 4:
		case 3:
			PORTC = PORTC | 0x10;
		case 2:
		case 1:
			PORTC = PORTC | 0x20;
			break;
	}

	if(!(PORTC & 0x02)){
		PORTC = PORTC | 0x40;
	}
    }
    return 1;
}
