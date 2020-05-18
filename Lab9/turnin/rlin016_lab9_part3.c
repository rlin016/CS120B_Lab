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

void set_PWM(double frequency){
	static double current_frequency;
	if(frequency != current_frequency){
		if(!frequency){ 
			TCCR3B &= 0x08;
		}
		else{
			TCCR3B |= 0x03;
		}
		
		if(frequency < 0.954){
			OCR3A = 0xFFFF;
		}
		else if(frequency > 31250){
			OCR3A = 0x0000;
		}
		else{
			OCR3A = (short)(8000000 / (128 * frequency)) - 1;
		}

		TCNT3 = 0;
		current_frequency = frequency;
	}
}

void PWM_on(){
	TCCR3A = (1 << COM3A0);
	TCCR3B = (1 << WGM32) | (1 << CS31) | (1 << CS30);
	set_PWM(0);
}

void PWM_off(){
	TCCR3A = 0x00;
	TCCR3B = 0x00;
}

void Tick();
unsigned char tempA, i, j;
enum States {Start, Wait, Playing}state;
const double notes[] = {369.994, 
			440.00, 493.883, 440.00, 659.255, 554.365,
			0,
			293.665,
			440.00, 493.883, 440.00, 659.255, 554.365,
			0,
			220.000,
			440.00, 493.883, 440.00, 659.255, 554.365,
			0,
			659.255, 739.989, 659.255,
			554.365, 	
			493.883, 440.000, 493.883, 440.000, 369.994
			};
const unsigned char time[] = {2, 
		              1, 1, 1, 1, 2,
			      0,
       	                      2, 
			      1, 1, 1, 1, 2, 
			      0,
			      2,
			      1, 1, 1, 1, 2,
			      0,
			      0, 0, 1,
			      1,
			      1, 1, 1, 1, 2					      
			     };
//const unsigned char downTime[] = {0, 0, 0, 0, 0, 0}

void Tick();

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	PWM_on();
	TimerSet(100);
	TimerOn();
	i = 0; 	
    while (1){
	tempA = ~PINA & 0x01;
	Tick();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    PWM_off();
    return 1;
}

void Tick(){
	switch(state){
		case Start:
			state = Wait;
			break;
		case Wait:
			if(tempA == 0x01){
				i = 0;
				j = 0;
				state = Playing;
			}
			break;
		case Playing:
			if(i == 30){
				set_PWM(0);
				state = Wait;
			}
			break;
	}
	
	switch(state){
		case Start:
		case Wait:
			break;
		case Playing:
			if(i < 30){
				if(j == 0x00){
					j = time[i];
					set_PWM(notes[i++]);
				}
				else{
					
					j--;
				}
			}
			break;
	}

}
