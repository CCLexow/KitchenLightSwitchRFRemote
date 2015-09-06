/*
 * ADC.h
 *
 * Created: 05.01.2014 17:29:25
 *  Author: cc
 */ 


#ifndef ADC_H_
#define ADC_H_
	
	#include <stdint.h>
	
	typedef enum ADC_RunModes
	{
		ADC_RM_IRQ,
		ADC_RM_Poll
	}TADC_RunModes;

	typedef enum ADC_InputChannels
	{
		ADC_IN_0,
		ADC_IN_1,
		ADC_IN_2,
		ADC_IN_3
	}TADC_InputChannels;

	void ADC_init(TADC_RunModes xADCRunMode);

	uint16_t ADC_u16SampleChannel(TADC_InputChannels xADCInputChannel, uint16_t u16TimeOutCnt);

#endif /* ADC_H_ */