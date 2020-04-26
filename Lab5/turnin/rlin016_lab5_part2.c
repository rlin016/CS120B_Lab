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

enum States{Start, Wait, UpPress, UpRelease, DownPress, DownRelease, Reset} state;
unsigned char tempA, tempC;
void Tick();

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;

	state = Start;
	tempC = 0x00;
    while (1){
	tempA = ~PINA;
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
			if((tempA & 0x03) == 0x01){
				state = UpPress;
				break;
			}
			else if((tempA & 0x03) == 0x02){
				state = DownPress;
				break;
			}
			else if((tempA & 0x03) == 0x03){
				state = Reset;
				break;
			}
			break;
		case UpPress:
			if((tempA & 0x03) == 0x03){
				state = Reset;
				break;
			}
			state = UpRelease;
			break;
		case UpRelease:
			if((tempA & 0x03) == 0x03){
				state = Reset;
			}
			else if(!(tempA & 0x01)){
				state = Wait;
			}
			break;
		case DownPress:
			if((tempA & 0x03) == 0x03){
				state = Reset;
				break;
			}
			state = DownRelease;
			break;
		case DownRelease:
			if((tempA & 0x03) == 0x03){
				state = Reset;
			}
			else if(!(tempA & 0x02)){
				state = Wait;
			}
			break;
		case Reset:
			state = Wait;
			break;

	}
	switch (state){
		case Start:
		case Wait:
		case UpRelease:
		case DownRelease:
			break; 
		case Reset:
			tempC = 0;
			break;
		case UpPress:
			if(tempC < 9){
				tempC = tempC + 1;
			}
			break;
		case DownPress:
			if(tempC > 0){
				tempC = tempC - 1;
			}
			break;		
	}
};
