/*******************************************************
Chip type               : ATmega128
Program type            : Application
AVR Core Clock frequency: 10,000000 MHz
Memory model            : Small
External RAM size       : 0
Data Stack size         : 1024
*******************************************************/

#include <mega128.h>
#include <delay.h>
#include <stdio.h>

// Alphanumeric LCD functions
#include <alcd.h>

// Declare your global variables here
unsigned char add, start, shutdown;

// External Interrupt 0 service routine
interrupt [EXT_INT0] void ext_int0_isr(void)
{
// Place your code here
shutdown=0;
}

// External Interrupt 1 service routine
interrupt [EXT_INT1] void ext_int1_isr(void)
{
// Place your code here
start=1;
}

// External Interrupt 2 service routine
interrupt [EXT_INT2] void ext_int2_isr(void)
{
// Place your code here
add+=1;
}

// External Interrupt 3 service routine
interrupt [EXT_INT3] void ext_int3_isr(void)
{
// Place your code here
add=0;
}

void main(void)
{
// Declare your local variables here
unsigned char text[16];

// Input/Output Ports initialization
// Port A initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRA=(1<<DDA7) | (1<<DDA6) | (1<<DDA5) | (1<<DDA4) | (1<<DDA3) | (1<<DDA2) | (1<<DDA1) | (1<<DDA0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=1 Bit2=0 Bit1=0 Bit0=0 
PORTA=(0<<PORTA7) | (0<<PORTA6) | (0<<PORTA5) | (1<<PORTA4) | (0<<PORTA3) | (0<<PORTA2) | (0<<PORTA1) | (0<<PORTA0);

// Port C initialization
// Function: Bit7=Out Bit6=Out Bit5=Out Bit4=Out Bit3=Out Bit2=Out Bit1=Out Bit0=Out 
DDRC=(1<<DDC7) | (1<<DDC6) | (1<<DDC5) | (1<<DDC4) | (1<<DDC3) | (1<<DDC2) | (1<<DDC1) | (1<<DDC0);
// State: Bit7=0 Bit6=0 Bit5=0 Bit4=0 Bit3=0 Bit2=0 Bit1=0 Bit0=0 
PORTC=(0<<PORTC7) | (0<<PORTC6) | (0<<PORTC5) | (0<<PORTC4) | (0<<PORTC3) | (0<<PORTC2) | (0<<PORTC1) | (0<<PORTC0);

// Port D initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRD=(0<<DDD7) | (0<<DDD6) | (0<<DDD5) | (0<<DDD4) | (0<<DDD3) | (0<<DDD2) | (0<<DDD1) | (0<<DDD0);
// State: Bit7=T Bit6=T Bit5=T Bit4=P Bit3=P Bit2=P Bit1=P Bit0=P 
PORTD=(0<<PORTD7) | (0<<PORTD6) | (0<<PORTD5) | (1<<PORTD4) | (1<<PORTD3) | (1<<PORTD2) | (1<<PORTD1) | (1<<PORTD0);

// Port E initialization
// Function: Bit7=In Bit6=In Bit5=In Bit4=In Bit3=In Bit2=In Bit1=In Bit0=In 
DDRE=(0<<DDE7) | (0<<DDE6) | (0<<DDE5) | (0<<DDE4) | (0<<DDE3) | (0<<DDE2) | (0<<DDE1) | (0<<DDF0);
// State: Bit7=T Bit6=T Bit5=T Bit4=T Bit3=T Bit2=P Bit1=P Bit0=P 
PORTE=(0<<PORTE7) | (0<<PORTE6) | (0<<PORTE5) | (0<<PORTE4) | (0<<PORTE3) | (1<<PORTE2) | (1<<PORTE1) | (1<<PORTE0);

// External Interrupt(s) initialization
// INT0: On
// INT0 Mode: Falling Edge
// INT1: On
// INT1 Mode: Falling Edge
// INT2: On
// INT2 Mode: Falling Edge
// INT3: On
// INT3 Mode: Falling Edge
EICRA=(1<<ISC31) | (0<<ISC30) | (1<<ISC21) | (0<<ISC20) | (1<<ISC11) | (0<<ISC10) | (1<<ISC01) | (0<<ISC00);
EICRB=(0<<ISC71) | (0<<ISC70) | (0<<ISC61) | (0<<ISC60) | (0<<ISC51) | (0<<ISC50) | (0<<ISC41) | (0<<ISC40);
EIMSK=(0<<INT7) | (0<<INT6) | (0<<INT5) | (0<<INT4) | (1<<INT3) | (1<<INT2) | (1<<INT1) | (1<<INT0);
EIFR=(0<<INTF7) | (0<<INTF6) | (0<<INTF5) | (0<<INTF4) | (1<<INTF3) | (1<<INTF2) | (1<<INTF1) | (1<<INTF0);

// Alphanumeric LCD initialization
// Connections are specified in the
// Project|Configure|C Compiler|Libraries|Alphanumeric LCD menu:
// RS - PORTC Bit 0
// RD - PORTC Bit 2
// EN - PORTC Bit 1
// D4 - PORTC Bit 4
// D5 - PORTC Bit 5
// D6 - PORTC Bit 6
// D7 - PORTC Bit 7
// Characters/line: 16
lcd_init(16);

// Global enable interrupts
#asm("sei")
start=0;

while (1)
      {
      // Place your code here
      cycle:
      while(start==0)
        {
        PORTA=0b00010000;
        sprintf(text,"Siklus : %d",add);
        lcd_gotoxy(0,0);
        lcd_puts(text);
        goto cycle;
        }
      
      if(add==0)
        {
        start=0;        
        goto cycle;
        }
        
      else if(add>=1)
        {
        shutdown=1;
        lcd_clear();
        goto inflow;
        }
        
      inflow:
      start=0;
      sprintf(text,"Siklus : %d",add);
      lcd_gotoxy(0,0);
      lcd_puts(text);      
      lcd_gotoxy(0,1);
      lcd_putsf("Isi Tank");      
      PORTA=0b00010011;
      if(shutdown==0)
        {
        lcd_clear();
        goto emergency;
        }
            
      else if(start==1)
        {
        start=0;
        PORTA=0b00010000;
        lcd_clear();
        lcd_gotoxy(0,0);
        lcd_putsf("BREAK!");
        loop1:
        if(start==1)
            {
            lcd_clear();
            goto inflow;
            }
        goto loop1;
        }
        
      else if(PINE.2==1)
        {
        lcd_clear();
        goto htr_stir;
        }

      else
        {
        goto inflow;
        }

      htr_stir:
      start=0;
      sprintf(text,"Siklus : %d",add);
      lcd_gotoxy(0,0);
      lcd_puts(text);
      lcd_gotoxy(0,1);
      lcd_putsf("Aduk");
      PORTA=0b00001000;
      if(shutdown==0)
        {
        lcd_clear();
        goto emergency;
        }
            
      else if(start==1)
        {
        start=0;
        PORTA=0b00010000;
        lcd_clear();
        lcd_gotoxy(0,0);
        lcd_putsf("BREAK!");
        loop2:
        if(start==1)
            {
            lcd_clear();
            goto htr_stir;
            }
        goto loop2;
        }
        
      else if(PINE.1==0)
        {
        lcd_clear();
        goto outflow;
        }
        
      else
        {
        goto htr_stir;
        }
      
      outflow:
      start=0;
      sprintf(text,"Siklus : %d",add);
      lcd_gotoxy(0,0);
      lcd_puts(text);
      lcd_gotoxy(0,1);
      lcd_putsf("Buang");
      PORTA=0b00010100;
      if(shutdown==0)
        {
        lcd_clear();
        goto emergency;
        }
            
      else if(start==1)
        {
        start=0;
        PORTA=0b00010000;
        lcd_clear();
        lcd_gotoxy(0,0);
        lcd_putsf("Istirahat");
        loop3:
        if(start==1)
            {
            lcd_clear();
            goto outflow;
            }
        goto loop3;
        }
        
      else if(PINE.0==0)
        {
        if(add==0)
            {
            lcd_clear();
            goto cycle;
            }
        else if(add>0)
            {
            add-=1;
            if(add==0)
                {
                lcd_clear();
                goto cycle;
                }
            else
                {
                lcd_clear();
                goto inflow;
                } 
            }
        }
        
      else
        {
        goto outflow;
        }
          
      emergency:
      lcd_gotoxy(0,0);
      lcd_putsf("Emergency!!!");  
      PORTA=0b01110000;
      loop4:
      goto loop4;
            
      }
}
