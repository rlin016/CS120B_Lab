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
	DDRB = 0xF0; PORTB = 0x00;
	DDRD = 0x00; PORTD = 0x00;
    /* Insert your solution below */
	unsigned short input, output;
	
	while(1){
		output = 0x00;
		input = (PIND << 1) | (PORTB & 0x01);
		if(input >= 70){
			output = 0x02;
		}
		else if(input > 5){
			output = 0x04;
		}
		PORTB = output;	
	}	
	return 1;
}
