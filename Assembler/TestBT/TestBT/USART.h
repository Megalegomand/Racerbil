// Define H file
#ifndef USART_H_
#define USART_H_

// Define CPU clock speed
// This is also needed for delay.h
#define F_CPU 16000000UL
#define BAUD 9600

// Include libraries
#include <avr/io.h>
#include <util/setbaud.h>
#include <util/delay.h>

void USART_init(){
	UBRRH = UBRRH_VALUE;
	UBRRL = UBRRL_VALUE;
	UCSRB = (1<<RXEN)|(1<<TXEN);
	UCSRC = (1<<UCSZ0)|(1<<UCSZ1)|(1<<URSEL);
}

/* Function to receive byte/char */
unsigned char USART_receive(){
	while(!(UCSRA & (1<<RXC)));
	return UDR;
}
/* Function to send byte/char */
void USART_send( unsigned char data){
	while(!(UCSRA & (1<<UDRE)));
	UDR = data;
}
/* Send string */
void USART_putstring(char* StringPtr){
	while(*StringPtr != 0x00){
		USART_send(*StringPtr);
	StringPtr++;}
}



#endif /* USART_H_ */