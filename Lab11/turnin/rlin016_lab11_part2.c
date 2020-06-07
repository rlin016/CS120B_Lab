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

unsigned char GetKeypadKey(){
	PORTC = 0xEF;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return('1'); }
	if(GetBit(PINC, 1) == 0) { return('4'); }
	if(GetBit(PINC, 2) == 0) { return('7'); }
	if(GetBit(PINC, 3) == 0) { return('*'); }

	PORTC = 0xDF;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return('2'); }
	if(GetBit(PINC, 1) == 0) { return('5'); }
	if(GetBit(PINC, 2) == 0) { return('8'); }
	if(GetBit(PINC, 3) == 0) { return('0'); }

	PORTC = 0xBF;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return('3'); }
	if(GetBit(PINC, 1) == 0) { return('6'); }
	if(GetBit(PINC, 2) == 0) { return('9'); }
	if(GetBit(PINC, 3) == 0) { return('#'); }

	PORTC = 0x7F;
	asm("nop");
	if(GetBit(PINC, 0) == 0) { return('A'); }
	if(GetBit(PINC, 1) == 0) { return('B'); }
	if(GetBit(PINC, 2) == 0) { return('C'); }
	if(GetBit(PINC, 3) == 0) { return('D'); }

	return('\0');
}

enum TickInputs_state{start};

int TickInputs(int state){
	 
            char input = GetKeypadKey();
            switch(input) {
                    case '\0': PORTB = 0x1F; break;
                    case '1': PORTB = 0x01; break;
                    case '2': PORTB = 0x02; break;
                    case '3': PORTB = 0x03; break;
                    case '4': PORTB = 0x04; break;
                    case '5': PORTB = 0x05; break;
                    case '6': PORTB = 0x06; break;
                    case '7': PORTB = 0x07; break;
                    case '8': PORTB = 0x08; break;
                    case '9': PORTB = 0x09; break;
                    case 'A': PORTB = 0x0A; break;
                    case 'B': PORTB = 0x0B; break;
                    case 'C': PORTB = 0x0C; break;
                    case 'D': PORTB = 0x0D; break;
                    case '*': PORTB = 0x0E; break;
                    case '#': PORTB = 0x0F; break;
                    case '0': PORTB = 0x00; break;
                    default: PORTB = 0x1B; break; //never occurs
            }
	    return state;
}

enum TickScroll_state{ScrollWait, ScrollGetString, ScrollOutputString}tickstate;

const char* CSString = "CS120B is Legend... wait for it DARY!";
const char* stringTest = "testing this type";

char outString[20];

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
//		strncpy(outString, CSString + 1, 16);
//		outString[16] = '\0';
		break;	
	case ScrollOutputString: //use outputString to output to LCD to write.
		LCD_DisplayString(1, stringTest);
//		LCD_ClearScreen();
//		LCD_DisplayString(1, outString);
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
