#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

void main()
{
DDRA=0xFF;

while(1)
{
PORTA=0x80;
_delay_ms(1000);
PORTA=0x00;
_delay_ms(2000);
}
}
