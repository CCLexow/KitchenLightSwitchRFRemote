/*
 * ADC.c
 *
 * Created: 05.01.2014 17:29:36
 *  Author: cc
 */ 

#include "ADC.h"
#include <avr/io.h>

void ADC_init(TADC_RunModes xADCRunMode)
{
		ADCSRA =	0b00000111;
		//			  ||||||||--->	ADPS0:	'1'	Set Prescaler to 128
		//			  |||||||---->	ADPS1:	'1'
		//		  	  ||||||----->	ADPS2:	'1'
		//		  	  |||||------>	ADIE:	'0'	
		//		  	  ||||------->	ADIF:	'0'	
		//		  	  |||-------->	ADATE:	'0'
		//		  	  ||--------->	ADSC:	'0'
		//		  	  |---------->	ADEN:	'0'	
	
		ADMUX = 0b01000000;
		//		  ||||||||--->	MUX0:	'0'	set mux to AN0
		//		  |||||||---->	MUX1:	'0'
		//		  ||||||----->	MUX2:	'0'
		//		  |||||------>	MUX3:	'0'
		//		  ||||------->	MUX4:	'0'
		//		  |||-------->	ADLAR:	'0'
		//		  ||--------->	REFS0:	'1'	use AVCC as vref
		//		  |---------->	REFS1:	'0'
	
	if(xADCRunMode == ADC_RM_IRQ)
	{
		//not yet implemented
	}
	else if(xADCRunMode == ADC_RM_Poll)
	{
		ADCSRA &= ~(1<<ADIE);	
	}
	
	//enable adc
	ADCSRA |= (1<<ADEN);
}


uint16_t ADC_u16SampleChannel(TADC_InputChannels xADCInputChannel, uint16_t u16TimeOutCnt)
{
	uint16_t u16RetVal = 0xFFFF;
	uint16_t u16WaitCnt = 0;
	// set multiplexer to given channel
	ADMUX &= 0xE0;	//delete current setting
	switch(xADCInputChannel)
	{
		case ADC_IN_0:
			// already done
		break;
		case ADC_IN_1:
			ADMUX |= (1<<MUX0);
		break;
		case ADC_IN_2:
			ADMUX |= (1<<MUX1);
		break;
		case ADC_IN_3:
			ADMUX |= (1<<MUX1) | (1<<MUX0);
		break;
	}
	
	//start conversion
	ADCSRA |= (1<<ADSC);
	
	//wait for conversion to stop
	while ((u16WaitCnt < u16TimeOutCnt) & ((ADCSRA & (1<<ADSC)) == (1<<ADSC)))
	{
		u16WaitCnt++;
	}
	
	//read back result if no time out occurred
	if (u16WaitCnt < u16TimeOutCnt)
	{
		u16RetVal = ADCL;
		u16RetVal = u16RetVal + ADCH * 256;
	}
	
	return u16RetVal;
}