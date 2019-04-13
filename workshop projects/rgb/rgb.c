#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

void main()
{
DDRB=0xFF;
while(1)
{
PORTB=0x01;
_delay_ms(1000);
PORTB=0x02;
_delay_ms(1000);
PORTB=0x04;
_delay_ms(1000);
PORTB=0x0B;
_delay_ms(1000);
PORTB=0x0F;
_delay_ms(1000);
PORTB=0x03;
_delay_ms(1000);
PORTB=0x09;
_delay_ms(1000);
}
}
