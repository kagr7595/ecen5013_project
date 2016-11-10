/***************************************************************************
*
*  	Filename: project_3.c
*	Description: All requirements for Project 3 are run through this file
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/

#ifndef _PROJECT_3_C
#define _PROJECT_3_C

#include "log.h"
#include "error.h"
#include "data.h"
#include "memory.h"
#include "circbuf.h"
#include "timer.h"
#include "profiler.h"
#include "command.h"
#include "LED_control.h"
#include "SPI.h"
#include "nRF24L01.h"

#ifdef FRDM
#include "uart.h"
#include "RGB.h"
#include "dma.h"
#endif

#include "project_3.h"

void project_3_report()
{
#ifdef FRDM
	init_uart();

#ifdef MY_DMA
	dma_init();
    uint8_t dma_array[256] = "0123456789ABCDEF.01234567890ABCDEF.0123456789ABCDEF.0123456789ABCDEF.\0";
	uint8_t * dma_array_ptr1 = dma_array+0;
	uint8_t * dma_array_ptr2 = dma_array+10;
	uint8_t second_array[256] = "Sunshine + Kittens = Happiness\0";
    dma_transfer(second_array,dma_array,count2null(second_array));
    my_newcharacter('\n',1);
    LOG_0(dma_array,count2null(dma_array));
    my_newcharacter('\n',1);
#endif

#ifdef CMD_RX_TEST
    // tests the receiving of a command
    // Through a terminal program, send hex data corresponding to a received packet.
    // EX: 0x01 0x01 0x03 0x00 0x05
    //     color 1-data blue-green checksum=5
    // EX: 0x02 0x01 0x32 0x00 0x35
    //     brightness 1-data 50-duty checksum=36
    RGB_init();
    CI_Msg cmd;
    uint8_t error;
    error = receive_cmd(&cmd);
    if(error) {
    	if(error == UNKNOWN_CMD) {
    		uint8_t print_arr0[50] = "Upon receiving a command: Error = UNKNOWN_CMD\n\0";
    		LOG_0(print_arr0,count2null(print_arr0));
    	}
    	else if(error == INVALID_LENGTH) {
    		uint8_t print_arr0[50] = "Upon receiving a command: Error = INVALID_LENGTH\n\0";
    		LOG_0(print_arr0,count2null(print_arr0));
    	}
    	else if(error == INVALID_DATA) {
    		uint8_t print_arr0[50] = "Upon receiving a command: Error = INVALID_DATA\n\0";
    		LOG_0(print_arr0,count2null(print_arr0));
    	}
    	else if(error == INCORRECT_CHECKSUM) {
    		uint8_t print_arr0[60] = "Upon receiving a command: Error = INCORRECT_CHECKSUM\n\0";
    		LOG_0(print_arr0,count2null(print_arr0));
    	}
    }
    uint8_t print_arr0[50] = "\nReceived a command:\0";
    LOG_0(print_arr0,count2null(print_arr0));
    uint8_t print_arr1[20] = "\n	Command: \0";
    LOG_1(print_arr1, count2null(print_arr1), (uint8_t)(cmd.command), UI8);
    uint8_t print_arr2[20] = "\n	Length: \0";
    LOG_1(print_arr2, count2null(print_arr2), cmd.length, UI8);
    uint8_t i = 0;
    while(i < cmd.length) {
    	 uint8_t print_arr3[50] = "\n	Data: \0";
    	 LOG_1(print_arr3, count2null(print_arr3), (*(cmd.data+i)), UI8);
    	 i++;
    }
    uint8_t print_arr4[20] = "\n	Checksum: \0";
    LOG_1(print_arr4, count2null(print_arr4), (uint16_t)(cmd.checksum), UI16);
    uint8_t print_arr5[2] = "\n\0";
    LOG_0(print_arr0,count2null(print_arr0));
    run_cmd(&cmd);
#endif
#endif

#ifndef FRDM
#ifdef CMD_TX_TEST_ORIG
    // tests the sending of a command
    // Pretending the terminal program is the FRDM board, this mimics the BBB sending the info
    CI_Msg cmd2;
    uint8_t data[1] = {5};
    create_cmd(&cmd2, SET_COLOR, 1, data);
    send_cmd(&cmd2);

    CI_Msg cmd;
    uint8_t error;
    error = receive_cmd(&cmd);
    run_cmd(&cmd);
#endif

#ifdef CM_TX_TEST
    printf("\nAbout to set brightness\n");
    set_brightness(50);
    printf("\nAbout to set color\n");
    set_color(BLUE);
#endif
#endif

#ifdef FRDM
#ifdef SPI_NRF_TESTS
    init_uart();
    SPI_init();

    // tests read
    uint8_t msg0[30] = "Read Register:\n	\0";
    LOG_0(msg0,count2null(msg0));
    uint8_t out_data[RX_ADDR_P1_LENGTH+1];
    nrf_read_reg(RX_ADDR_P1, RX_ADDR_P1_LENGTH+1, out_data);
    LOG_3(out_data,RX_ADDR_P1_LENGTH+1);


    //tests write
    uint8_t msg1[30] = "\n\nWrite Register Test:\n\0";
    LOG_0(msg1,count2null(msg1));
    uint8_t out_data_before[TX_ADDR_LENGTH+1];
    uint8_t in_data[TX_ADDR_LENGTH] = {0x01,0x02,0x03,0x04,0x05};
    uint8_t out_data_after[TX_ADDR_LENGTH+1];

    //read original data
    uint8_t msg2[30] = "	Original Data:		\0";
    LOG_0(msg2,count2null(msg2));
    nrf_read_reg(TX_ADDR, TX_ADDR_LENGTH+1, out_data_before);
    LOG_3(out_data_before,TX_ADDR_LENGTH+1);

    //write new data
    uint8_t msg3[30] = "\n	New Data:		\0";
    LOG_0(msg3,count2null(msg3));
    nrf_write_reg(TX_ADDR, TX_ADDR_LENGTH, in_data);
    LOG_3(in_data,TX_ADDR_LENGTH);

    //check that the register has been updated
    uint8_t msg4[30] = "\n	Check Write Data:	\0";
    LOG_0(msg4,count2null(msg4));
    nrf_read_reg(TX_ADDR, TX_ADDR_LENGTH+1, out_data_after);
    LOG_3(out_data_after,TX_ADDR_LENGTH+1);



    //CONFIG register read
    uint8_t msg5[30] = "\n\nConfig Register Read: \0";
    LOG_0(msg5,count2null(msg5));
    uint8_t config_read = nrf_config_read();
    LOG_3(&config_read,1);

    //CONFIG register write
    uint8_t msg6[30] = "\nConfig Register Write: \0";
    LOG_0(msg6,count2null(msg6));
    uint8_t config_write = 0x0F;
    nrf_config_write(config_write);
    LOG_3(&config_write,1);

    //CONFIG register read
    uint8_t msg7[30] = "\nConfig Register Read: \0";
    LOG_0(msg7,count2null(msg7));
    config_read = nrf_config_read();
    LOG_3(&config_read,1);



    //STATUS register (read) using the NOP command
    uint8_t msg8[30] = "\n\nStatus Register Read: \0";
    LOG_0(msg8,count2null(msg8));
    uint8_t status_read = nrf_status();
    LOG_3(&status_read,1);



    //TX_ADDR read
    uint8_t msg9[50] = "\n\nTransmitter Address Register Read: \0";
    LOG_0(msg9,count2null(msg9));
    uint8_t tx_addr_r[TX_ADDR_LENGTH+1];
    nrf_tx_addr_read(tx_addr_r);
    LOG_3(tx_addr_r,TX_ADDR_LENGTH+1);

    //TX_ADDR write
    uint8_t msg10[50] = "\nTransmitter Address Register Write: \0";
    LOG_0(msg10,count2null(msg10));
    uint8_t tx_addr_w[TX_ADDR_LENGTH] = {0x12,0x34,0x56,0x78,0x9A};
    nrf_tx_addr_write(tx_addr_w);
    LOG_3(tx_addr_w,TX_ADDR_LENGTH);

    //TX_ADDR read
    uint8_t msg11[50] = "\nTransmitter Address Register Read: \0";
    LOG_0(msg11,count2null(msg11));
    nrf_tx_addr_read(tx_addr_r);
    LOG_3(tx_addr_r,TX_ADDR_LENGTH+1);



    //RF_SETUP register read
    uint8_t msg12[30] = "\n\nRF Setup Register Read: ";
    LOG_0(msg12,count2null(msg12));
    uint8_t rf_setup_r = nrf_rf_setup_read();
    LOG_3(&rf_setup_r,1);

    //RF_SETUP register write power
    uint8_t msg13[50] = "\nRF Setup Register Write Power (bits 2:1): ";
    LOG_0(msg13,count2null(msg13));
    nrf_rf_setup_power(RF6);
    uint8_t pwr = RF6;
    LOG_3(&pwr,1);

    //RF_SETUP register read
    uint8_t msg14[30] = "\nRF Setup Register Read: ";
    LOG_0(msg14,count2null(msg14));
    rf_setup_r = nrf_rf_setup_read();
    LOG_3(&rf_setup_r,1);



    //FIFO_STATUS register Read
    uint8_t msg15[30] = "\n\nFIFO Status Register Read: ";
    LOG_0(msg15,count2null(msg15));
    uint8_t fifo_status = nrf_fifo_status();
    LOG_3(&rf_setup_r,1);
#endif
#endif

    while(1);
}
#endif
