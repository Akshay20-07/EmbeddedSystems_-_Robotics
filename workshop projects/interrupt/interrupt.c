#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#define F_CPU 1000000UL

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

ISR(INT0_vect)
{
 PORTB=0xF0;
 Lcd_cmd(0x80);
 Lcd_str("intrrupt running");
 _delay_ms(1000);
 }

 int main()
 {
 DDRB=0xFF;
 DDRC=0xFF;
 DDRD=0X04;
 PORTD=0X04;
 Lcd_init();
 MCUCR|=(1<<ISC00);
 GICR|=(1<<INT0);
 sei();
 while(1)
 {
 PORTB=0x0F;
 Lcd_cmd(0x80);
 Lcd_str("main running");
 _delay_ms(1000);
 }
 return 0;
 }
