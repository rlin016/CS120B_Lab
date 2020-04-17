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

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0xFF; PINA = 0x00;
	DDRB = 0x00; PORTB = 0x00;
//	unsigned char tempA, tempB;
    /* Insert your solution below */
    while (1) {
	Tick();
    }
    return 1;
}

void Tick(){
//	DDRA = 0xFF; PINA = 0x00;
//	DDRB = 0x00; PORTB = 0x00;
	unsigned tempA, tempB;
	tempA = PINA;
	tempB = PORTB;
	switch(state){

		state = ZeroOn;
		break;
	case ZeroOn:
		if(tempA & 0x01){
			state = ZeroPress;
		}
		break;
	case ZeroPress:
		if(!(tempA & 0x01)){
			state = OneOn;
		}
		break;
	case OneOn:
		if(tempA & 0x01){
			state = OnePress;
		}
		break;
	case OnePress:
		if(!(tempA & 0x01)){
			state = ZeroOn;
		}
		break;
	default:
		state = ZeroOn;
		break;
	}
	switch (state){
		case ZeroOn:
			tempB = 0x01;
			break;
		case ZeroPress:
			tempB = 0x01;
			break;
		case OneOn:
			tempB = 0x02;
			break;
		case OnePress:
			tempB = 0x02;
		default:
			tempB = 0x00;
			break;
	}
	PORTB = tempB;
};
