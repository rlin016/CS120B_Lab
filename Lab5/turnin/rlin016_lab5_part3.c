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

enum States{Start, StartRelease, LightOne, LightOneRelease, LightTwo, LightTwoRelease, LightThree, LightThreeRelease, LightFour} state;

unsigned char tempA, tempC, reverse;

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRC = 0xFF; PORTC = 0x00;
    /* Insert your solution below */
	state = Start;
	while(1){
		Tick();	
	}
	return 1;
}

//when reverse is 0, you go FORWARD, when reverse is 1, you got BACKWARDs

void Tick(){
	tempA = ~PINA;
	tempC = 0x00;
	switch(state){
		case Start:
			if(tempA & 0x01){
				state =	StartRelease;
			}
			break;
		case StartRelease:
			if(!(tempA & 0x01)){
				state = LightOne;
			}
			break;
		case LightOne:
			if(tempA & 0x01){
				state = LightOneRelease;
			}
			break;
		case LightOneRelease:
			if(!(tempA & 0x01)){
				if(reverse){
					state = LightOne;
				}
				else{
					state = LightTwo;
				}
			}
			break;
		case LightTwo:
			if(tempA & 0x01){
				if(reverse){
					state = LightOneRelease;
				}
				else{
					state = LightTwoRelease;
				}
			}
			break;
		case LightTwoRelease:
			if(!(tempA & 0x01)){
				if(reverse){
					state = LightTwo;
				}
				else{
					state = LightThree;
				}
			}
			break;
		case LightThree:
			if(tempA & 0x01){
				if(reverse){
					state = LightTwoRelease;
				}
				else{
					state = LightThreeRelease;
				}
			}
			break;
		case LightThreeRelease:
			if(!(tempA & 0x01)){	
				if(reverse){
					state = LightThree;
				}
				else{
					state = LightFour;
				}
			}
			break;
		case LightFour:
			if(tempA & 0x01){
				state = LightThreeRelease;
			}
			break;
	}

	switch(state){
		case Start:
		case StartRelease:
		case LightOneRelease:
		case LightTwoRelease:
		case LightThreeRelease:
			break;
		case LightOne:
			reverse = 0;
			tempC = 0x05;
			break;
		case LightTwo:
			tempC = 0x0A;
			break;
		case LightThree:
			tempC = 0x14;
			break;
		case LightFour:
			reverse = 1;
			tempC = 0x28;
			break;
	}

	PORTC = tempC;
};



