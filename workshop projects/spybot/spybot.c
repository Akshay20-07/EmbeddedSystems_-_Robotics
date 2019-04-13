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
DDRB=0xff;
DDRA=0x00;
lcd_init();
adc_init();
int v;
while(1)
{
v=adc_read(1);

if(v>=400 && v<=600)
{lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_str("slow down");
PORTB=0b00010000;
PORTB=0b00000110;
_delay_ms(1000);
}

else if(v<400)
{lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_str("move");
PORTB=0b00100000;
PORTB=0b00000000;
_delay_ms(100);}


else if(v>600)
{
lcd_cmd(0x01);
lcd_cmd(0x80);
lcd_str("stop");
PORTB=0b01000000;
PORTB=0b00000110;
_delay_ms(100);}

}
}
