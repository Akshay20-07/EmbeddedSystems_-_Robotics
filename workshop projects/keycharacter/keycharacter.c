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



unsigned char key1()
{
unsigned char a;
unsigned int i=0;
 inc=0;
while(1)
{
if((i==200)&&(inc==0))
{ 
loc+=1;
count=1;
inc=1;
}
else
{
i++;
}

PORTD=0x0E;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
 return '!';
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
 
 return 'a';
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
 return 'd';
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
 return 'g';
  //Lcd_cmd(0x01);
 
} 

PORTD=0x0D;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
return'j';
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
return 'm';
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
 return 'p';
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
 return 't';
} 

PORTD=0x0B;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
return 'w';
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
return del;
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
 return ' ';
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
return ' ';
} 

PORTD=0x07;
_delay_ms(5);
if((PINA&0x01)==0)
{

while(!(PINA&0x01));

return ' ';
 
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
 return ' ';
 
}
 if((PINA&0x04)==0)
{
while(!(PINA&0x04));
 return ' ';
 
}
 if((PINA&0x08)==0)
{
 
 while(!(PINA&0x08));
 return ' ';
 
} 


}
}

int main()
{
unsigned char key,pre_key=0,max,current_key;
DDRC=0xFF;
DDRB=0xFF;
DDRD=0xFF;	//col
DDRA=0x00;	//row
PORTA=0xFF;	//pull up
PORTD=0x00;
Lcd_init();
//ch=key();

loc=0x7F;
while(1)
{
key=key1();
if(key=='!')
max=15;
if(key>='a' && key>='o')
max=3;
if(key>='p')
max=4;

if(pre_key!=key)
{
if(inc==0)
loc+=1;
count=2;
current_key=key;
}

else if(pre_key==key && count>=1)
{
current_key=key+count-1;
if(count==max)
count=1;
else
count+=1;
}

if(key==del)
{
Lcd_cmd(loc);
Lcd_data(' ');
loc-=1;
}
else 
{
Lcd_cmd(loc);
Lcd_data(current_key);
}
pre_key=key;
}

return 0;
}

