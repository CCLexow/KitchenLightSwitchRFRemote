/*
 * Dio_Driver.h
 *
 * Created: 05.01.2014 16:36:36
 *  Author: cc
 */ 


#ifndef DIO_DRIVER_H_
#define DIO_DRIVER_H_

typedef enum Dio_Port_Names
{
	Dio_Name0,
	Dio_Name1,
	Dio_Dummy
} TDio_Port_Names;


typedef enum Dio_Port_Level
{
	Dio_Low = 0,
	Dio_High,
	Dio_Unknown
} TDio_Port_Level;

TDio_Port_Level Dio_ReadChannel(TDio_Port_Names ChannelID);
void Dio_WriteChannel(TDio_Port_Names ChannelID, TDio_Port_Level Level);



#endif /* DIO_DRIVER_H_ */