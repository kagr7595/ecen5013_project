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

#include "log.h"

// Logging to UART or to terminal with a simple string and length of characters in string
// void LOG_0(<type> * data, <type> len)
void LOG_0(uint8_t * data, uint64_t len)
{
    uint64_t i;
#ifdef FRDM
    //Starting bit, 8bits data, ending bit
    

#else
    for (i = 0; i<len; i++) {
	printf("%c",*(data+i));
    }
#endif
}

//Logging a string with specific lenth of characters and appending a parameter
//void LOG_1(<type> * data, <type> len, <type> * param, <type> data_type_size)
void LOG_1(uint8_t * data, uint64_t len, uint32_t * param,  uint32_t data_type_size)
{
    uint64_t i;
#ifdef FRDM


#else


#endif
}




#endif

