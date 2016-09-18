/***************************************************************************
*
*  	Filename: data.h
*	Description: Header file for data.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _DATA_H
#define _DATA_H

#include "stdio.h"
#include "stdint.h"

/* Defines section
 * Add all #defines here
 ***************************************************************************/

/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/
// Convert data from a standard integer type into an asci string
// Need to handle signed data
int8_t my_itoa(uint8_t * str, int32_t data, int32_t base);

// Convert data from an ascii represented string into an integer type
// Need to handle signed data
int32_t my_atoi(uint32_t * str);

// Convert data types in memory from a big endian representation to 
// little endian
uint32_t big_to_little(uint32_t data);

// Convert data types in memory from a little endian representation to 
// big endian
uint32_t little_to_big(uint32_t data);

// Takes pointer to memory and length of bytes to print 
// and prints the hex output
void dump_memory(uint8_t * start, uint32_t length);

#endif
