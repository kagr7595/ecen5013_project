/***************************************************************************
*
*  	Filename: project_1.h
*	Description: Header file for project_1.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _PROJECT_1_H
#define _PROJECT_1_H

#include "stdio.h"
#include "stdint.h"
#include "memory.c"
#include "data.c"

/* Defines section
 * Add all #defines here
 ***************************************************************************/
#define ARRAY_LENGTH 32

/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/
// Create unsigned array of 32 bytes
// Create three pointers to three various points in this array
// Initialize memroy at two of the pointers
// Use memmove to move8 bytes from aptr_1 to aptr_3
// Use memmove to t move 16 bytes from apter_2 to aptr1
// Use reverse on aptr_1 to reverse the entire 32 bytes
// Use printf to print out the entire 32 byte array 
// printf statements should use the pragma to disable during 
// FRDM board related compilation 
void project_1_report();

#endif
