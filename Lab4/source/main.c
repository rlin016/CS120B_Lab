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

enum States{Start, ZeroOn, ZeroPress, OneOn, OnePress} state, next_state;

void Tick();

int main(void) {
	DDRA = 0xFF; PINA = 0x00;
	DDRB = 0x00; PORTB = 0x00;
	state = Start;
    while (1){
	Tick();
    }
    return 1;
}

void Tick(){
	unsigned tempA, tempB;
	tempA = PINA;
	tempB = PORTB;
	switch(state){
		case Start:
			next_state = ZeroOn;
			break;
		case ZeroOn:
			if(tempA & 0x01){
				next_state = ZeroPress;
			}
			else{
				next_state = ZeroOn;
			}
			break;
		case ZeroPress:
			if(!(tempA & 0x01)){
				next_state = OneOn;
			}
			else{
				next_state = ZeroPress;
			}
			break;
		case OneOn:
			if(tempA & 0x01){
				next_state = OnePress;
			}
			else{
				next_state = OneOn;
			}
			break;
		case OnePress:
			if(!(tempA & 0x01)){
				next_state = ZeroOn;
			}
			else{
				next_state = OnePress;
			}
			break;
		default:
			next_state = ZeroOn;
			break;
	}
	switch (state){
			case Start:
				tempB = 0x00;
				break;
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
				break;
			default:
				tempB = 0x00;
				break;
	}
	state = next_state;
	PORTB = tempB;
};
