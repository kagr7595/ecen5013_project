/***************************************************************************
*
*  	Filename: uart.h
*	Description: Header file for uart.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _UART_H
#define _UART_H

#include "frdm.h"
// #include "core_cm0plus.h" DO I NEED YOU?  FOUND YOU ONLINE>>>>LOTS OF DEFS

/* Defines and Structures section
 ***************************************************************************/


/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/

// UART Receive data to be stored into another pointer for processing
void uart_rx_data(.....);


// UART send data to uart
void uart_tx_data(.....);

// Initialize clock
// Example: Baud rate of 115200 means 115200 bits are sent persecond
// RS232 format requires 10 bits to send each byte,
// (1starting, 8 data, 1 ending, *1parity*) (parity is optional 11th bit)
// so at 115200 baud you can send 11520 bytes per second
void clock_init(......);

// There should be a defined function for this one?
void uart_irq(......);

#endif
