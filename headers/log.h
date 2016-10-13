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
#include "error.h"
#include "data.h"

/* Defines and Structures section
 ***************************************************************************/
#define UI8  0
#define UI16 1
#define UI32 2
#define UI64 3
#define I8   4
#define I16  5
#define I32  6
#define I64  7
#define FL32 8

/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/

// Logging with a simple string and length of characters in string
// void LOG_0(<type> * data, <type> len)
void LOG_0(uint8_t * data, uint8_t len);


//Logging a string with specific length of characters and appending a parameter
//void LOG_1(<type> * data, <type> len, <type> * param, <type> data_type_size)
void LOG_1(uint8_t * data, uint8_t len, uint64_t i_data,  uint8_t data_type);


//Logging a string with specific length of characters and appending a parameter
//void LOG_2(<type> * data, <type> len, <type> * param, <type> data_type_size)
void LOG_2(uint8_t * data, uint8_t len, float f_data,  uint8_t data_type);


// Creates a new logger repeatable character (as many as num_character).  
// Will always create at least one even if you put zero
// Up to 256 of the same character (useful for spacing and newlines)
void my_newcharacter(uint8_t character, uint8_t num_character);
#endif
