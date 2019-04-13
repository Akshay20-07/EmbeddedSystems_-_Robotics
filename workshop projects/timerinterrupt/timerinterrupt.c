#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#define F_CPU 1000000UL

#define Lcd PORTC
#define RS PC0
#define RW PC1
#define EN PC2

unsigned int count=0;
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

ISR(TIMER0_OVF_vect)
{
count++;
if(count==15)
{
Lcd_cmd(0x80);
Lcd_str("INterrupt");
PORTB=0xFF;
_delay_ms(1000);
count=0;
}
}

void print()
{
Lcd_cmd(0x80);
Lcd_str("main");
_delay_ms(4000);
}


int main()
{
DDRB=0xFF;
DDRC=0xFF;
TIMSK|=(1<<TOIE0);
TCCR0|=(1<<CS00)|(1<<CS02);
Lcd_init();
sei();
while(1)
{
PORTB=0x00;
print();
}
return 0;
}


