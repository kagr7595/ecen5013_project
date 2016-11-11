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
#endif

/* Defines and Structures section
 ***************************************************************************/
#define BUF_LENGTH 100
#define CS_NRF_LOW() (PTC_BASE_PTR->PCOR |= (1<<8))
#define CS_NRF_HIGH() (PTC_BASE_PTR->PSOR |= (1<<8))

/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/
// SPI wrapper for SPI_rx_byte and SPI_tx_byt
uint8_t SPI_tx_rx(uint8_t send, int32_t fd);

// SPI Receive data to be received
uint8_t SPI_rx_byte();

// SPI send data to uart
void SPI_tx_byte(uint8_t send);

// Sets up SPI registers
void SPI_init(void);

#endif
