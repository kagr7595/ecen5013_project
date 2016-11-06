/***************************************************************************
*
*  	Filename: dma.h
*	Description: Header file for dma.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _DMA_H
#define _DMA_H

#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "log.h"
#ifdef FRDM
#include "MKL25Z4.h"
#include "core_cm0plus.h"

/* Defines section
 * Add all #defines here
 ***************************************************************************/
#define DMAMUX_ENABLE 1
#define DMAMUX_DISABLE 0
#define DMA_INIT 1

/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/
// Basic DMA setup for clocks, addresses, etc.
void dma_init();

// enable/disable DMAMUX CFG
void dmamux_en(uint8_t enable);

// DMA writes and reads
uint8_t dma_transfer(uint8_t * src, uint8_t * dst, uint32_t byte_length);

// Run DMA in byte mode
uint8_t dma_byte(uint8_t * src, uint8_t * dst, uint32_t byte_length);

// Run DMA in word mode
uint8_t dma_word(uint8_t * src, uint8_t * dst, uint32_t word_length);

// Set byte_length transfer
void dma_set_bcr_length(uint32_t byte_length);

// Clears errors and sets done bit. 
void dma_clear_status(uint8_t in_init);

// Handles DMA0 interrupt request at end of data transfer
void DMA0_IRQHandler();

#endif

#endif


