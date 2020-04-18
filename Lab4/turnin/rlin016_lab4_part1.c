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
unsigned char tempA, tempB;
void Tick();

int main(void) {
	DDRA = 0x00; PINA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;

	state = Start;
    while (1){
	tempA = PINA;
	Tick();
	PORTB = tempB;
    }
    return 1;
}

void Tick(){
//	tempA = PINA;
//	tempB = 0x00;
	
//	tempB = tempA;
	switch(state){
		case Start:
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
			tempB = 0x02;
			break;			
		case OneOn:
			tempB = 0x02;
			break;
		case OnePress:
			tempB = 0x01;
			break;
		default:
			tempB = 0x00;
			break;
	}
//	PORTB = tempB;
};
