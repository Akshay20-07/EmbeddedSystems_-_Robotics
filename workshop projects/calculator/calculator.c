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
 return '7';
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
 
 return '4';
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
 return '1';
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));

  Lcd_cmd(0x01);
 
} 

PORTD=0x0D;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
return'8';
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
return '5';
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
 return '2';
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
 return '0';
} 

PORTD=0x0B;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
return '9';
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
return '6';
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
 return '3';
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
return '=';
} 

PORTD=0x07;
_delay_ms(5);
if((PINA&0x01)==0)
{

while(!(PINA&0x01));

return '/';
 
}
if((PINA&0x02)==0)
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


}
}

unsigned char digit()
{
unsigned char ch;
ch=key();
switch(ch)
{case'1': {Lcd_cmd(0x80);
      Lcd_num('1');
	  break;}
case'2': {Lcd_cmd(0x80);
      Lcd_num('2');
	  break;}
case'3': {Lcd_cmd(0x80);
      Lcd_num('3');
	  break;}
case'4': {Lcd_cmd(0x80);
      Lcd_num('4');
	  break;}
case'5': {Lcd_cmd(0x80);
      Lcd_num('5');
	  break;}
case'6': {Lcd_cmd(0x80);
      Lcd_num('6');
	  break;}
case'7': {Lcd_cmd(0x80);
      Lcd_num('7');
	  break;}
case'8': {Lcd_cmd(0x80);
      Lcd_num('8');
	  break;}
case'9': {Lcd_cmd(0x80);
      Lcd_num('9');
	  break;}
case'0': {Lcd_cmd(0x80);
      Lcd_num('0');
	  break;}
}	  }

void main()
{
unsigned char op; unsigned int a,b,c;
DDRC=0xFF;
DDRD=0xFF; //column
DDRA=0x00; //row
PORTA=0xFF; //pull up
Lcd_init();
while(1)
{ op=key();
switch(op)
{case'*': {Lcd_cmd(0x80);
      Lcd_str("*");
	  a=key();
	  Lcd_cmd(0x81);
	  Lcd_num('a');
	  b=key();
	  Lcd_cmd(0x82);
	  Lcd_num('b');
	  c=a*b;
      Lcd_cmd(0xC4);
	  Lcd_num('c');
	  break;}
case'+': {Lcd_cmd(0x80);
      Lcd_num("+");
	  a=key();
	  Lcd_cmd(0x81);
	  Lcd_num('a');
	  b=key();
	  Lcd_cmd(0x82);
	  Lcd_num('b');
	  c=a+b;
      Lcd_cmd(0xC4);
	  Lcd_num('c');
	  break;}
case'-': {Lcd_cmd(0x80);
      Lcd_num("-");
	  a=key();
	  Lcd_cmd(0x81);
	  Lcd_num('a');
	  b=key();
	  Lcd_cmd(0x82);
	  Lcd_num('b');
	  c=a-b;
      Lcd_cmd(0xC4);
	  Lcd_num('c');
	  break;}
case'/': {Lcd_cmd(0x80);
      Lcd_num("/");
	  a=key();
	  Lcd_cmd(0x81);
	  Lcd_num('a');
	  b=key();
	  Lcd_cmd(0x82);
	  Lcd_num('b');
	  c=a/b;
      Lcd_cmd(0xC4);
	  Lcd_num('c');
	  break;}
default: digit();
        break;
			  }
}}
