#include <avr/io.h>
#ifdef _SIMULATE_
#include "simAVRHeader.h"
#include "../header/timer.h"
#endif

void ADC_init(){
  ADCSRA |= (1 << ADEN) | (1 << ADSC) | (1 << ADATE);
}

unsigned short ADC_result;
unsigned char tempB, tempD;

void Tick();

int main(void){
  ADC_init();
  ADC_result = 0x00;
  tempB = 0x00;
  tempD = 0x00;
  DDRB = 0xFF; PORTB = 0x00;
  DDRD = 0xFF; PORTD = 0x00;
  DDRA = 0x00; PORTA = 0x00;
  while(1){
    Tick();
  }
  return 1;
}

void Tick(){
  ADC_result = ADC;
  tempB = (char)(ADC_result);
  tempD = (char)((ADC_result >> 8));
  PORTB = tempB;
  PORTD = tempD;
}
