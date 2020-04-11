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
    /* Insert your solution below */
	unsigned tempA, outC;
	
	while(1){
		tempA = PINA & 0x0F;
		outC = 0x00;
		switch (tempA){
			case 15:
			case 14:
			case 13:
				outC = outC | 0x01;
			case 12:
			case 11:
			case 10:
				outC = outC | 0x02;
			case 9:
			case 8:
			case 7:
				outC = outC | 0x04;
			case 6:
			case 5:
				outC = outC | 0x08;
			case 4:
			case 3:
				outC = outC | 0x10;
			case 2:
			case 1:
				outC = outC | 0x20;
				break;
		}
		if(!(outC & 0x08)){
			outC = outC | 0x40;
		}
		tempA = PINA;
		if(!(tempA & 0x40) && (tempA & 0x20) && (tempA & 0x10)){
			outC = outC | 0x80;
		}
		PORTC = outC;
	}	
		
	return 1;
}
