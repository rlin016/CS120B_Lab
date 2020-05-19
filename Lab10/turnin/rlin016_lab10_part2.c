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
#include "../header/timer.h"
#endif

void TickThreeLEDs();
void TickBlinkingLEDs();
void TickCombineLEDs();

enum ThreeLeds{ThreeStart, ZeroLed, OneLed, TwoLed}threestate;
enum BlinkingLeds{BlinkStart, OnLed, OffLed}blinkstate;

unsigned char tempB, i, j;
unsigned char threeLed, blinkingLed;

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	i = 0;
	j = 0;
	TimerSet(100);
	TimerOn();
    while (1) {
	    tempB = 0; 
	    TickThreeLEDs();
	    TickBlinkingLEDs();
	    TickCombineLEDs();
	    PORTB = tempB;
	    while(!TimerFlag);
	    TimerFlag = 0;
    }
    return 1;
}

void TickThreeLEDs(){
	if(i == 3){
	switch(threestate){
		case ThreeStart:
			threestate = ZeroLed;
			break;
		case ZeroLed:
			threestate = OneLed;
			break;
		case OneLed:
			threestate = TwoLed;
			break;
		case TwoLed:
			threestate = ZeroLed;
			break;
	}
	switch(threestate){
		case ThreeStart:
			break;
		case ZeroLed:
			threeLed = 0x01;
		        break;
		case OneLed:
			threeLed = 0x02;
	 		break;
		case TwoLed:
			threeLed = 0x04;
			break;	
	}
	i = 0;
	}
	else{
		i++;
	}		
}

void TickBlinkingLEDs(){
	if(j == 10){
	switch(blinkstate){
		case BlinkStart:
			blinkstate = OnLed;
			break;
		case OnLed:
			blinkstate = OffLed;
			break;
		case OffLed:
			blinkstate = OnLed;
			break;	
	}
	switch(blinkstate){
			case BlinkStart:
			break;
		case OnLed:
			blinkingLed = 0x08;
		      	break;	
		case OffLed:
			blinkingLed = 0x00;
			break;
	}
	
	j = 0;

	}
	else{
		j++;
	}	
}

void TickCombineLEDs(){
	tempB = (threeLed & 0x07)| (blinkingLed & 0x08);
}
