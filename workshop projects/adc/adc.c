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



void adc_init()
{
ADMUX|=(1<<REFS1)|(1<<REFS0);
ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

unsigned int adc_read(unsigned char channel)
{
channel&=0x00;
ADMUX|=channel;
ADCSRA|=(1<<ADSC);
while(!(ADCSRA &(1<<ADIF)));

ADCSRA|=(1<<ADIF);
return (ADC);

}
void main()
{ 
unsigned int a,d; 
DDRA=0xFF;
DDRC=0xFF;
adc_init();
Lcd_init();
Lcd_cmd(0x01);
_delay_ms(100);
while(1)
{
a=adc_read(0);
_delay_ms(100);
if(a>=60 && a<65)
{
d=20;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=65 && a<70)
{
d=19;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
else if (a>=70 && a<75)
{
d=18;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=75 && a<80)
{
d=17;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=80 && a<85)
{
d=16;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=85 && a<92)
{
d=15;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=92 && a<99)
{
d=14;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=99 && a<106)
{
d=13;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=106 && a<113)
{
d=12;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=113 && a<120)
{
d=11;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=120 && a<152)
{
d=10;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}

 else if (a>=152 && a<184)
{
d=9;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=184 && a<216)
{
d=8;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=216 && a<248)
{
d=7;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=248 && a<280)
{
d=6;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=280 && a<418)
{
d=5;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}

 else if (a>=418 && a<556)
{
d=4;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=556 && a<694)
{
d=3;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=694 && a<832)
{
d=2;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>=832 && a<950)
{
d=1;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}
 else if (a>950)
{
d=0;
Lcd_cmd(0xc2);
Lcd_num(d);
_delay_ms(100);
}

else
{
 Lcd_cmd(0x80);
 Lcd_str("Distance:");
 Lcd_cmd(0xc1);
 Lcd_str("out of range");
 _delay_ms(100);
 }

Lcd_cmd(0x80);
Lcd_str("Distance:");

Lcd_cmd(0xc6);
Lcd_str("cm");
_delay_ms(100);


}
}

