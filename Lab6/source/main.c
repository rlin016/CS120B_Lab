/*	Author: raquelxyz
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	Video Link: https://youtu.be/ve6R-ylTU58
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "timer.h"
//#include "../header/timer.h"
#endif

enum States{Start, Light} state;
unsigned char tempB;

void Tick();
void Display_Lights();

int main(void){
	DDRA = 0x00; PORTA = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	TimerSet(1000);
	TimerOn();

	while(1){
		Tick();
		while(!TimerFlag);
		TimerFlag = 0;
	}
	return 1;
}

void Tick(){
	tempB = PORTB;
	switch(state){
		case Start:
			tempB = 0x00;
			state = Light;
		break;
		case Light:
		break;
	}
	switch(state){
		case Start:
		break;
		case Light:
			Display_Lights();
			break;
	}
	PORTB = tempB;
}

void Display_Lights(){
	if(!(tempB == 0x04) && (tempB)){
		tempB = tempB << 1;
	}
	else{
		tempB = 0x01;
	}
}
	

