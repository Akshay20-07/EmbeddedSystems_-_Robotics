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

void Lcd_num(unsigned int i)
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

void adc_init()
{
ADMUX|=(1<<REFS0);
ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

unsigned int adc_read(unsigned char channel)
{
ADMUX=0x40|channel;
ADCSRA|=(1<<ADSC);
while(!(ADCSRA &(1<<ADIF)));
ADCSRA|=(1<<ADIF);
return (ADC);
}
void main()
{ 
unsigned int a; 
DDRA=0xFF;
DDRC=0xFF;
adc_init();
Lcd_init();
while(1)
{
a=adc_read(0);
Lcd_cmd(0x80);
Lcd_str("ADC_value:    ");
Lcd_cmd(0x8F);
Lcd_num(a);
_delay_ms(100);

a=(a*500)/1024;
Lcd_cmd(0xC5);
Lcd_num(a);
}
}

