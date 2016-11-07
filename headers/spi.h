/***************************************************************************
*
*  	Filename: spi.h
*	Description: Header file for spi.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _SPI_H
#define _SPI_H

#ifdef FRDM
#include "MKL25Z4.h"
#include "core_cm0plus.h"
//#include "startup_MKL25Z4.S"
#endif

//#include "circbuf.h"

/* Defines and Structures section
 ***************************************************************************/
#define BUF_LENGTH 100

/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/

// SPI Receive data to be stored into another pointer for processing
void SPI_rx_data(uint8_t *read, uint8_t length);

// SPI send data to uart
void SPI_tx_data(uint8_t *send, uint8_t length);

// Sets up SPI registers
void SPI_init(void);

#endif
