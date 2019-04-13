#include<avr/io.h>
#define F_CPU 10000000UL
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
 OCR0=59;
 return OCR0 ;
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
 OCR0=52;
 return OCR0;
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
  OCR0=46;
 return OCR0;
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
  OCR0=44;
  return OCR0;
 
} 

PORTD=0x0D;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
 OCR0=38;
return OCR0;
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
OCR0=34;
return OCR0;
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
 OCR0=28;
 return OCR0;
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
 OCR0=05;
 return OCR0;
} 

/*PORTD=0x0B;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
OCR0=113;
return OCR0;
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
OCR0=100;
return OCR0;
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
 OCR0=85;
 return OCR0;
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
OCR0=70;
return OCR0;
} 

PORTD=0x07;
_delay_ms(5);
if((PINA&0x01)==0)
{

while(!(PINA&0x01));
OCR0=50;
return OCR0;
 
}
/*if((PINA&0x02)==0)
{
while(!(PINA&0x02))
 
  return '*';
 
}
 if((PINA&0x04)==0)
{
while(!(PINA&0x04))
 
 return '-';
 
}
 if((PINA&0x08)==0)
{
 
 while(!(PINA&0x08))
 
  return '+';
 
} 
*/

}
}

void pwm_init()
{
TCCR0|=(1<<WGM01)|(1<<CS01)|(1<<CS00)|(1<<COM00);
DDRB|=(1<<PB3);
} 

void main()
{
unsigned char ch;
DDRC=0xFF;
DDRD=0xFF;	//col
DDRA=0x00;	//row
PORTA=0xFF;	//pull up
Lcd_init();
pwm_init();
while(1)
{
ch=key();
_delay_ms(100);
}
}
