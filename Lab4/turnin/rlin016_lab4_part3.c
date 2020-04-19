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

enum States{Start, Wait, SharpPress, Unlock, Lock} state;
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
			state = Wait;
			break;
		case Wait:
			if(tempA == 0x04){
				state = SharpPress;
			}
			else if((tempA & 0x80) == 0x80){
				state = Lock;
			}
			break;
		case SharpPress:
			if(tempA == 0x02){
				state = Unlock;
			}
			else if(tempA == 0x04){
				state = SharpPress;
			}
			else if((tempA & 0x80) == 0x80){
				state = Lock;
			}
			else{
				state = Wait;
			}
			break;
		case Unlock:
			if((tempA & 0x80) == 0x80){
				state = Lock;
			}
			break;
		case Lock:
			state = Wait;
			break;
	}
	switch(state){
		case Start:
		case Wait:
		case SharpPress:
			break;
		case Unlock:
			tempB = 0x01;
			break;
		case Lock:
			tempB = 0x00;
			break;
	}
};
