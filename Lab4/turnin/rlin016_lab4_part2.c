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

enum States{Start, Wait, WaitStatus, Up, Down, Reset} state;
unsigned char tempA, tempC;
void Tick();

int main(void) {
	DDRA = 0x00; PINA = 0x00;
	DDRC = 0xFF; PORTC = 0x00;

	state = Start;
	tempC = 7;
    while (1){
	tempA = PINA;
	Tick();
	PORTC = tempC;
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
			if((tempA & 0x03) == 0x03){
				state = Reset;
			}
			else if(tempA & 0x01){
				state = Up;
			}
			else if(tempA & 0x02){
				state = Down;
			}
			break;
		case Reset:
			state = Wait;
			break;
		case Up:
		case Down:
			if((tempA & 0x03) == 0x03){
				state = Reset;
			}
			else if(tempA & 0x00){
				state = Wait;
			}
			else{
				state = WaitStatus;
			}
			break;
		case WaitStatus:
			if(tempA == 0x00){
				state = Wait;
			}			
			break;
	}
	switch (state){
		case Start:
			break;
		case Wait:
			break;
		case Reset:
			tempC = 0;
			break;
		case Up:
			if(tempC < 9){
				tempC = tempC + 1;
			}
			break;
		case Down:
			if(tempC > 0){
				tempC = tempC - 1;
			}
			break;
		case WaitStatus:
			break;		
	}
};
