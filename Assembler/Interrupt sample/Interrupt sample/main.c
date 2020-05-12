/*
 * Interrupt sample.c
 *
 * Created: 12/05/2020 15.59.48
 * Author : Philip
 */ 

#include <avr/io.h>
#include <avr/interrupt.h>
unsigned int stss=0;
char buffer[8];
int bufferpos = 0;
enum UARTState{Command, Set};
enum UARTState cUARTState = Command;	

ISR(USART_RXC_vect)
{
	if (!cUARTState=Set){
		switch(UDR){
			case: 1
			UDR=getAccelerometerH();
			addBuffer(getAccelerometerL());
			case: 2
			UDR=getLightsensorH();
			addBuffer(getLightsensorL());
			case: 3
			cUARTState=Set;
			stss=1;
			case: 4
			cUARTState=Set;
			stss=2;
		}
	}
	else{
		switch(stss){
			case: 1
			Engine=UDR;
			cUARTState=Command;
			case: 2
			EngineMode=UDR;
			cUARTState=Command;
		}
	}
		
		
}


ISR(USART_TXC_vect) {
	if (!bufferpos) {
		UDR = buffer[bufferpos];
		bufferpos -= 1;
	}
}

void addBuffer(char c) {
	if (bufferpos < 8) {
		buffer[bufferpos] = c;
		bufferpos += 1;
	}
}



