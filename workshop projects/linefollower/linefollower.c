#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

#define Lcd PORTC
#define RS PC0
#define RW PC1
#define EN PC2

void Lcd_cmd(unsigned char C)
{
Lcd=(C & 0xF0);
Lcd &=~(1<<RS);
Lcd &=~(1<<RW);
Lcd |=(1<<EN);
_delay_ms(10);
Lcd &=~(1<<EN);

Lcd=((C<<4)&0xF0);
Lcd &=~(1<<RS);
Lcd &=~(1<<RW);
Lcd |=(1<<EN);
_delay_ms(10);
Lcd &=~(1<<EN);
}

void Lcd_data(unsigned char D)
{
Lcd=(D & 0xF0);
Lcd |=(1<<RS);
Lcd &=~(1<<RW);
Lcd |=(1<<EN);
_delay_ms(10);
Lcd &=~(1<<EN);

Lcd=((D<<4)&0xF0);
Lcd |=(1<<RS);
Lcd &=~(1<<RW);
Lcd |=(1<<EN);
_delay_ms(10);
Lcd &=~(1<<EN);
}

void Lcd_num(int i)
{
int d;
Lcd_cmd(0x04);
while(i!=0)
{ 
d=i%10;
Lcd_data(d+48);
i/=10;
d=i%10;
Lcd_data(d+48);
i/=10;
}
Lcd_cmd(0x06);
}

void Lcd_init()
{
Lcd_cmd(0x02);
Lcd_cmd(0x28);
Lcd_cmd(0x06);
Lcd_cmd(0x0C);
}

void Lcd_str (unsigned char *str)
{
while(*str)
Lcd_data(*str++);
}

void main()
{
DDRB=0xFF;
DDRC=0xFF;
DDRA=0x00;

Lcd_init();
while(1)
{
if(PINA & 0x01 && PINA & 0x02)
{

PORTB=0b00000110;
//_delay_ms(100);
Lcd_cmd(0x80);
Lcd_str("no movement");
//_delay_ms(100);
}
else if(PINA & 0x01)
{
PORTB=0b00000101;
//_delay_ms(100);
Lcd_cmd(0x80);
Lcd_str("Left turn");
//_delay_ms(100);
}
else if(PINA & 0x02)
{
PORTB=0b00001010;
//_delay_ms(100);
Lcd_cmd(0x80);
Lcd_str("RIght turn");
//_delay_ms(100);
}
else
{

PORTB=0b00001001;
//_delay_ms(100);
Lcd_cmd(0x80);
Lcd_str("moving forward");
//_delay_ms(100);
}
_delay_ms(10);
}
}

