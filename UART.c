/*
 * UART.c
 *
 */ 

#include "UART.h"
#include <util/setbaud.h>

void UART_init(void)
{	
	/* 	UART INIT 
		8-N-1
		Baud rate defined in header file
	*/
	/*#if defined(__AVR_ATmega328P__) || defined(_AVR_ATmega88__)*/
	#if defined(_AVR_IOM88_H_) || defined(__AVR_ATmega168PA__) || defined(__AVR_ATmega328P__)
		UCSR0B = (0<<RXCIE0) | (0<<TXCIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02);			
		//UCSR0B = (0<<RXCIE0) | (0<<TXCIE0) | (1<<RXEN0) | (1<<TXEN0) | (0<<UCSZ02);			
		UCSR0C = (1<<UCSZ01) | (1<<UCSZ00);
		UBRR0H = UBRRH_VALUE;
		UBRR0L = UBRRL_VALUE;
		#if USE_2X
			UCSR0A |= (1<<U2X0);
		#else
			UCSR0A &= ~(1<<U2X0);
		#endif
		
	#else
		UCSRB = 0b00011000;
		/*		  ||||||||
				  |||||||--> TXB8: 	not used
				  ||||||---> RXB8: 	not used
				  |||||----> UCSZ2:	Set character size to 8 Bit (see also UCSRC)
				  ||||-----> TXEN: 	Enable Transmitter
				  |||------> RXEN:	Enable Receiver
				  ||-------> UDRIE:	Disable data register empty interrupt
				  |--------> TXCIE: Disable tx ready interrupt
				  ---------> RXCIE: Disable rx ready interrupt
		*/
		UCSRC = 0b10000110;
		/*		  ||||||||
				  |||||||--> UCPOL:   Not used in asynchronous mode (-> set to zero)
				  |||||----> UCSZ1:0: Set character size to 8 bit
				  ||||-----> USBS:	  Set to 1 Stop Bit
				  ||-------> UPM1:0:  Disable parity mode
				  |--------> UMSEL:   Set USART to asynchronous mode
				  ---------> URSEL:   Set to '1' to access UCSRC
		*/
	

		UBRRH = UBRRH_VALUE;
		UBRRL = UBRRL_VALUE;
   		#if USE_2X
   			UCSRA |= (1 << U2X);
   		#else
   			UCSRA &= ~(1 << U2X);
   		#endif
	#endif
}

void UART_putc(uint8_t u08Data)
{
	#if defined(__AVR_ATmega328P__) || defined(_AVR_IOM88_H_) || defined(__AVR_ATmega168PA__)
	    while(!(UCSR0A & (1<<UDRE0)));
		UDR0 = u08Data;
	#else
		/* Wait for empty transmit buffer */
		while ( !( UCSRA & (1<<UDRE)) );
		/* Put data into buffer, sends the data */
		UDR = u08Data;
	#endif
}

void UART_puts(char * pu08Data)
{
	while(*pu08Data){
		UART_putc(*pu08Data++);
	}
}

void UART_Tx_uint08(uint8_t u08Send)
{
    uint8_t u08ptr,u08i;
    uint8_t au08charBuffer[10];
    uint8_t u08temp,u08number;

    u08number = u08Send;
    u08ptr = 10;
    if (u08number==0){
    	UART_putc('0');
    }else{
		while (u08number != 0){
			u08ptr--;
			u08temp = u08number % 10;
			au08charBuffer[u08ptr] = u08temp;
			u08number = u08number / 10;
		}

		for(u08i = u08ptr;u08i<10 ;u08i++){
			switch(au08charBuffer[u08i]){
				case 0: UART_putc('0');break;
				case 1: UART_putc('1');break;
				case 2: UART_putc('2');break;
				case 3: UART_putc('3');break;
				case 4: UART_putc('4');break;
				case 5: UART_putc('5');break;
				case 6: UART_putc('6');break;
				case 7: UART_putc('7');break;
				case 8: UART_putc('8');break;
				case 9: UART_putc('9');break;
			}
		}
    }
}

