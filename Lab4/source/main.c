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
//#include "RIMS.h"
#endif

enum States{Start, ZeroOn, ZeroPress, OneOn, OnePress} state;

void Tick(){
	switch(state){
		case Start: 
			state = ZeroOn; 
			break;
		case ZeroOn:
			if(A0){
				state = ZeroPress;
			}
			break;
		case ZeroPress:
			if(!A0){
				state = OneOn;
			}
			break;
		case OneOn:
			if(A0){
				state = OnePress;
			}
			break;
		case OnePress:
			if(!A0){
				state = ZeroOn;
			}
			break;
		default:
			state = ZeroOn;
			break;
	}
	switch(state){
		case ZeroOn:
			B = 0x01;
			break;
		case ZeroPress:
			B = 0x01;
			break;
		case OneOn:
			B = 0x02;
			break;
		case OnePress:
			B = 0x02;
			break;
		default: 
			B = 0x00;
			break;
	}
};

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xFF; PINA = 0x00;
	DDRB = 0x00; PORTB = 0x00; 
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}
