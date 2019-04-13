#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

void main()
{
DDRB=0xFF;
while(1)
{
 PORTB=0b00000001;
 _delay_ms(1000);
 PORTB=0b00000010;
 _delay_ms(1000);
  PORTB=0b00000100;
 _delay_ms(1000);
  PORTB=0b00001000;
 _delay_ms(1000);
  PORTB=0b00010000;
 _delay_ms(1000);
  PORTB=0b00100000;
 _delay_ms(1000);
  PORTB=0b01000000;
 _delay_ms(1000);
  PORTB=0b10000000;
 _delay_ms(1000);
 }
 }
