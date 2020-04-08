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
	DDRC = 0xFF; PORTC = 0x00;

	unsigned char tempA, cnt;
    /* Insert your solution below */
    while (1) {
	tempA = 0x00;
	cnt = 0x04;
	tempA = PINA;
	tempA = (tempA & 0x0F); //should yield the result of 0000 xxxx where x is the given input
	while(tempA){ //ends only when there are no zeroes...
		if((tempA & 0x01)){
			cnt = cnt - 1;			
		}
		tempA = tempA >> 1;
	}
	PORTC = cnt & 0x0F;
	if((PINA & 0x0F) == 0x0F){
		PORTC = PORTC | 0x80;
	}
     }
    return 1;
}
