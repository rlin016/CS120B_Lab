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
void TickFrequencyChecker();
void TickOutputSpeaker();

enum ThreeLeds{ThreeStart, ZeroLed, OneLed, TwoLed}threestate;
enum BlinkingLeds{BlinkStart, OnLed, OffLed}blinkstate;
enum FrequencyChecker{FreqStart, FreqWait, FreqUp, FreqDown}freqstate;
enum OutputSpeaker{SpeakStart, SpeakWait, SpeakHigh, SpeakLow}speakstate; 

unsigned char frequency, k, speakerOutput; //increment k, assign to frequency
unsigned char tempA, tempB;
unsigned short i, j;
unsigned char threeLed, blinkingLed;

int main(void) {
    /* Insert DDR and PORT initializations */
	DDRA = 0x00; PORTA = 0xFF;
	DDRB = 0xFF; PORTB = 0x00;
    /* Insert your solution below */
	i = 0;
	j = 0;
	k = 1;
	TimerSet(1);
	TimerOn();
    while (1) {
	    tempA = ~PINA;
	    tempB = 0; 
	    TickThreeLEDs();
	    TickBlinkingLEDs();
	    TickCombineLEDs();
	    TickFrequencyChecker();
	    TickOutputSpeaker();
	    PORTB = tempB;
	    while(!TimerFlag);
	    TimerFlag = 0;
    }
    return 1;
}

void TickThreeLEDs(){
	if(i == 300){
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
	if(j == 1000){
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
	tempB = (threeLed & 0x07) | (blinkingLed & 0x08) | (speakerOutput & 0x10);
}

void TickFrequencyChecker(){
	switch(freqstate){
		case FreqStart:
			freqstate = FreqWait;
			break;
		case FreqWait:
			if(tempA == 0x01){
				freqstate = FreqUp;
			}
			else if(tempA == 0x02){
				freqstate = FreqDown;
			}
			break;
		case FreqUp:
			freqstate = FreqWait;
			break;
		case FreqDown:
			freqstate = FreqWait;
			break;
	}
	switch(freqstate){
		case FreqStart:
		case FreqWait:
			break;
		case FreqUp:
			if(k > 1){
				k--;
			}
			break;
		case FreqDown:
			if(k < 250){
				k++;
			}
			break;
	}
}

void TickOutputSpeaker(){
	switch(speakstate){
		case SpeakStart:
			speakstate = SpeakWait;
			break;
		case SpeakWait:
			if(tempA == 0x04){
				frequency = k;
				speakstate = SpeakHigh;
			}
			break;
		case SpeakHigh:
			if((frequency == 0)){
				frequency = k;
				speakstate = SpeakLow;
			}
			break;
		case SpeakLow:
			if((frequency == 0) && (tempA == 0x04)){
				frequency = k;
				speakstate = SpeakHigh;
			}
			else{
				speakstate = SpeakWait;
			}
			break;
	}
	switch(speakstate){
		case SpeakStart:
			break;
		case SpeakWait:
			frequency = k;
			break;
		case SpeakHigh:
			speakerOutput = 0x10;
			frequency--;
			break;
		case SpeakLow:
			speakerOutput = 0x00;
			frequency--;
			break;
	}
}

			
