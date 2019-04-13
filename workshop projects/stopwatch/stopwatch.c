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

void Lcd_num(unsigned char i)
{
unsigned char d;
Lcd_cmd(0x04);
 
d=i%10;
Lcd_data(d+48);
i/=10;
d=i%10;
Lcd_data(d+48);
i/=10;

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

/*void clock ()
{
char m,h,s;
for(h=0;h<=12;h++)
{
Lcd_cmd(0xC2);
Lcd_num(h);
//_delay_ms(100);
for(m=0;m<=59;m++)
{
Lcd_cmd(0xC6);
Lcd_num(m);
//_delay_ms(100);
for(s=0;s<=59;s++)
{
Lcd_cmd(0xC9);
Lcd_num(s);
_delay_ms(1000);
}
}
}
}
*/

void main()
{
unsigned int set=0;
unsigned char m,h,s;
DDRC=0xFF;
DDRB=0xFF;
DDRD=0xFF;	//col
DDRA=0x00;	//row
PORTA=0xFF;	//pull up
PORTD=0x00;
Lcd_init();
while(1)
{ 
	label:

Lcd_cmd(0x80);
Lcd_str("Stop Watch");
_delay_ms(100);
Lcd_cmd(0xC2);
Lcd_str("00");
Lcd_cmd(0xC5);
Lcd_str("00");
Lcd_cmd(0xC8);
Lcd_str("00");
Lcd_cmd(0xC4);
Lcd_data(':');
Lcd_cmd(0xC7);
Lcd_data(':');

PORTD=0x0E;
_delay_ms(1);
if((PINA&0x01)==0)
{
while(!(PINA&0x01))
{
 Lcd_cmd(0x80);
Lcd_str("   Start   ");
 
for(h=0;h<=12;h++)
{
Lcd_cmd(0xC3);
Lcd_num(h);
//_delay_ms(100);
for(m=0;m<=59;m++)
{
Lcd_cmd(0xC6);
Lcd_num(m);
//_delay_ms(100);
for(s=0;s<=59;s++)
{
Lcd_cmd(0xC9);
Lcd_num(s);
_delay_ms(1000);

if((PINA&0x02)==0)
{
while(!(PINA&0x02));
 set++;
 if(set==1)
 {
 Lcd_cmd(0x80);
 Lcd_str("   PAUSE   ");
 while((PINA&0x02)==0x02);
 }
 if(set==2)
 {
 Lcd_cmd(0x80);
 Lcd_str("   Start   ");
 set=0;
 }
}

if((PINA&0x04)==0)
{
 while((PINA&0x04)==0)
 {
 Lcd_cmd(0x80);
 Lcd_str("   Stop   ");
 _delay_ms(1000);
 goto label;
 }
}
}
}
}
}
}
}
}
