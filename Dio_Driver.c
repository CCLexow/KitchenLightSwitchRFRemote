/*
 * Dio_Driver.c
 *
 * Created: 05.01.2014 16:37:27
 *  Author: cc
 */ 

#include "Dio_Driver.h"
#include <avr/io.h>

/*-------------------------------------------------------------------------------------------------------------------------------------
	Inputs         
  -------------------------------------------------------------------------------------------------------------------------------------*/
//no inputs defined
/*-------------------------------------------------------------------------------------------------------------------------------------*/

/*-------------------------------------------------------------------------------------------------------------------------------------
	Outputs
  -------------------------------------------------------------------------------------------------------------------------------------*/
#define PIN_Name0_High		PORTD |=  (1<<PD6)
#define PIN_Name0_Low		PORTD &= ~(1<<PD6)
#define PIN_Name1_High		PORTD |=  (1<<PD7)
#define PIN_Name1_Low		PORTD &= ~(1<<PD7)

/**
 * Returns the value of the specified DIO channel.
 */
TDio_Port_Level Dio_ReadChannel(TDio_Port_Names ChannelID)
{
	TDio_Port_Level result = Dio_Unknown;

	switch (ChannelID) {
		default:
			/*
			 * Error: ChannelID is not an input
			 */
			result = Dio_Unknown;
			break;
	}
	return result;
}

/**
 * Service to set a level of a channel.
 */
void Dio_WriteChannel(TDio_Port_Names ChannelID, TDio_Port_Level Level)
{
	if (Level == Dio_Unknown) {
		/*
		 * Error: Unknown value
		 */
	} 
	else {
		switch (ChannelID) {
			case Dio_Name0:
			if (Level == Dio_High) {
				PIN_Name0_High;
			} else {
				PIN_Name0_Low;
			}
			break;
			case Dio_Name1:
			if (Level == Dio_High) {
				PIN_Name1_High;
			} else {
				PIN_Name1_Low;
			}
			break;
			default:
				/*
				 * Error: ChannelID is input
				 */
				break;
		}
	}
}