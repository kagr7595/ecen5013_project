/***************************************************************************
*
*  	Filename: log.c
*	Description: Logging capability code
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _LOG_C
#define _LOG_C

#include "uart.h"
#include "log.h"

// Logging to UART or to terminal with a simple string and length of characters in string
// void LOG_0(<type> * data, <type> len)
void LOG_0(uint8_t * data, uint8_t len)
{
#ifdef VERBOSE
#ifdef FRDM
	uart_tx_data(data,len);
#else
    uint8_t i;
    for (i = 0; i<len; i++) {
    	printf("%c",*(data+i));
    }
#endif
#endif
}

//Logging a string with specific length of characters and appending a parameter
//void LOG_1(<type> * data, <type> len, <type> * param, <type> data_type_size)
void LOG_1(uint8_t * data, uint8_t len, uint8_t * intfl,  uint8_t intfl_len)
{
	LOG_0(data,len);
	LOG_0(intfl,intfl_len);
	LOG_0("\n ",1);
}




#endif

