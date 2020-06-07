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
//#include "scheduler.h"
#ifdef _SIMULATE_
#include "../header/bit.h"
#include "../header/scheduler.h"
#include "simAVRHeader.h"
#include "../header/timer.h"
#endif
#include "io.h"

char* GetKeypadKey(){
	PORTC = 0xEF;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return("1"); }
	if(GetBit(PINC, 1) == 0) { return("4"); }
	if(GetBit(PINC, 2) == 0) { return("7"); }
	if(GetBit(PINC, 3) == 0) { return("*"); }

	PORTC = 0xDF;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return("2"); }
	if(GetBit(PINC, 1) == 0) { return("5"); }
	if(GetBit(PINC, 2) == 0) { return("8"); }
	if(GetBit(PINC, 3) == 0) { return("0"); }

	PORTC = 0xBF;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return("3"); }
	if(GetBit(PINC, 1) == 0) { return("6"); }
	if(GetBit(PINC, 2) == 0) { return("9"); }
	if(GetBit(PINC, 3) == 0) { return("#"); }

	PORTC = 0x7F;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return("A"); }
	if(GetBit(PINC, 1) == 0) { return("B"); }
	if(GetBit(PINC, 2) == 0) { return("C"); }
	if(GetBit(PINC, 3) == 0) { return("D"); }

	return("\0");
}

enum TickInputs_state{KeyStart, KeyWait, KeyInput, KeyRelease};
char* outputLCD = "Nothing's pressed yet :)";

unsigned char* tempC;
unsigned char testingSM = '1';

int TickInputs(int state){
	
	tempC = GetKeypadKey();
	 switch(state){
		 case KeyStart:
			 LCD_DisplayString(1, outputLCD);
			 state = KeyWait;
			 break;
		 case KeyWait:
//			 LCD_WriteData(testingSM);
			if(tempC != "\0"){ 
				 state = KeyInput;
			}
			 break;
	 	case KeyInput:
			 state = KeyRelease;
			 break;
		case KeyRelease:
			if(tempC == "\0"){
				 state = KeyWait;
			}
			break;
	 }
	 switch(state){
		 case KeyStart:
			 break;
		 case KeyWait:
			 break;
		case KeyInput:
	            outputLCD = tempC;
	            LCD_DisplayString(1, outputLCD);		     
		    break;
		case KeyRelease:
			break;
	 }

	 return state;
}


int TickOutputDisplay(int state){
	LCD_DisplayString(1, outputLCD);
	return state;
}

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRD = 0xFF; PORTD = 0x00;
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0xF0;
    /* Insert your solution below */
	LCD_init();
	static struct Task task1;
	struct Task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
//	const char start = -1;

	task1.state = KeyStart;
	task1.period = 100;
	task1.elapsedTime = task1.period;
	task1.TickFct = &TickInputs;
//LCD_WriteData(testingSM);
	TimerSet(100);
	TimerOn();
	unsigned short i;
    while (1) {
	for(i = 0; i < numTasks; i++){
		if( tasks[i]->elapsedTime == tasks[i]->period ){
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 100;
	}
	while(!TimerFlag);
	TimerFlag = 0;

    }
    return 1;
}