void UART_Tx_uint16(uint16_t u16Send)
{
    uint8_t u08ptr,u08i;
    uint8_t au08charBuffer[10];
    uint16_t u16temp,u16number;

    u16number = u16Send;
    u08ptr = 10;
    if (u16number==0){
    	UART_putc('0');
    }else{
		while (u16number != 0){
			u08ptr--;
			u16temp = u16number % 10;
			au08charBuffer[u08ptr] = u16temp;
			u16number = u16number / 10;
		}

		for(u08i = u08ptr;u08i<10 ;u08i++){
			switch(au08charBuffer[u08i]){
				case 0: UART_putc('0');break;
				case 1: UART_putc('1');break;
				case 2: UART_putc('2');break;
				case 3: UART_putc('3');break;
				case 4: UART_putc('4');break;
				case 5: UART_putc('5');break;
				case 6: UART_putc('6');break;
				case 7: UART_putc('7');break;
				case 8: UART_putc('8');break;
				case 9: UART_putc('9');break;
			}
		}
    }
}

void UART_Tx_uint32(uint32_t u32Send)
{
    uint8_t u08ptr,u08i;
    uint8_t au08charBuffer[10];
    uint32_t u32temp,u32number;

    u32number = u32Send;
    u08ptr = 10;
    if (u32number==0){
    	UART_putc('0');
    }else{
		while (u32number != 0){
			u08ptr--;
			u32temp = u32number % 10;
			au08charBuffer[u08ptr] = u32temp;
			u32number = u32number / 10;
		}

		for(u08i = u08ptr;u08i<10 ;u08i++){
			switch(au08charBuffer[u08i]){
				case 0: UART_putc('0');break;
				case 1: UART_putc('1');break;
				case 2: UART_putc('2');break;
				case 3: UART_putc('3');break;
				case 4: UART_putc('4');break;
				case 5: UART_putc('5');break;
				case 6: UART_putc('6');break;
				case 7: UART_putc('7');break;
				case 8: UART_putc('8');break;
				case 9: UART_putc('9');break;
			}
		}
    }
}

void UART_Tx_int32(int32_t i32Send)
{
    uint8_t u08ptr,u08i;
    uint8_t au08charBuffer[10];
	int32_t i32number;
    uint32_t u32temp,u32number;

	i32number = i32Send;
    u08ptr = 10;
    if (i32number==0){
    	UART_putc('0');
    }else{
		if(i32number < 0){
			i32number = - i32number;
			UART_putc('-');
		}
		u32number = (uint32_t)i32number;
		while (u32number != 0){
			u08ptr--;
			u32temp = u32number % 10;
			au08charBuffer[u08ptr] = u32temp;
			u32number = u32number / 10;
		}

		for(u08i = u08ptr;u08i<10 ;u08i++){
			switch(au08charBuffer[u08i]){
				case 0: UART_putc('0');break;
				case 1: UART_putc('1');break;
				case 2: UART_putc('2');break;
				case 3: UART_putc('3');break;
				case 4: UART_putc('4');break;
				case 5: UART_putc('5');break;
				case 6: UART_putc('6');break;
				case 7: UART_putc('7');break;
				case 8: UART_putc('8');break;
				case 9: UART_putc('9');break;
			}
		}
    }
}

uint16_t UART_Rx(void)
{	
	uint16_t u16RetVal = 0xFFFF;
	/* Received data present? */
#if defined(__AVR_ATmega328P__) || defined(_AVR_IOM88_H_) || defined(__AVR_ATmega168PA__)
	if(UCSR0A & (1<<RXC0))
	{
		/* Get received data from buffer */
		u16RetVal = (uint16_t)UDR0;
	}
#else
	if(UCSRA & (1<<RXC))
	{
		/* Get received data from buffer */
		u16RetVal = (uint16_t)UDR;
	}
#endif	
	
	return u16RetVal;
}

void UART_txu08Bit_Masked(uint8_t u08TxData)
{
	//mask control bytes
	if(u08TxData >= 252)
	{
/*		UART_u08PutToTxBuffer(252);*/
		UART_putc(252);
		u08TxData = u08TxData - 252;
	}
	//UART_u08PutToTxBuffer(u08TxData);
	UART_putc(u08TxData);
}

void UART_txu16Bit_Masked(uint16_t u16TxData)
{

	volatile union xExtractU16Bytes
	{
		uint16_t u16Value;
		struct u08Help{
			uint8_t u08Lower;
			uint8_t u08Upper;
		}u08Bytes;
	}xExtractU16BytesUnion;

	//save value into union
	xExtractU16BytesUnion.u16Value = u16TxData;


	//transmit first high byte
	UART_txu08Bit_Masked(xExtractU16BytesUnion.u08Bytes.u08Upper);
	//and then low byte
	UART_txu08Bit_Masked(xExtractU16BytesUnion.u08Bytes.u08Lower);
}