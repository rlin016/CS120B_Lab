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
	unsigned tempA, tempB, cnt;
    while (1) {
	tempA = PINA;
	tempB = PINB;
	cnt = 0x00;
	while(tempA){
		if(tempA & 0x01){
			cnt = cnt + 1;
		}
		tempA = tempA >> 1;
	}
	while(tempB){
		if(tempB & 0x01){
			cnt = cnt + 1;
		}
		tempB = tempB >> 1;
	}
	PORTC = cnt;
    }
    return 1;
}
