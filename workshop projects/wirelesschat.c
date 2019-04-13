#define F_CPU 1000000
#include<avr/io.h>
#include<util/delay.h>
#include<stdio.h>

#define USART_BAUDRATE 9600    // Baud Rate value
#define BAUD_PRESCALE ((F_CPU / (USART_BAUDRATE * 2UL)) - 1)
 
void USART_write_string(unsigned char *str);
void usart_init(void);
void usart_putch(unsigned char send);
unsigned int usart_getch(void);

void LCD_cmd(unsigned char cmd);
void LCD_data(unsigned char data);
void LCD_init();
void disp_cmd(unsigned char c);
void disp_data(unsigned char d);
unsigned int pass();

int x=0x80, t=65,c=0, LUC=1,urc=0x80, p =91,q=92,NUM=0,m,n=0;;
int main()
{   int i,passok,j;
	unsigned char value;
    char passmatch[4];
	char prepass[]="ABCD";
	unsigned char pas[]="ABCD";
	unsigned char q[4];
	DDRA=0xf0;
	PORTA=0x0f;
	DDRC=0xff;
    DDRB=0XFF;
	LCD_init();
    usart_init();        // initialization of USART
		disp_cmd(0x01);
		_delay_ms(50);
		disp_cmd(0x80);
		LCD_string("R3,C1 for R mode");
		disp_cmd(0xc0);
		LCD_string("R3,C2 for S mode");
		_delay_ms(200);
	while(1)
	{ 	
	 main : PORTB=0x0b;
	  _delay_ms(5);
	  if(PINA==0x0e)
	  {	
	  againr : disp_cmd(0x01);
		_delay_ms(50);
	  	disp_cmd(0xc0);
		LCD_string("*Device Pairing*");
		_delay_ms(200);
		disp_cmd(0x80);
		for(i=0;i<4;i++)
		{	
	    	value=usart_getch();
			passmatch[i]=value;
			disp_data('*');
			//disp_data(passmatch[i]);
			_delay_ms(50);
		}
		for(i=0;i<4;i++)
		{
		if(passmatch[i]==prepass[i])
		j=j+1;
		}


		if(j==4)
		{disp_cmd(0x01);
		_delay_ms(50);
		disp_cmd(0xc3);
		LCD_string("Receving...");
		_delay_ms(200);
    		//while(1)
    		//{   
			msgrcv();
			_delay_ms(100);		
			//}
			j=0;
			goto main;
		}
			else
			{disp_cmd(0x80);LCD_string("Try Again..!");j=0;_delay_ms(2000);disp_cmd(0x80);LCD_string("                ");_delay_ms(50); goto againr;}
	  }
	  if(PINA==0x0d)
	   {
	   agains :disp_cmd(0x01);
		_delay_ms(50);
		disp_cmd(0xc0);
		LCD_string("*Device Pairing*");
		_delay_ms(200);
		disp_cmd(0x80);
		for(m=0;m<4;m++)
		{
		value=pass();
		q[m]=value;
		disp_data('*');
		//disp_data(q[i]);
		_delay_ms(50);
		}
		for(m=0;m<4;m++)
		{
		 if(q[m]==pas[m])
		 n=n+1;
		}
		if(n==4)
		{disp_cmd(0x01);
		_delay_ms(50);
		disp_cmd(0xc3);
		LCD_string("Sending...");
		_delay_ms(200);
		//	while(1)
		//	{
				key();
				_delay_ms(200);
		//	}
		n=0;
		goto main;
		}
		else
		{
		disp_cmd(0x80);	LCD_string("Try Again..!");	n=0;_delay_ms(2000);disp_cmd(0x80);LCD_string("                ");_delay_ms(50); goto agains;
		}
			
	  }
    }
    return 0;
}
 
 
void usart_init()
{
    UCSRB |= (1 << RXEN)|(1<<TXEN);   // Turn on the transmission and reception circuitry
    UCSRC |= (1 << URSEL)  | (1<<USBS)| (1 << UCSZ0) | (1 << UCSZ1);                                            // Use 8-bit character sizes
    UBRRL = BAUD_PRESCALE;            // Load lower 8-bits of the baud rate value into the low byte of the UBRR register
    UBRRH = (BAUD_PRESCALE >> 8); // Load upper 8-bits of the baud rate value..
                                    // into the high byte of the UBRR register
}
 
unsigned int usart_getch()
{    unsigned int ret;
    while ((UCSRA & (1 << RXC)) == 0);
    {   
    }    // Do nothing until data has been received and is ready to be read from UDR
   
    return UDR; // return the byte
}
 

void usart_putch(unsigned char send)
{    while(!(UCSRA & (1<<UDRE)))
   {
   }
   UDR=send;
}

