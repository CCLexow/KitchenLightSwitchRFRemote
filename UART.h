/*
 * UART.h
 *
 */ 


#ifndef UART_H_
#define UART_H_

	#include <stdint.h>
	#include <avr/io.h>

	#define BAUD 57600
	
	void UART_init(void);

	void UART_putc(uint8_t u08Data);

	void UART_puts(char * pu08Data);

	void UART_Tx_uint08(uint8_t u08Send);

	void UART_Tx_uint16(uint16_t u16Send);

	void UART_Tx_uint32(uint32_t u32Send);

	void UART_Tx_int32(int32_t i32Send);

	uint16_t UART_Rx(void);

	void UART_txu08Bit_Masked(uint8_t u08TxData);
	void UART_txu16Bit_Masked(uint16_t u16TxData);

#endif /* UART_H_ */