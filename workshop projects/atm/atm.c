#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

#define Lcd PORTC
#define RS PC0
#define RW PC1
#define EN PC2
#define del 0x7F
unsigned char count=1,loc,inc=0;

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

void main()
{
unsigned int i,j,flag=0;
unsigned char ar1[]={"1234"},ar2[4];
DDRC=0xFF;
DDRB=0xFF;
DDRD=0xFF;	//col
DDRA=0x00;	//row
PORTA=0xFF;	//pull up
PORTD=0x00;
Lcd_init();
//ch=key();
while(1)
{
for(i=0;i<4;i++)
{
ar2[i]=key();
Lcd_cmd(0x80+i);
Lcd_data(ar2[i]);
}

for(j=0;j<4;j++)
{
 if(ar2[j]!=ar1[j])
 flag++;
  
  if(flag==0)
  {
  Lcd_cmd(0xc2);
  Lcd_str("access granted");
  }
  else
  {
  Lcd_cmd(0xc2);
  Lcd_str("access denied");
  }
}
}
}
