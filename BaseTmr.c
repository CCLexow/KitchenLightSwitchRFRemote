/*
 * BaseTmr.c
 *
 * Created: 05.01.2014 16:40:09
 *  Author: cc
 */ 
#include "BaseTmr.h"
#include <avr/io.h>

uint32_t BaseTmr_u32TimerTicks;

//inits timer 0 to create 10ms time base
void BaseTmr_Init(void)
{
	//set mode to CTC
	//WGM02 = 0 WGM01 = 1 WGM00 = 0
	//set prescaler to 1024
	//cs02=1 CS01=0 CS00=1
	//normal operation on port pins
	//no interrupts
	#if defined(_AVR_IOM88_H_) || defined(__AVR_ATmega168PA__)
		TIMSK0 = 0;
		TIFR0 = 0;
		TCCR0A = (1<<WGM01) | (0<<WGM00);
		TCCR0B = (0<<WGM02) | (0<<CS02) | (1<<CS01) | (1<<CS00);
		
		//set compare and timer count register
		OCR0A = 250;	 // equals 1ms @ 16MHz
		TCNT0 = 0;
	#elif defined(_AVR_IOM32_H_)
		// disable interrupts
		TIMSK &= ~(1<<OCIE0) & ~(1<<TOIE0);
		
		// clear interrupt flags
		TIFR  &= ~(1<<OCF0) & ~(1<<TOV0);
		
		//configure timer
		TCCR0 = 0b00001011;
		//		  ||||||||--->	CS00:	'1'	Set Prescaler to 64
		//		  |||||||---->	CS01:	'1'
		//		  ||||||----->	CS02:	'0'
		//		  |||||------>	WGM01:	'1'	Set mode to CTC
		//		  ||||------->	COMO0:	'0'	Normal port operation 
		//		  |||-------->	COMO1:	'0'
		//		  ||--------->	WGM00:	'0'
		//		  |---------->	FOC0:	'0'	dc
		
		//set compare and timer count register
		OCR0 = 250;	 // equals 1ms @ 16MHz
		TCNT = 0;	
				
	#endif
	
	// clear timer ticks
	BaseTmr_u32TimerTicks=0;
}



void BaseTmr_WaitForNextTimeSlot_10ms(void)
{
	uint8_t u08Cnt;
	
	//wait until 10ms are over
	for(u08Cnt=0;u08Cnt<10;u08Cnt++)
	{
		#if defined(__AVR_ATmega32__)
			TIFR |= (1<<OCF0);
			while((TIFR & (1<<OCF0)) != (1<<OCF0));
		#endif
		#if defined(__AVR_ATmega168PA__)
			TIFR0 |= (1<<OCF0A);
			while((TIFR0 & (1<<OCF0A)) != (1<<OCF0A));
		#endif
		
	}
	// add 10ms
	BaseTmr_u32TimerTicks+=10;
}

uint32_t BaseTmr_u32GetTimerTicks(void)
{
	return BaseTmr_u32TimerTicks;
}