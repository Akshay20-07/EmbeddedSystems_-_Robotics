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
channel&=0x01;
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
lcd_str("distance = ");
_delay_ms(100);

v=adc_read(1);

if(v>60 && v<65)
{lcd_cmd(0xc6);
lcd_str("20 cm");
_delay_ms(100);}
else if(v>65 && v<70)
{lcd_cmd(0xc6);
lcd_str("19 cm");
_delay_ms(100);}
else if(v>70 && v<75)
{lcd_cmd(0xc6);
lcd_str("18 cm");
_delay_ms(100);}
else if(v>75 && v<80)
{lcd_cmd(0xc6);
lcd_str("17 cm");
_delay_ms(100);}
else if(v>80 && v<85)
{lcd_cmd(0xc6);
lcd_str("16 cm");
_delay_ms(100);}
else if(v>85 && v<92)
{lcd_cmd(0xc6);
lcd_str("15 cm");
_delay_ms(100);}
else if(v>92 && v<96)
{lcd_cmd(0xc6);
lcd_str("14 cm");
_delay_ms(100);}
else if(v>96 && v<99)
{lcd_cmd(0xc6);
lcd_str("13 cm");
_delay_ms(100);}
else if(v>99 && v<113)
{lcd_cmd(0xc6);
lcd_str("12 cm");
_delay_ms(100);}
else if(v>113 && v<120)
{lcd_cmd(0xc6);
lcd_str("11 cm");
_delay_ms(100);}
else if(v>120 && v<152)
{lcd_cmd(0xc6);
lcd_str("10 cm");
_delay_ms(100);}
else if(v>152 && v<184)
{lcd_cmd(0xc6);
lcd_str("09 cm");
_delay_ms(100);}
else if(v>184 && v<216)
{lcd_cmd(0xc6);
lcd_str("08 cm");
_delay_ms(100);}
else if(v>216 && v<248)
{lcd_cmd(0xc6);
lcd_str("07 cm");
_delay_ms(100);}
else if(v>248 && v<280)
{lcd_cmd(0xc6);
lcd_str("06 cm");
_delay_ms(100);}
else if(v>280 && v<418)
{lcd_cmd(0xc6);
lcd_str("05 cm");
_delay_ms(100);}
else if(v>418 && v<556)
{lcd_cmd(0xc6);
lcd_str("04 cm");
_delay_ms(100);}
else if(v>556 && v<694)
{lcd_cmd(0xc6);
lcd_str("03 cm");
_delay_ms(100);}
else if(v>694 && v<832)
{lcd_cmd(0xc6);
lcd_str("02 cm");
_delay_ms(100);}
else if(v>832 && v<950)
{lcd_cmd(0xc6);
lcd_str("01 cm");
_delay_ms(100);}
else if(v>950 && v<970)
{lcd_cmd(0xc6);
lcd_str("00 cm");
_delay_ms(100);}

else
{lcd_cmd(0xc0);
lcd_str("out of range");
_delay_ms(100);
lcd_cmd(0x01);}
}
}
