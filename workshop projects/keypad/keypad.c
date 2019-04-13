#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

void main()
{
DDRA=0xFF;
DDRB=0xFF;
DDRD=0xFF;	//col
DDRC=0x00;	//row
PORTC=0xFF;	//pull up
while(1)
{
PORTD=0x00;
_delay_ms(5);
if((PINC&0x01)==0)
{
while(!(PINC&0x01))
{
 PORTB=0x01;
 _delay_ms(1000);
 PORTB=0x00;
 }
}
else if((PINC&0x02)==0)
{
while(!(PINC&0x02))
 {
  PORTB=0x04;
  _delay_ms(1000);
 PORTB=0x00;
 }
}
else if((PINC&0x04)==0)
{
 while(!(PINC&0x04))
 {
  PORTA=0x80;
  _delay_ms(100);
 PORTA=0x00;
 }
}
else if((PINC&0x08)==0)
{
 while(!(PINC&0x08))
 {
  PORTB=0xF0;
  _delay_ms(1000);
 PORTB=0x00;
 }
} 
}
}
