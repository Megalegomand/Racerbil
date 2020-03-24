#include "USART.h"
#include "avr/io.h"

void PWM_init()
{
	/*set fast PWM mode with non-inverted output*/
	TCCR2 = (1<<WGM00) | (1<<WGM01) | (1<<COM01) | (1<<CS00);
	DDRD|=(1<<PD7);  /*set OC0 pin as output*/
}

int main(void){
	PWM_init();
	USART_init();
	char c;
	while(1){
		USART_send('E');
		//c = USART_receive();
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
		}
	}
	return 0;
}

