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

void Lcd_animation()
{
Lcd_cmd(0x40);
Lcd_data(0x11);
Lcd_data(0x0A);
Lcd_data(0x04);
Lcd_data(0x1F);
Lcd_data(0x00);
Lcd_data(0x00);
Lcd_data(0x00);

}

void Lcd_anima()
{
Lcd_cmd(0x40);
Lcd_data(0x00);
Lcd_data(0x00);
Lcd_data(0x00);
Lcd_data(0x1F);
Lcd_data(0x04);
Lcd_data(0x0A);
Lcd_data(0x11);

}

void main()
{
int i,j;
DDRC=0xFF;
Lcd_init();
while(1)
{
for(i=0x80;i<=0xA7;i++)
{
j=i+1;
Lcd_cmd(i);
Lcd_data(0);
Lcd_anima();
_delay_ms(400);
Lcd_cmd(0x01);


Lcd_cmd(j);
Lcd_data(0);
Lcd_animation();
_delay_ms(400);
Lcd_cmd(0x01);

}

for(i=0xE7;i>=0xC0;i--)
{
j=i-1;
Lcd_cmd(i);
Lcd_data(0);
Lcd_anima();
_delay_ms(400);
Lcd_cmd(0x01);

Lcd_cmd(j);
Lcd_data(0);
Lcd_animation();
_delay_ms(400);
Lcd_cmd(0x01);
}
}
}
