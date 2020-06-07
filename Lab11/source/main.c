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
#include <stdio.h>
#ifdef _SIMULATE_
#include "../header/bit.h"
#include "../header/scheduler.h"
#include "simAVRHeader.h"
#include "../header/timer.h"
#include <string.h>
#endif
#include "io.h"

enum TickScroll_state{ScrollWait, ScrollGetString, ScrollOutputString}tickstate;

const char* CSString = "CS120B is Legend... wait for it DARY!";

char* outString;

int TickOutputLCD(int state){
//	LCD_DisplayString(1, stringTest);
	static unsigned char i;
	switch(state){
		case ScrollWait:
			LCD_DisplayString(1, outString);
			state = ScrollGetString;
			break;
		case ScrollGetString:
		//	LCD_DisplayString(1,stringTest);
			state = ScrollOutputString;
			break;
		case ScrollOutputString:
			state = ScrollOutputString;
			break;
	}

	switch(state){
		case ScrollWait: //wait for input A, do nothing for part 2
			break;
		case ScrollGetString: //use strncpy to get desired segment of string
			strncpy(outString, CSString + 1, 16);
			break;	
		case ScrollOutputString: //use outputString to output to LCD to write.
			LCD_DisplayString(1, outString);
			break;
	}
	return state;
}


int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRC = 0xF0; PORTC = 0x0F;
	DDRD = 0xFF; PORTD = 0x00;

	LCD_init();

    /* Insert your solution below */
	static struct Task task1;
	struct Task *tasks[] = {&task1};
	const unsigned short numTasks = sizeof(tasks) / sizeof(task*);
	const char start = -1;

	task1.state = ScrollWait;
	task1.period = 500;
	task1.elapsedTime = task1.period;
	task1.TickFct = &TickOutputLCD;

/*	task2.state = start;
	task2.period = 500;
	task2.elapsedTime = task1.period;
	task2.TickFct = &TickOutputLCD; */

//	LCD_init();

	TimerSet(500);
	TimerOn();

	unsigned short i;
    while (1) {
	for(i = 0; i < numTasks; i++){
		if( tasks[i]->elapsedTime == tasks[i]->period ){
			tasks[i]->state = tasks[i]->TickFct(tasks[i]->state);
			tasks[i]->elapsedTime = 0;
		}
		tasks[i]->elapsedTime += 500;
	}
	while(!TimerFlag);
	TimerFlag = 0;

    }
    return 1;
}
