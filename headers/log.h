/***************************************************************************
*
*  	Filename: log.h
*	Description: Header file for log.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _LOG_H
#define _LOG_H

#include <stdint.h>

/* Defines and Structures section
 ***************************************************************************/


/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/

// Logging with a simple string and length of characters in string
// void LOG_0(<type> * data, <type> len)
void LOG_0(uint8_t * data, uint8_t len);


//Logging a string with specific length of characters and appending a parameter
//void LOG_1(<type> * data, <type> len, <type> * param, <type> data_type_size)
void LOG_1(uint8_t * data, uint8_t len,  uint8_t * intfl,  uint8_t intfl_len);

#endif
