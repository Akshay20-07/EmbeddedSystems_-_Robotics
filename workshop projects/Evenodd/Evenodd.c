#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

void main()
{
 DDRB=0xFF;
 while(1)
 {
 PORTB=0B00000001;
 _delay_ms(1000);
 PORTB=0b00000100;
 _delay_ms(1000);
  PORTB=0B00010000;
 _delay_ms(1000);
 PORTB=0B01000000;
 _delay_ms(1000);
  PORTB=0B00000010;
 _delay_ms(1000);
  PORTB=0B00001000;
 _delay_ms(1000);
  PORTB=0B00100000;
 _delay_ms(500);
  PORTB=0B10000000;
 _delay_ms(1000);
 }
 }
