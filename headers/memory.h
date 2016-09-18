/***************************************************************************
*
*  	Filename: memory.h
*	Description: Header file for memory.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _MEMORY_H
#define _MEMORY_H

#include "stdio.h"
#include "stdint.h"

/* Defines section
 * Add all #defines here
 ***************************************************************************/


/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/
// Take two pointers (one source and one destination) and a length of bytes
// to move from one location to the other
// Checks overlapped areas between the two memory blocks
// Returns error if move failed
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length);

// Takes pointer to memory location and a length in bytes, 
// then zeros out all the memroy
// Returns error if the zeroing out failed
int8_t my_memzero(uint8_t * src, uint32_t length);

// Takes pointer to memory location and a length in bytes,
// then reverses order of all bytes
// Returns error if reverse failed
int8_t my_reverse(uint8_t * src, uint32_t length);

#endif
