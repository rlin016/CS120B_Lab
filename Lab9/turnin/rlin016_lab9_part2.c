/*	Author: raquelxyz
 *  Partner(s) Name: 
 *	Lab Section:
 *	Assignment: Lab #  Exercise #
 *	Exercise Description: [optional - include for your own benefit]
 *
 *	I acknowledge all content contained herein, excluding template or example
 *	code, is my own original work.
 *	
 *	Video Link: https://youtu.be/NRkKlr3tdBE
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
unsigned char tempA, i;
enum StatesPower{PowerStart, PwrOn, POn, PwrOff, POff}power;
enum StatesScale{Start, Wait, Up, UpRelease, Down, DownRelease}scale;
enum PowerStatus{Off, On}pwr;
const double notes[] = {261.63, 293.66, 329.63, 349.23, 392.00, 440.00, 493.88, 523.25};

void TickOnOff();
void TickScale();

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRB = 0xFF; PORTB = 0x00;
	DDRA = 0x00; PORTA = 0xFF;
    /* Insert your solution below */
	PWM_on();
	TimerSet(50);
	TimerOn();
	i = 0; 	
    while (1){
	tempA = ~PINA & 0x07;
	TickOnOff();
	TickScale();
	while(!TimerFlag);
	TimerFlag = 0;
    }
    PWM_off();
    return 1;
}

void TickOnOff(){
	switch(power){
		case PowerStart:
			if(tempA == 0x01){
				power = PwrOn;
			}
			break;
		case PwrOn:
			if(tempA == 0x00){
				power = POn;
			}
			break;
		case POn:
			if(tempA == 0x01){
				power = PwrOff;
			}
			break;
		case PwrOff:
			if(tempA == 0x00){
				power = POff;
			}
			break;
		case POff:
			if(tempA == 0x01){
				power = PwrOn;
			}
			break;
	}
	switch(power){
		case PowerStart:
		case POn:
		case POff:
			break;
		case PwrOn:
			pwr = On;
			break;
		case PwrOff:
			pwr = Off;
			break;
	}
}

void TickScale(){
	if(!pwr){
		set_PWM(0);
	}
	else{
	switch(scale){
		case Start: 
			scale = Wait;
			break;
		case Wait:
			if(tempA == 0x02){
				scale = Up;
			}
			else if(tempA == 0x04){
				scale = Down;
			}
			break;
		case Up:
			scale = UpRelease;
			break;

		case UpRelease:
			if(tempA == 0x00){
				scale = Wait;
			}
			break;
		case Down:
			scale = DownRelease;
			break;
		case DownRelease:
			if(tempA == 0x00){
				scale = Wait;
			}
			break;
	}
	switch(scale){
		case Start:
		case UpRelease:
		case DownRelease:
			break;
		case Wait:
			set_PWM(notes[i]);
			break;
		case Up:
			if(i < 7){
				set_PWM(notes[++i]);
			}
			break;
		case Down:
			if(i > 0){
				set_PWM(notes[--i]);
			}
			break;
	}
	}
}
