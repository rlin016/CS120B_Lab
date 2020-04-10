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
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0x000; PORTD = 0x00;
    /* Insert your solution below */
	unsigned short tempD;
	while(1){
		tempD = PORTD;
		if(tempD >= 70){
			PORTB = PORTB | 0x02;
		}
		else if(tempD > 5){
			PORTB = PORTB | 0x04;
		}	
    	}	
	return 1;
}
