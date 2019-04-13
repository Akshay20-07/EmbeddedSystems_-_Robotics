#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

unsigned char a[]={0x25};
void main()
{
DDRB=0xFF;

while(1)
{
for(int i=0;i<=6;i++)
{
PORTB=a[i];
_delay_ms(100);
}
}
}
