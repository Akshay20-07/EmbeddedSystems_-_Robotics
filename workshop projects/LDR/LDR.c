#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

#define lcd PORTC
#define RS PC0
#define RW PC1
#define EN PC2

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

while(!(ADCSRA&(1<<ADIF)));
ADCSRA|=(1<<ADIF);

return(ADC);
}

void lcd_cmd(unsigned char c)
{
lcd=(c & 0xF0);
lcd&=~(1<<RS);  //RS=0
lcd&=~(1<<RW);  //RW=0
lcd|=(1<<EN);   //EN=1
_delay_ms(10);
lcd&=~(1<<EN);  //EN=0
lcd=((c<<4) & 0xF0);
lcd&=~(1<<RS);
lcd&=~(1<<RW);
lcd|=(1<<EN);
_delay_ms(10);
lcd&=~(1<<EN);
}

void lcd_data(unsigned char c)
{
lcd=(c & 0xF0);
lcd|=(1<<RS);   //RS=1
lcd&=~(1<<RW);  //RW=0
lcd|=(1<<EN);   //EN=1
_delay_ms(10);
lcd&=~(1<<EN);  //EN=0
lcd=((c<<4) & 0xF0);
lcd|=(1<<RS);
lcd&=~(1<<RW);
lcd|=(1<<EN);
_delay_ms(10);
lcd&=~(1<<EN);
}


void lcd_init()
{
lcd_cmd(0x02);
lcd_cmd(0x28);
lcd_cmd(0x06);
lcd_cmd(0x0C);
}

void lcd_num(int i)
{
int d=0;
lcd_cmd(0x04);  //decreament cursor
while(i!=0)
{
d=i%10;
lcd_data(d+48);   //adding ASCII vslue of 0
i/=10;
}
lcd_cmd(0x06);  //increament cursor
}

void lcd_str(unsigned char *str)
{
while(*str)
lcd_data(*str++);
}

void main()
{
DDRC=0xff;
DDRA=0x00;
lcd_init();
adc_init();
int d;
int v;
while(1)
{
lcd_cmd(0x80);
lcd_str("color = ");
_delay_ms(100);

v=adc_read(1);

if(v>60 && v<100)
{lcd_cmd(0xc6);
lcd_str("voilet");
_delay_ms(100);}
else if(v>100 && v<150)
{lcd_cmd(0xc6);
lcd_str("indigo");
_delay_ms(100);}
else if(v>150 && v<200)
{lcd_cmd(0xc6);
lcd_str("blue");
_delay_ms(100);}
else if(v>200 && v<250)
{lcd_cmd(0xc6);
lcd_str("green");
_delay_ms(100);}
else if(v>250 && v<300)
{lcd_cmd(0xc6);
lcd_str("yellow");
_delay_ms(100);}
else if(v>300 && v<350)
{lcd_cmd(0xc6);
lcd_str("orange");
_delay_ms(100);}
else if(v>350 && v<400)
{lcd_cmd(0xc6);
lcd_str("red");
_delay_ms(100);}
else if(v>400)
{lcd_cmd(0xc6);
lcd_str("white");
_delay_ms(100);}
else
{lcd_cmd(0xc0);
lcd_str("unable to recognise");
_delay_ms(100);
lcd_cmd(0x01);}
}
}
