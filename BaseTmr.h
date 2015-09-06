/*
 * BaseTmr.h
 *
 * Created: 05.01.2014 16:40:20
 *  Author: cc
 */ 


#ifndef BASETMR_H_
#define BASETMR_H_

	#include <stdint.h>

	void BaseTmr_Init(void);

	void BaseTmr_WaitForNextTimeSlot_10ms(void);
	
	// returns the timer ticks in ms
	uint32_t BaseTmr_u32GetTimerTicks(void);

#endif /* BASETMR_H_ */