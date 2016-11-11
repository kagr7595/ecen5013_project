/***************************************************************************
*
*  	Filename: spi_bbb.h
*	Description: Header file for spi_bbb.c
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _SPI_BBB_H
#define _SPI_BBB_H

#ifdef BBB
#include <stdint.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <getopt.h>
#include <fcntl.h>
#include <sys/ioctl.h>
#include <linux/types.h>
#include <linux/spi/spidev.h>
#include "log.h"


/* Defines and Structures section
 ***************************************************************************/
#define SPI_PATH "/dev/spidev1.0"

static uint8_t mode = 1;
//Global variable to pass into many functions
int32_t fd;


#define SPEED 100000


/* Function prototype Section
 * Add protoypes for all functions called by this module, with the exception
 * of runtime routines.
 ***************************************************************************/
//transfers the send byte and returns receive byte
uint8_t SPI_tx_rx(uint8_t send);

//SPI initialization for BBB
void SPI_init();

#endif

#endif
