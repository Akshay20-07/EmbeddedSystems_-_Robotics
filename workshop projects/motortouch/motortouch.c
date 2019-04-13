#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

#define lcd PORTC
#define RS PC0
#define RW PC1
#define EN PC2

void adc_init()
{
ADMUX|=(1<<REFS0);
ADCSRA|=(1<<ADPS2)|(1<<ADPS1)|(1<<ADPS0)|(1<<ADEN);
}

unsigned int adc_read(unsigned char channel)
{
ADMUX=0x40|channel;
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
unsigned int x,y;
DDRC=0xff;
DDRA=0x00;
PORTB=0x00;
DDRB=0xFF;
lcd_init();
adc_init();
lcd_cmd(0x01);

while(1)
{
DDRA=0x05;
PORTA=0x03;
x=adc_read(1);
x=x/4;
lcd_cmd(0x80);
lcd_str("x: ");
lcd_cmd(0x84);
lcd_num(x);
DDRA=0x0A;
PORTA=0x06;
y=adc_read(2);
y=y/4;
lcd_cmd(0xC0);
lcd_str("y: ");
lcd_cmd(0xC4);
lcd_num(y);

if((x>220)&&(x<245))//&&(y>95)&&(y<175))
{
lcd_cmd(0x88);
lcd_str("forward");
PORTB=0x06;
_delay_ms(100);
}
if((x>160)&&(x<180))//&&(y>95)&&(y<175))
{
lcd_cmd(0x88);
lcd_str("backward");
PORTB=0x09;
_delay_ms(100);
}
if((x>180)&&(x<200))//&&(y>40)&&(y<95))
{
lcd_cmd(0x88);
lcd_str("RIGHT");
PORTB=0x0A;
_delay_ms(100);
}
if((x>245)&&(x<300))//&&(y>175)&&(y<220))
{
lcd_cmd(0x88);
lcd_str("LEFT");
PORTB=0x05;
_delay_ms(100);
}
if((x>200)&&(x<220))//&&(y>95)&&(y<175))
{
lcd_cmd(0x88);
lcd_str("STOP");
PORTB=0x00;
_delay_ms(100);
}

}
}