void putstr(char *send)
{
	int i=0;
  	while(send[i]!='\0')
   		{
		while(!(UCSRA & (1<<UDRE)));
	
		UDR=send[i];
		i++;
		};
}


void LCD_init()
{	
	disp_cmd(0x02);
	disp_cmd(0x28);   	//another way of writing cmd 0x28;///LCD_cmd(0x20);	///LCD_cmd(0x08);		
	disp_cmd(0x06);	
	disp_cmd(0x0e);	
}

void LCD_cmd(unsigned char saur)
{
PORTC=saur;
PORTC |=0x04;
_delay_ms(1);
PORTC &=~0x04;
}
void LCD_data(unsigned char saurabh)
{
PORTC=saurabh;
PORTC |=0x05; 
_delay_ms(1);
PORTC &=~0x04; 
}
void disp_cmd(unsigned char saur)       
{
LCD_cmd(saur & 0xF0);
LCD_cmd(((saur<<4)&0xF0));
}

void disp_data(unsigned char saurabh)
{
LCD_data(saurabh & 0xF0);
LCD_data(((saurabh<<4)&0xF0));
}

void LCD_string(unsigned char *str)
{
int i=0;
while(str[i]!='\0')
{
disp_data(str[i]);
disp_cmd(0x06);
i++;
}
}

void number_LCD(unsigned int abc)      ///// number in a string function   //////
{	disp_cmd(0x04);
	unsigned int d=0;
	while(abc!=0)
	{	d=abc%10;
		disp_data(d+48);
		abc=abc/10;
	}
}


void msgrcv()
{
unsigned int val,h=1;
while(h)
{
		val=usart_getch();
		PORTB=0x0b;
		_delay_ms(5);
	if(val==94)
	{
			disp_cmd(0x80);	
			disp_cmd(0x01);	
			x=0x80;n=0;h=0;
			_delay_ms(200);
			disp_cmd(0x80);
			LCD_string("R3,C1 for R mode");
			disp_cmd(0xc0);
			LCD_string("R3,C2 for S mode");
			_delay_ms(250);
	}
	
	if((val>=65) && (val<=90))
	{	
		if(val==65)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==66)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==67)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==68)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==69)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==70)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==71)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==72)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==73)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==74)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==75)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==76)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==77)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==78)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==79)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==80)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==81)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==82)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==83)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==84)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==85)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==86)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==87)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==88)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==89)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==90)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		x++;
	}
	else if((val>=97) && (val<=122))
	{	
		if(val==97)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==98)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==99)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==100)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==101)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==102)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==103)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==104)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==105)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==106)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==107)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==108)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==109)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==110)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==111)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==112)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==113)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==114)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==115)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==116)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==117)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==118)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		if(val==119)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
		else if(val==120)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==121)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
		else if(val==122)
		{x--;
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}		
		x++;
	}
	if((val>=48) && (val<=57))
	{
	if(val==49)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
	 if(val==50)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
	if(val==51)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
	if(val==53)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}	
	if(val==54)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);		
		}
	 if(val==55)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
	if(val==56)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}
	if(val==52)
		{
		disp_cmd(x);
		disp_data(val);
		_delay_ms(300);	
		}		
		x++;
	}	
	else if(val==91)
		{
		disp_cmd(x);
		disp_data(' ');
		_delay_ms(300);		
		x++;
		}
	else if(val==92)
	{	x--;
			disp_cmd(x);
			disp_data(' ');
			_delay_ms(1000);
	}
	else if(val==93)
	{	x=0x80;
			disp_cmd(x);
			LCD_string("                ");
			_delay_ms(500);
	}
}
}


//////////////////////////////

unsigned int pass()
{int i=1;
while(i==1)
	{	PORTB=0x0e;
		_delay_ms(5);
		if(PINA==0x0e)
		{i=0;_delay_ms(400); usart_putch(t); return 'A';}
		if(PINA==0x0d)
		{i=0;_delay_ms(400); usart_putch(t+1); return 'B';}
		if(PINA==0x0b)
		{i=0;_delay_ms(400); usart_putch(t+2); return 'C';}
		if(PINA==0x07)
		{i=0;_delay_ms(400); usart_putch(t+3); return 'D';}
	}
}

///////////////////////////////



//////////////////////////////

