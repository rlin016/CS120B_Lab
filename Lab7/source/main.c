/*	Author: raquelxyz
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
i *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "../header/timer.h"
#include "../header/io.h"
#endif

enum States{Start, Wait, Increment, Decrement, Reset}state;
unsigned char tempA, count;

void Tick();
void Display_Lights();

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRC = 0xFF; PORTC = 0x00;
	DDRD = 0xFF; PORTD = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
	TimerSet(1000);
	TimerOn();
    /* Insert your solution below */
    while (1) {
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
			count = 0;
			state = Wait;
			break;
		case Wait:
			if((tempA & 0x03)== 0x01){
			       state = Increment;
			}
			else if((tempA & 0x03) == 0x02){
				state = Decrement;
			}
			else if((tempA & 0x03) == 0x03){
				state = Reset;
			}
			break;
		case Increment:
			if((tempA & 0x03) == 0x01){
				state = Increment;
			}
			else if((tempA & 0x03) == 0x03){
				state = Reset;
			}
			else{
				state = Wait;
			}
			break;
		case Decrement:
			if((tempA & 0x03) == 0x02){
				state = Decrement;
			}
			else if((tempA & 0x03) == 0x03){
				state = Reset;
			}
			else{
				state = Wait;
			}
			break;
		case Reset:
			state = Wait;
			break;
	}
	switch(state){
		case Start:
			break;
		case Wait:
			Display_Lights();
			break;
		case Increment:
			if(count < 9){
				count++;
			}
			Display_Lights();
			break;
		case Decrement:
			if(count > 0){
				count--;
			}
			Display_Lights();
			break;
		case Reset:
			count = 0;
			Display_Lights();
			break;
	}
}

void Display_Lights(){
	PORTC = count;
	//LCD_WriteData(count + '0');
}


