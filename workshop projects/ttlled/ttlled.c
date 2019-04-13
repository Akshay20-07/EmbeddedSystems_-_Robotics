#include<avr/io.h>
#define F_CPU 16000000UL
#include<util/delay.h>

#define BAUD 9600UL
#define ubrr_value ((F_CPU/(BAUD*16UL)) -1)

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

void usart_init()
{
UBRRH=(ubrr_value>>8);
UBRRL= ubrr_value;
UCSRC|=(1<<URSEL)|(1<<UCSZ1)|(1<<UCSZ0);
UCSRB|=(1<<RXEN)|(1<<TXEN);
}
void usart_transmit(unsigned char d)
{
while(!(UCSRA&(1<<UDRE)));
UDR=d;
}
unsigned char usart_recieve()
{
while(!(UCSRA&(1<<RXC)));
return UDR;
}
 
 void usart_str (unsigned char *str)
{
while(*str)
usart_transmit(*str++);
}
int main()
{
unsigned char v;
DDRC=0xFF;
DDRB=0XFF;
DDRA=0xFF;
usart_init();
Lcd_init();
while(1)
{
v=usart_recieve();
Lcd_cmd(0x86);
Lcd_data(v);

if( v=='a'||  v=='A')
{
Lcd_cmd(0x01);
Lcd_cmd(0xC0);
Lcd_str("on");
usart_str("ON");
PORTB=0xFF;
_delay_ms(1000);
}
if(v=='q'|| v=='Q')
{
Lcd_cmd(0x01);
Lcd_cmd(0xC0);
Lcd_str("off");
usart_str("OFF");
PORTB=0x00;
_delay_ms(1000);
}
if(v=='z' ||  v=='Z')
{
Lcd_cmd(0x01);
Lcd_cmd(0xC0);
Lcd_str("buzzer");
usart_str("buzzer");
PORTA=0x80;
_delay_ms(100);
}

}
return 0;
}




