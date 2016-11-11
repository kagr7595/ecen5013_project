/***************************************************************************
*
*  	Filename: spi_bbb.c
*	Description: SPI Application Layer code for BBB
*                    This file is heavily based off of:
*                     * spidev_test.c
*                     * SPI testing utility (using spidev driver)
*                     *
* 		      * Copyright (c) 2007  MontaVista Software, Inc.
* 		      * Copyright (c) 2007  Anton Vorontsov <avorontsov@ru.mvista.com>
* 		      *
* 		      * This program is free software; you can redistribute it and/or modify
* 		      * it under the terms of the GNU General Public License as published by
* 		      * the Free Software Foundation; either version 2 of the License.
*                     *
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _SPI_BBB_C
#define _SPI_BBB_C

#ifdef BBB

#include "spi_bbb.h"


uint8_t SPI_tx_rx(uint8_t send)
{
    int ret = 0;;
    uint8_t log_notsend [256] = "can't send spi message";
    
    uint8_t receive [1] = "K";
    struct spi_ioc_transfer tr;
    tr.tx_buf = send;
    tr.rx_buf = receive;
    tr.len = 1;
    tr.delay_usecs = 0;
    tr.speed_hz = SPEED;
    tr.bits_per_word = 8;
    
    ret = ioctl(fd, SPI_IOC_MESSAGE(1), &tr);
    //if (ret < 1)
    // LOG_0(log_notsend,count2null(log_notsend));
	
	//LOG_1("",0,receive,UI8);
	
    return receive[1];
}


void SPI_init() {


    static const char *device = SPI_PATH;
    static uint8_t bits = 8;
    static uint32_t speed = SPEED;
    static uint16_t delay = 0;
    int32_t ret = 0;

    uint8_t log_notopen [256] = "can't open device\0";
    uint8_t log_notsetspi [256] = "can't set spi mode\0";
    uint8_t log_notgetspi [256] = "can't get spi mode\0";
    uint8_t log_notsetbpw [256] = "can't set bits per word\0";
    uint8_t log_notgetbpw [256] = "can't get bits per word\0";
    uint8_t log_notsetmspeed [256] = "can't set max speed hz\0";
    uint8_t log_notgetmspeed [256] = "can't get max speed hz\0";
    
    //OPEN DEVICE
    fd = open(device, O_RDWR);
    if (fd < 0) {
	LOG_0(log_notopen,count2null(log_notopen));
    }

    //SETTING CFG
    /*
     * spi mode
     */
    ret = ioctl(fd, SPI_IOC_WR_MODE, &mode);
    if (ret == -1) {
	LOG_0(log_notsetspi,count2null(log_notsetspi));	
    }
    
    ret = ioctl(fd, SPI_IOC_RD_MODE, &mode);
    if (ret == -1) {
	LOG_0(log_notgetspi,count2null(log_notgetspi));	
    }
    
    /*
     * bits per word
     */
    ret = ioctl(fd, SPI_IOC_WR_BITS_PER_WORD, &bits);
    if (ret == -1) {
	LOG_0(log_notsetbpw,count2null(log_notsetbpw));	
    }
    
    ret = ioctl(fd, SPI_IOC_RD_BITS_PER_WORD, &bits);
    if (ret == -1) {
	LOG_0(log_notgetbpw,count2null(log_notgetbpw));
    }
    
    /*
     * max speed hz
     */
    ret = ioctl(fd, SPI_IOC_WR_MAX_SPEED_HZ, &speed);
    if (ret == -1) {
	LOG_0(log_notsetmspeed,count2null(log_notsetmspeed));
    }
    
    ret = ioctl(fd, SPI_IOC_RD_MAX_SPEED_HZ, &speed);
    if (ret == -1) {
	LOG_0(log_notgetmspeed,count2null(log_notgetmspeed));	
    }
}
#endif

#endif
