/*	Author: rlin016
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Video Link: https://youtu.be/vFOmcOTMNFs
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
//#include "RIMS.h"
#include "timer.h"
#endif

enum States{Start, Wait, UpPress, DownPress, Reset, UpRotate, DownRotate} state;
unsigned char tempA, tempC, timeWait;
void Tick();

int main(void) {
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(100);
	TimerOn();
	state = Start;
	tempC = 0x07;
    while (1){
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    return 1;
}

void Tick(){
	tempA = ~PINA;

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
			else if((tempA & 0x03) == 0x01){
				timeWait = 0;
				state = UpRotate;
				break;
			}
			else{
				state = Wait;
				break;
			}
		case DownPress:
			if((tempA & 0x03) == 0x03){
				state = Reset;
				break;
			}
			else if((tempA & 0x03) == 0x02){
				timeWait = 0;
				state = DownRotate;
				break;
			}
			else{
				state = Wait;
				break;
			}
		case Reset:
			state = Wait;
			break;
		case UpRotate:
			if((tempA & 0x03) == 0x01){
				state = UpRotate;
				break;
			}
			else{
				state = Wait;
				break;
			}
		case DownRotate:
			if((tempA & 0x03) == 0x02){
				state = DownRotate;
				break;
			}
			else{
				state = Wait;
				break;
			}			

	}
	switch (state){
		case Start:
		case Wait:
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
		case UpRotate:
			if(timeWait == 0x0A){
				tempC = tempC + 1;
				timeWait = 0;
			}
			else{
				timeWait++;
			}
			break;
		case DownRotate:
			if(timeWait == 0x0A){
				tempC = tempC - 1;
				timeWait = 0;
			}
			else{
				timeWait++;
			}
			break;
				
	}
	PORTB = tempC;
};
