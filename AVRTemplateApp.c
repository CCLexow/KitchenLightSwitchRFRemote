/*
 * nrf24l01p_Test.c
 *
 * Created: 05.01.2014 15:50:40
 *  Author: cc
 */ 
//m168 10 $(TargetName).hex
//m328p 7 $(TargetName).hex

#include <avr/io.h>
#include <util/delay.h>
#include "BaseTmr.h"
#include "Port.h"
#include "Dio_Driver.h"
#include "ADC.h"
#include "UART.h"
#include "nRF24L01.h"
#include "mirf.h"
#include "spi.h"
#include <avr/interrupt.h>


#define DBG_Output_On	0x01
#define DBG_Output_Off	0x00
#define DBG_Output		DBG_Output_On

#define KLS_Master	1
#define KLS_Slave	2

#define KLS_SystemMode KLS_Master

#define KLS_ToggleLight		0xAA
#define KLS_ToggleLightNeg	0x55

void System_Setup(void)
{
	Port_init();
	BaseTmr_Init();
	UART_init();
	//ADC_init(ADC_RM_Poll);

	
	// Initialize AVR for use with mirf
	mirf_init();
	// Wait for mirf to come up
	_delay_ms(50);
	// Activate interrupts
	sei();
	// Configure mirf
	mirf_config();	
}

uint8_t u08VerifyRFModuleConfiguration(void)
{
	uint8_t u08MirfReg;
	mirf_read_register(CONFIG,&u08MirfReg,1);	
	if (u08MirfReg == 75)
	{
		return 0x01;
	}
	else
	{
		return 0x00;
	}
}

#if KLS_SystemMode == KLS_Master
void KLS_MasterMode(void)
{
	uint8_t au08MirfBuffer[mirf_PAYLOAD];
	
	#if DBG_Output == DBG_Output_On
		UART_puts("Sending Light Toggle Message\r\n");
	#endif
	
	// keep power supply up
	
	// prepare tx buffer
	au08MirfBuffer[0] = KLS_ToggleLight;
	au08MirfBuffer[1] = KLS_ToggleLightNeg;
	// transmit data
	mirf_send((uint8_t*)&au08MirfBuffer[0],mirf_PAYLOAD);
	// wait for transmission to end
	while (PIND & (1<<PIND2))
	{
		// wait for interrupt
	}
	mirf_poll_for_irq();
	// shut down power supply

	#if DBG_Output == DBG_Output_On
		UART_puts("Light Toggle Message sent\r\n");
	#endif
	while(1);
}
#endif

#if KLS_SystemMode == KLS_Slave
void KLS_SlaveMode(void)
{
	while(1)
	{
		BaseTmr_WaitForNextTimeSlot_10ms();
	}
}
#endif

int main(void)
{
	volatile union xExtractU32Bytes
	{
		uint32_t u32Value;
		struct u08Help{
			uint8_t u08Byte0;
			uint8_t u08Byte1;
			uint8_t u08Byte2;
			uint8_t u08Byte3;
		}u08Bytes;
	}xExtractU32BytesUnion;
	
	volatile uint8_t u08Toggle;

	System_Setup();

	#if DBG_Output == DBG_Output_On
		UART_puts("Kitchen Light Switch\r\n");
		#if KLS_SystemMode == KLS_Master
			UART_puts("System is running as Master");
		#elif KLS_SystemMode == KLS_Slave
			UART_puts("System is running as Slave");
		#endif
		UART_puts("\r\n");
	#endif
	
	
	if (u08VerifyRFModuleConfiguration())
	{
		UART_puts("Module correctly configured\r\n");
	}
	else
	{
		UART_puts("Module not correctly configured\r\n");	
	}


	while(1)
	{
		#if KLS_SystemMode == KLS_Master
			KLS_MasterMode();		
		#elif KLS_SystemMode == KLS_Slave
			KLS_SlaveMode();		
		#endif
	}
}