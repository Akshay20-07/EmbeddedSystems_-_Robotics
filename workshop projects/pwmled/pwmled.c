#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

void pwm_init()
{
TCCR0|=(1<<WGM01)|(1<<WGM00)|(1<<CS01|(1<<COM01);
 DDRB=(1<<PB3);
 }

 void main()
 {
  pwm_init();
  while(1)
  {
  OCR0=100;
  _delay_ms(3000);
  OCR0=10;
   _delay_ms(3000);
  OCR0=50;
   _delay_ms(3000);
  OCR0=235;
   _delay_ms(3000);
  }
  }
