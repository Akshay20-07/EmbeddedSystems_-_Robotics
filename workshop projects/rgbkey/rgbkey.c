#include<avr/io.h>
#define F_CPU 1000000UL
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

unsigned char key()
{
unsigned char a;

while(1)
{
PORTD=0x0E;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
 PORTB=0x01;
_delay_ms(1000);
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
 PORTB=0x02;
_delay_ms(1000);
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
PORTB=0x04;
_delay_ms(1000);
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));

  PORTB=0x0B;
_delay_ms(1000);
 
} 

PORTD=0x0D;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
PORTB=0x0F;
_delay_ms(1000);
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
PORTB=0x03;
_delay_ms(1000);
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
PORTB=0x09;
_delay_ms(1000);
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
 return '0';
} 

}
}

void main()
{
unsigned char ch;
DDRC=0xFF;
DDRB=0xFF;
DDRD=0xFF;	//col
DDRA=0x00;	//row
PORTA=0xFF;	//pull up
Lcd_init();
//ch=key();
while(1)
{
key();
_delay_ms(100);
}
}
