#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

int main()
{
DDRB=0x0F;
DDRA=0x00;
PORTA=0x01;
while(1)
{
PORTB=PINA;
}
return 0;
}
