#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>

void pwm_init()
{
TCCR0|=(1<<WGM01)|(1<<WGM00)|(1<<CS01)|(1<<COM01);
 DDRB=(1<<PB3);
 }

unsigned char key()
{
unsigned char a;

while(1)
{
PORTD=0x0E;
_delay_ms(5);
if((PINA&0x01)==0)
{
while(!(PINA&0x01));
 OCR0=50;
 return OCR0;
}
if((PINA&0x02)==0)
{
while(!(PINA&0x02));
 OCR0=150;
 return OCR0;
}
 if((PINA&0x04)==0)
{
 while(!(PINA&0x04));
 OCR0=250;
 return OCR0;
}
 if((PINA&0x08)==0)
{
 while(!(PINA&0x08));
  OCR0=100;
  return OCR0;
} 


}
}

int main()
{
unsigned char ch;
pwm_init();
while(1)
{
ch=key();
_delay_ms(3000);
}
return 0;
}
