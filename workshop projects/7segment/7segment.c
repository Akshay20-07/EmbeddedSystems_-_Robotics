#include<avr/io.h>
#define F_CPU 16000000UL
#include <util/delay.h>

unsigned char a[]={0xC0,0xF9,0xA4,0xB0,0x99,0x92,0x82,0xF8,0x80,0x90};

void main()
{
DDRB=0xFF;

while(1)
{
for(int i=0;i<=9;i++)
{
PORTB=a[i];
_delay_ms(1000);
}

}
}
