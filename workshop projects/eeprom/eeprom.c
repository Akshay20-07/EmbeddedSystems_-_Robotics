#include<avr/io.h>
#define F_CPU 1000000UL
#include<util/delay.h>
#include<avr/eeprom.h>

/*
	#include<avr/eeprom.h>
	uint8_t eeprom_read_byte(const uint8_t *addr)
	void eeprom_write_byte(uint8_t *addr, uint8_t value)
	uint16_t eeprom_read_word(const uint16_t *addr)
	void eeprom_write_word(uint16_t *addr, uint16_t value)
	void eeprom_read_block(void *pointer_ram, const void *pointer_eeprom, size_t n)
	void eeprom_write_block(void *pointer_eeprom, const void *pointer_ram, size_t n)
*/

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

/*
	Steps to store data into eeprom:- 

	Initially you have to program the hex file into controller and
	then you have to program the .eep file into eeprom 
*/
	char eeprom_data[] EEMEM= "i3indya tech\0";

int main()
{	
	char ram_data[13];
	DDRC = 0XFF;

	lcd_init();
	
	eeprom_read_block(ram_data,eeprom_data,13);


	lcd_command(0x80);
	lcd_string(ram_data);
	//lcd_string("Enter password");
	

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
	
void lcd_clear(unsigned char pos)
{
	if(pos==1)
	{
	lcd_command(0x80);
	lcd_string("                ");
	}
	else if(pos==2)
	{
	lcd_command(0xc0);
	lcd_string("                ");
	}
	else if(pos==3)
	{
	lcd_command(0x80);
	lcd_string("                ");
	lcd_command(0xc0);
	lcd_string("                ");
	}

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

	if(value==0)
	lcd_data(value+48);

	while(value!=0)
	{
	d=value%10;
	lcd_data(d+48);
	value=value/10;
	}
	lcd_command(0x06);	//auto increment mode
}

