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

PORTB=0b0100000;
_delay_ms(1000);

PORTB=0b10000000;
_delay_ms(1000);

//stage2
PORTB=0b10000001;
_delay_ms(1000);

PORTB=0b10000010;
_delay_ms(1000);

PORTB=0b10000100;
_delay_ms(1000);

PORTB=0b10001000;
_delay_ms(1000);

PORTB=0b10010000;
_delay_ms(1000);

PORTB=0b10100000;
_delay_ms(1000);

PORTB=0b1100000;
_delay_ms(1000);

//stage3

PORTB=0b11000001;
_delay_ms(1000);

PORTB=0b11000010;
_delay_ms(1000);

PORTB=0b11000100;
_delay_ms(1000);

PORTB=0b11001000;
_delay_ms(1000);

PORTB=0b11010000;
_delay_ms(1000);

PORTB=0b11100000;
_delay_ms(1000);

//stage4

PORTB=0b11100001;
_delay_ms(1000);

PORTB=0b11100010;
_delay_ms(1000);

PORTB=0b11100100;
_delay_ms(1000);

PORTB=0b11101000;
_delay_ms(1000);

PORTB=0b11110000;
_delay_ms(1000);

//stage 5
PORTB=0b00001111;
_delay_ms(3000);
//stage 6
PORTB=0b00011110;
_delay_ms(3000);
//stage7
PORTB=0b00111100;
_delay_ms(3000);
//stage8
PORTB=0b01111000;
_delay_ms(3000);
//stage9
PORTB=0b11110000;
_delay_ms(3000);


}
}
