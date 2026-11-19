/*****************************************************************************
 *	    File: Final.c
 *    Author: James Myhill
 *   Created: 11/16/2026
 * Processor: ATmega128A (on the ReadyAVR board)
 *
 *****************************************************************************/

// define CPU speed (7.3728 MHz for the ATmega128A)
#define F_CPU   7372800UL

#define END_STRING  '\0'
#define CR          0x0D
#define LF          0x0A
#define ESC         0x1B

#include <avr/io.h>
#include <util/delay.h>
#include <stdio.h>  // for sprintf functionality
#include "UARTLibrary.h"
#include "UART0Library.h"
#include <avr/interrupt.h>       // Needed for AVR interrupt defines

#define BAUDRATE   9600 // standard values from 1200 to 115200
#define DATABITS      8 // 5-8
#define STOPBITS      1 // 1,2
#define PARITY        0 // 0=none, 1=odd, 2=even

//char text[40];
/*
void send_string(const char *cp) {
	while(*cp != END_STRING) {
		uart_tx(*cp++);
	}
}
*/


volatile char inp = 0; 

int main(void) {
	
	//uart_init(BAUDRATE,DATABITS,STOPBITS,PARITY);
	uart0_init(BAUDRATE,DATABITS,STOPBITS,PARITY);
	
	EIFR = (1<<INTF0)|(1<<INTF1)|(1<<INTF2)|(1<<INTF3)|(1<<INTF4);
	DDRB &= ~((1<<DDB0)|(1<<DDB1)|(1<<DDB2)|(1<<DDB3)|(1<<DDB4));
	PORTB |= (1<<PORTB0)|(1<<PORTB1)|(1<<PORTB2)|(1<<PORTB3)|(1<<PORTB4);
	//DDRD &= ~((1<<DDD0)|(1<<DDD1)|(1<<DDD2)|(1<<DDD3)|(1<<DDD4));
	DDRD &= ~((1 << 0)|(1 << 1)|(1 << 2)|(1 << 3));
	PORTD |= 0x0F;
	DDRE &= ~(1 << 4);
	PORTE |= (1 << 4);
	//PORTD |= ((1<<PORTD0)|(1<<PORTD1)|(1<<PORTD2)|(1<<PORTD3)); //might not need
	EICRA &= ~((1<<ISC01)|(1<<ISC00)|(1<<ISC11)|(1<<ISC10)|(1<<ISC21)|(1<<ISC20)|(1<<ISC31)|(1<<ISC30));
	EICRB |= (1<<ISC41);
	EICRA &= ~(1<<ISC40);
	//EICRA = (1<<ISC01)|(1<<ISC11)|(1<<ISC21)|(1<<ISC31);
	EIMSK |= (1<<INT0)|(1<<INT1)|(1<<INT2)|(1<<INT3)|(1<<INT4);
	//EIMSK &= ~(1<<INT3);// just testing NB must shift back for final implementation
	sei();
	
	//const char resetMsg[] = "\r\nTesting\r\n\0";	
	//send_string(resetMsg);
	
	while(1)
	{
		if(inp != 0)
		{
			char dir = inp;
			inp = 0;
			//uart_tx(dir);
			uart0_tx(dir);
			_delay_ms(30);
		}else{
			//uart_tx('0');
			uart0_tx('X');
			//_delay_ms(50);
		}
	}
	return 0;
}


	ISR(INT0_vect){
		inp = 'R';
	}
	
	ISR(INT1_vect){
		inp = 'D';
	}
	
	ISR(INT2_vect){
		inp = 'L';
	}
	
	ISR(INT3_vect){
		inp = 'U';
	}
	
	ISR(INT4_vect){
		inp = 'S';
	}