void key()
{int h=1;
  while(h)
  {
	{	PORTB=0x0e;
		_delay_ms(5);
		if(PINA==0x0e)
		{ c=65;
			disp_cmd(x);		
			if(LUC==2)
			{
			printc();
			}
			if(LUC==1)
			{c=97;
			printc();
			}
			if(NUM==1)
			{
			c=49;
			printc();
			}
			_delay_ms(500);	
		for(int i=0;i<400;i++)
  		 {
			if(PINA == 0x0e)
			{ c=66;
				disp_cmd(x);		
				if(LUC==2)
				{
				printc();
				}
				if(LUC==1)
				{c=98;
				printc();
				}
				_delay_ms(500);
			for(int j=0;j<4000;j++)
		 		 {
					if(PINA == 0x0e)
					{ c=67;
						disp_cmd(x);		
		 				if(LUC==2)
						{
						printc();
						}
						if(LUC==1)
						{c=99;
						printc();
						}
					_delay_ms(500);
					}
         		 }
	
			}
		  }
		  x++;
		}			
	else if(PINA == 0x0d)
		{ c=68;	
			disp_cmd(x);	
			if(LUC==2)
			{
			printc();
			}
			if(LUC==1)
			{c=100;
			printc();
			}
			if(NUM==1)
			{
			c=50;
			printc();
			}
			_delay_ms(500);
		for(int i=0;i<4000;i++)
		  {
			if(PINA == 0x0d)
			{ c=69;			
				disp_cmd(x);	
				if(LUC==2)
				{
				printc();
				}
				if(LUC==1)
				{c=101;
				printc();
				}
				_delay_ms(500);
				for(int j=0;j<400;j++)
		 		 {
					if(PINA == 0x0d)
					{ c=70;
						disp_cmd(x);		
					if(LUC==2)
					{
					printc();
					}
					if(LUC==1)
					{c=102;
					printc();
					}
					_delay_ms(500);
					}
         		 }
			}
          }
		  x++;
		}
			else if(PINA == 0x0b)
		{ c=71;	
			disp_cmd(x);	
			if(LUC==2)
			{
			printc();
			}
			if(LUC==1)
			{c=103;
			printc();
			}
			if(NUM==1)
			{
			c=51;
			printc();
			}
			_delay_ms(500);
		for(int i=0;i<4000;i++)
		  {
			if(PINA == 0x0b)
			{ c=72;			
				disp_cmd(x);	
				if(LUC==2)
				{
				printc();
				}
				if(LUC==1)
				{c=104;
				printc();
				}
				_delay_ms(500);
				for(int j=0;j<400;j++)
		 		 {
					if(PINA == 0x0b)
					{ c=73;
						disp_cmd(x);		
						if(LUC==2)
						{
						printc();
						}
						if(LUC==1)
						{c=105;
						printc();
						}
					_delay_ms(500);
					}
         		 }
			}
          }
		  x++;
		}
		  	else if(PINA == 0x07)
		{ c=74;	
			disp_cmd(x);	
			if(LUC==2)
			{
			printc();
			}
			if(LUC==1)
			{c=106;
			printc();
			}
			if(NUM==1)
			{
			c=52;
			printc();
			}
			_delay_ms(500);
		for(int i=0;i<4000;i++)
		  {
			if(PINA == 0x07)
			{ c=75;			
				disp_cmd(x);	
				if(LUC==2)
				{
				printc();
				}
				if(LUC==1)
				{c=107;
				printc();
				}
				_delay_ms(500);
				for(int j=0;j<400;j++)
		 		 {
					if(PINA == 0x07)
					{ c=76;
						disp_cmd(x);		
						if(LUC==2)
						{
						printc();
						}
						if(LUC==1)
						{c=108;
						printc();
						}
					_delay_ms(500);
					}
         		 }
			}
          }
		  x++;
		}
	}



	{	PORTB=0x0d;
		_delay_ms(5);
		if(PINA==0x0e)
		{ c=77;
			disp_cmd(x);		
			if(LUC==2)
			{
			printc();
			}
			if(LUC==1)
			{c=109;
			printc();
			}
			if(NUM==1)
			{
			c=53;
			printc();
			}
			_delay_ms(500);
		for(int i=0;i<400;i++)
  		 {
			if(PINA == 0x0e)
			{ c=78;
				disp_cmd(x);		
				if(LUC==2)
				{
				printc();
				}
				if(LUC==1)
				{c=110;
				printc();
				}
			_delay_ms(500);
			for(int j=0;j<4000;j++)
		 		 {
					if(PINA == 0x0e)
					{ c=79;
						disp_cmd(x);		
		 				if(LUC==2)
						{
						printc();
						}
						if(LUC==1)
						{c=111;
						printc();
						}	
					_delay_ms(500);
					}
         		 }
	
			}
		  }
		  x++;
		}			
		else if(PINA == 0x0d)
		{ c=80;	
			disp_cmd(x);	
			if(LUC==2)
			{
			printc();
			}
			if(LUC==1)
			{c=112;
			printc();
			}
			if(NUM==1)
			{
			c=54;
			printc();
			}
			_delay_ms(500);
		for(int i=0;i<4000;i++)
		  {
			if(PINA == 0x0d)
			{ c=81;			
				disp_cmd(x);	
				if(LUC==2)
				{
				printc();
				}
				if(LUC==1)
				{c=113;
				printc();
				}
				_delay_ms(500);
				for(int j=0;j<400;j++)
		 		 {
					if(PINA == 0x0d)
					{ c=82;
						disp_cmd(x);		
						if(LUC==2)
						{
						printc();
						}
						if(LUC==1)
						{c=114;
						printc();
						}
					_delay_ms(500);
						for(int j=0;j<100;j++)
		 				 {
							if(PINA == 0x0d)
							{ c=83;
								disp_cmd(x);		
								if(LUC==2)
								{
								printc();
								}
								if(LUC==1)
								{c=115;
								printc();
								}
							_delay_ms(500);
							}
         				 }
					}
         		 }
			 }
          }
		  x++;
		}
			else if(PINA == 0x0b)
		{ c=84;	
			disp_cmd(x);	
			if(LUC==2)
			{
			printc();
			}
			if(LUC==1)
			{c=116;
			printc();
			}
			if(NUM==1)
			{
			c=55;
			printc();
			}
			_delay_ms(500);
		for(int i=0;i<4000;i++)
		  {
			if(PINA == 0x0b)
			{ c=85;			
				disp_cmd(x);	
				if(LUC==2)
				{
				printc();
				}
				if(LUC==1)
				{c=117;
				printc();
				}
				_delay_ms(500);
				for(int j=0;j<400;j++)
		 		 {
					if(PINA == 0x0b)
					{ c=86;
						disp_cmd(x);		
						if(LUC==2)
						{
						printc();
						}
						if(LUC==1)
						{c=118;
						printc();
						}
					_delay_ms(500);
					}
         		 }
			}
          }
		  x++;
		}
		  	else if(PINA == 0x07)
		{ c=87;	
			disp_cmd(x);	
			if(LUC==2)
			{
			printc();
			}
			if(LUC==1)
			{c=119;
			printc();
			}
			if(NUM==1)
			{
			c=56;
			printc();
			}
			_delay_ms(500);
		for(int i=0;i<4000;i++)
		  {
			if(PINA == 0x07)
			{ c=88;			
				disp_cmd(x);	
				if(LUC==2)
				{
				printc();
				}
				if(LUC==1)
				{c=120;
				printc();
				}
				_delay_ms(500);
				for(int j=0;j<400;j++)
		 		 {
					if(PINA == 0x07)
					{ c=89;
						disp_cmd(x);		
						if(LUC==2)
						{
						printc();
						}
						if(LUC==1)
						{c=121;
						printc();
						}
					_delay_ms(500);
						for(int j=0;j<100;j++)
		 				 {
							if(PINA == 0x07)
							{ c=90;
								disp_cmd(x);		
								if(LUC==2)
								{
								printc();
								}
								if(LUC==1)
								{c=122;
								printc();
								}
								_delay_ms(500);
							}
         				 }
					}
         		 }
			 }
          }
		  x++;
		}
   	}


	{	PORTB=0x0b;
		_delay_ms(5);
		if(PINA==0x0e)
		{ 
		}

		else if(PINA==0x0d)
		{ 
		}

		else if(PINA==0x0b)
		{ 
		}

		else if(PINA==0x07)
		{ 
			disp_cmd(0x80);	
			disp_cmd(0x01);	
			x=0x80;n=0;h=0;
			_delay_ms(200);
			disp_cmd(0x80);
			LCD_string("R3,C1 for R mode");
			disp_cmd(0xc0);
			LCD_string("R3,C2 for S mode");
			_delay_ms(250);
			usart_putch(94);
		}
	}



	{	PORTB=0x07;
		_delay_ms(5);
		if(PINA==0x0e)
		{NUM=1;
		LUC=0;
		_delay_ms(400);
		}

		else if(PINA==0x0d)
		{ 
			disp_cmd(x);
			disp_data(' ');
			usart_putch(91);
			_delay_ms(1000);
			x++;
		}

		else if(PINA==0x0b)
		{ LUC=2;
			NUM=0;
			_delay_ms(400);
			for(int i=0;i<4000;i++)
			{
				if(PINA==0x0b)
				{	NUM=0;
					LUC=1;
					_delay_ms(400);
				}
			}
		}

		else if(PINA==0x07)
		{	usart_putch(92);
			x--;
			disp_cmd(x);
			disp_data(' ');
			_delay_ms(1000);
			for(int i=0;i<2000;i++)
			{
				if(PINA==0x07)
				{ 		usart_putch(93);
					 	disp_cmd(urc);
						LCD_string("                ");
						_delay_ms(400);
						x=0x80;
				}
			}
		}
	}
  }
}

void printc()
{//	disp_cmd(x);	
disp_data(c);
usart_putch(c);
_delay_ms(50);
}