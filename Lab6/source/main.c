/*	Author: raquelxyz
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
#include "timer.h"
//#include "../header/timer.h"
#endif

enum States{Start, Light, Maint, MaintPress, MaintRelease}state;
unsigned char tempA, tempB, count, forward;

void Tick();
void DisplayLight();

int main(void){
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00; 
	TimerSet(300);
	TimerOn();
	while(1){
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 1;
}

void Tick(){
	tempA = ~PINA;
	tempB = PORTB;
	switch(state){
		case Start:
			tempB = 0x00;
			state = Light;
			break;
		case Light:
			if(tempA & 0x01){
				state = Maint;
			}
			break;
		case Maint:
			if(!(tempA & 0x01)){
				state = MaintPress;
			}
			break;
		case MaintPress:
			if((tempA & 0x01)){
				state = MaintRelease;
			}
			break;
		case MaintRelease:
			if(!(tempA & 0x01)){
				state = Light;
			}
			break;
	}
	switch(state){
		case Start:
			break;
		case Light:
		case MaintRelease:
			DisplayLight();
			break;
		case Maint:
		case MaintPress:
			break;
	}
	PORTB = tempB;
}

void DisplayLight(){
	if(!tempB){
		tempB = 0x01;
		count = 0x02;
		forward = 1;
	} else{
		if (count && forward){
			tempB = tempB << 1;
			count--;
		}
		else if(count && !forward){
			tempB = tempB >> 1;
			count++;
			forward = 1;
		}
		else{
			tempB = tempB >> 1;
			count++;
			forward = 0;
			
		}
	}
}
	

