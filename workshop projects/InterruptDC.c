#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>
#include <avr/interrupt.h>

#define lcd PORTC

#define rs  0
#define rw  1
#define en  2

void lcd_init();
void lcd_command(unsigned char);
void lcd_data(unsigned char);
void lcd_string(char *str);
void lcd_number(unsigned int);
void lcd_clear(unsigned char pos);

 char count=0;
 unsigned char hr,min,sec,msec;

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
	{
	hr=0;
	}
	
	
	}

}
void init_timer()
{
	OCR1A = 10000;
	TCCR1B |=(1<<CS10) | (1<<WGM12);
	TIMSK=(1<<OCIE1A);
	
}
int main()
{
DDRC=0xFF;

	lcd_init();	
	init_timer();
	sei();
	lcd_command(0x80);
	lcd_string("  Digital clock  ");
while(1)
{
	lcd_command(0xc4);
	lcd_number(hr);
	lcd_command(0xc5);
	lcd_data(':');
	lcd_command(0xc7);
	lcd_number(min);
	lcd_command(0xc8);
	lcd_data(':');
	lcd_command(0xca);
	lcd_number(sec);
	lcd_command(0xcb);
	lcd_data(':');
	lcd_command(0xcc);
	lcd_data(msec+48);	
				
}
return 0;
}

void lcd_init()
{
	lcd_command(0x02);
 	lcd_command(0x28);
	lcd_command(0x06);
	lcd_command(0x0c);
}
void lcd_command(unsigned char com)
{
	lcd = com & 0xF0;		//send higher bit

	lcd &= ~(1<<rs); 		//rs =0
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);

	lcd = (com<<4) & 0xF0;	//send lower bit

	lcd &= ~(1<<rs); 		//rs =0
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);
}
void lcd_data(unsigned char value)
{

	lcd =value & 0xF0;		//send higher bit

	lcd |= (1<<rs); 		//rs =1
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);


	lcd =(value<<4) & 0xF0;	//send lower bit

	lcd |= (1<<rs); 		//rs =1
	lcd &= ~(1<<rw);		//rw =0
	lcd |=(1<<en);			//en =1
	_delay_ms(1);
	lcd &= ~(1<<en);		//en =0
	_delay_ms(1);
}

void lcd_string(char *str)
{
	int i=0;
	while(str[i]!='\0')
	{
	lcd_data(str[i]);
	i++;
	}
}

void lcd_number(unsigned int value)
{
	unsigned int d=0;
	lcd_command(0x04);	//auto decrement mode

	d=value%10;
	lcd_data(d+48);
	value=value/10;
	d=value%10;
	lcd_data(d+48);
	
	lcd_command(0x06);	//auto increment mode
}
