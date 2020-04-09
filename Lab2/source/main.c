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
	DDRC = 0x00; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;

	unsigned char tempA, tempB, tempC;
    /* Insert your solution below */
    while (1) {
	tempA = PINA;
	tempB = PINB;
	tempC = PINC;
	
	if(tempA > 140 || tempB > 140 || tempC > 140){
		PORTD = PORTD | 0x01;
	}
	else if(((tempA + tempB) > 140) || ((tempA + tempC) > 140) || ((tempB + tempC) > 140)){
		PORTD = PORTD | 0x01;
	}
	else if((tempA + tempB + tempC) > 140){
		PORTD = PORTD | 0x01;
	}
	
	
     }
    return 1;
}
