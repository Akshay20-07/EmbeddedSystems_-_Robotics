#include<avr/io.h>
#include<avr/interrupt.h>
#include<util/delay.h>
#define F_CPU 1000000UL


#define Lcd PORTC
#define RS PC0
#define RW PC1
#define EN PC2

unsigned int count=0,min=0,sec=0,msec=0,hr=0;
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
int d=0;
Lcd_cmd(0x04);

d=i%10;
Lcd_data(d+48);
i/=10;
d=i%10;
Lcd_data(d+48);

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


ISR(TIMER1_COMPA_vect)
{
 count+=1;
 if(count==10)
 {
 count=0;
 msec++;
 if(msec==10)
 {
  msec=0;
  sec++;
  }
  if(sec==60)
  {
   sec=0;
   min++;
   }
   if(min==60)
   {
   min=0;
   hr++;
   }
   if(hr==24)
   {hr=0;
   }
   }
 }

void init_timer()
{
  OCR1A=10000;
  TCCR1B|=(1<<CS10)|(1<<WGM12);
  TIMSK|=(1<<OCIE1A);
}

int main()
{
//unsigned int h,m,s,ms;

DDRC=0xFF;

Lcd_init();
sei();

Lcd_cmd(0x80);
Lcd_str("digital clock");
while(1)
{

Lcd_cmd(0xc1);
Lcd_num(hr);
Lcd_cmd(0xc2);
Lcd_data(':');
Lcd_cmd(0xc4);
Lcd_num(min);
Lcd_cmd(0xc5);
Lcd_data(':');
Lcd_cmd(0xc7);
Lcd_num(sec);
Lcd_cmd(0xc8);
Lcd_data(':');
Lcd_cmd(0xCA);
Lcd_num(msec);
}
return 0;
}
