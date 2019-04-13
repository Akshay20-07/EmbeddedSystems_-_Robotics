#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

void main()
{
DDRB=0xFF;
DDRA=0x00;
while(1)
{
if((PINA&0x0F)==8)
PORTB=0x0A;
if((PINA&0x0F)==4)
PORTB=0x09;
if((PINA&0x0F)==6)
PORTB=0x06;
if((PINA&0x0F)==2)
PORTB=0x05;
}
}
