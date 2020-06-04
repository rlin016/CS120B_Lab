/*      Author: raquelxyz
 *  Partner(s) Name: 
 *      Lab Section:
 *      Assignment: Lab #  Exercise #
 *      Exercise Description: [optional - include for your own benefit]
 *
i *     I acknowledge all content contained herein, excluding template or example
 *      code, is my own original work.
 */
#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
//#include "../header/io.h"
#endif
#include "timer.h"
#include "io.h"

enum States{Wait, Up, UpWait, Down, DownWait, Reset} state;

void Tick();
void Display(unsigned char);

unsigned char tempA;
unsigned char count;

int main(void) {
    /* Insert DDR and PORT initializations */
        DDRC = 0xFF; PORTC = 0x00;
        DDRD = 0xFF; PORTD = 0x00;
        DDRA = 0x00; PORTA = 0xFF;

        state = Wait;
        count = 0;

        LCD_init();
        TimerSet(100);
        TimerOn();

    /* Insert your solution below */
    while (1) {
            tempA = ~PINA;
            Tick();
            while(!TimerFlag);
            TimerFlag = 0;

    }
        return 1;
}

void Display(unsigned char count){
        LCD_ClearScreen();
        LCD_WriteData(count + '0');
}


void Tick(){
        static unsigned char i = 0;
        switch(state){
                case Wait:
                        if((tempA & 0x03) == 0x01){
                                state = Up;
                        }
                        else if((tempA & 0x03) == 0x02){
                                state = Down;
                        }
                        else if((tempA & 0x03) == 0x03){
                                state = Reset;
                        }
                        break;
                case Up:
                        if((tempA & 0x03) == 0x03){
                                state = Reset;
                        }
                        else if((tempA & 0x01) == 0x00){
                                state = Wait;
                        }
                        else{
                                state = UpWait;
                        }
                        break;
                case UpWait:
                        if((tempA & 0x03) == 0x03){
                                state = Reset;
                        }
                        else if ((i == 10) && ((tempA & 0x03) == 0x01)){
                                i = 0;
                                state = Up;
                        }
                        else if((tempA & 0x03) == 0){
                                state = Wait;
                        }
                        break;
                case Down:
                        if((tempA & 0x03) == 0x03){
                                state = Reset;
                        }
                        else if((tempA & 0x02) == 0x00){
                                state = Wait;
                        }
                        else{
                                state = DownWait;
                        }
                        break;
                case DownWait:
                        if((tempA & 0x03) == 0x03){
                                state = Reset;
                        }
                        else if((i == 10) && ((tempA & 0x03) == 0x02)){
                                i = 0;
                                state = Down;
                        }
                        else if((tempA & 0x03) == 0){
                                state = Wait;
                        }
                        break;
                case Reset:
                        state = Wait;
                        break;
        }
        switch(state){
                case Wait:
                        break;
                case Up:
                        if(count < 9){
                                count++;
                        }
                        break;
                case UpWait:
                case DownWait:
                        i++;
                        break;
                case Down:
                        if(count > 0){
                                count--;
                        }
                        break;
                case Reset:
                        count = 0;
                        break;
        }

        Display(count);
}

                                                                                                                                                         

