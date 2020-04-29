#include "USART.h"
#include "avr/io.h"

#define START			0x08       // TWI start
#define REP_START		0x10	   // TWI repeat start
#define MT_SLA_ACK		0x18	   // slave ACK has been received
#define MT_DATA_ACK		0x28	   // master ACK has been received
#define NACK			0x38	   // Arbitration lost or NACK
#define MR_SLA_ACK		0x40       // slave ACK has been received
#define SLA_W           0b11010000 // slave address + master write
#define SLA_R           0b11010001 // slave address + master read
#define READ_ONLY       0x00	   // Read only pointer register mode

enum state {Search, Track, Speed};
enum state drivestate = Search;

void PWM_init()
{
	/*set fast PWM mode with non-inverted output*/
	TCCR2 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRD|=(1<<PD7);  /*set OC0 pin as output*/
}

void TWI_init() {
	// Set I2C freq to 200kHz
	TWBR = 8;
	TWSR = (0 << TWPS1) | (0 << TWPS1);
}

int main(void){
	PWM_init();
	USART_init();
	TWI_init();
	char c;
	while(1){
		//c = USART_receive();
		//USART_send(c);
		/*
		if (c == '0') {
			OCR2 = 0;
			USART_send(c);
		} else if (c == '1') {
			OCR2 = 255 / 9 * 1;
			USART_send(c);
		} else if (c == '2') {
			OCR2 = 255 / 9 * 2;
			USART_send(c);
		} else if (c == '3') {
			OCR2 = 255 / 9 * 3;
			USART_send(c);
		} else if (c == '4') {
			OCR2 = 255 / 9 * 4;
			USART_send(c);
		} else if (c == '5') {
			OCR2 = 255 / 9 * 5;
			USART_send(c);
		} else if (c == '6') {
			OCR2 = 255 / 9 * 6;
			USART_send(c);
		} else if (c == '7') {
			OCR2 = 255 / 9 * 7;
			USART_send(c);
		} else if (c == '8') {
			OCR2 = 255 / 9 * 8;
			USART_send(c);
		} else if (c == '9') {
			OCR2 = 255 / 9 * 9;
			USART_send(c);
		}*/
		
		// Start
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		
		while (!(TWCR & (1<<TWINT)));
		
		if ((TWSR & 0xF8) != START) {
			USART_send('1');
			USART_send(TWSR);
		}
		
		TWDR = SLA_W;
		TWCR = (1<<TWINT) | (1<<TWEN);
		
		while (!(TWCR & (1<<TWINT)));
		
		if ((TWSR & 0xF8) != MT_SLA_ACK) {
			USART_send('2');
			USART_send(TWSR);
		}
		
		TWDR = 0x3B; // DATA
		TWCR = (1<<TWINT) | (1<<TWEN);
		
		while (!(TWCR & (1<<TWINT)));
		
		if ((TWSR & 0xF8) != MT_DATA_ACK) {
			USART_send('3');
			USART_send(TWSR);
		}
		
		// Repeat Start
		TWCR = (1<<TWINT) | (1<<TWSTA) | (1<<TWEN);
		
		while (!(TWCR & (1<<TWINT)));
		
		if ((TWSR & 0xF8) != START) {
			USART_send('4');
			USART_send(TWSR);
		}
		
		TWDR = SLA_R;
		TWCR = (1<<TWINT) | (1<<TWEN);
		
		while (!(TWCR & (1<<TWINT)));
		
		if ((TWSR & 0xF8) != MR_SLA_ACK) {
			USART_send('5');
			USART_send(TWSR);
		}
		
		while (!(TWCR & (1<<TWINT)));
		
		USART_send('D');
		USART_send(TWDR);
		// Mangler at teste om den skal sende stop
		
		// Stop
		TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWSTO);
		
		//while (!(TWCR & (1<<TWINT)));
		
		USART_send('S');
		
		/*
		int d=0;
		for(int i = 0; i < 1000; i++) {
			for(int i = 0; i < 10000; i++) {
				d+=1;
			}
		}*/
	}
	return 0;
}