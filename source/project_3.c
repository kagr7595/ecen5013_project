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

#ifdef FRDM
#include "uart.h"
#include "RGB.h"
#include "dma.h"
#endif

#include "project_3.h"

void project_3_report()
{
#ifdef FRDM
#ifdef MY_DMA
	dma_init();
#endif
    init_uart();
#ifdef MY_MEM_TEST_N_PROFILER
    uint8_t dma_array[256] = "00000111112222233333444445555566666777778888899999\0";
	uint8_t * dma_array_ptr1 = dma_array+0;
	uint8_t * dma_array_ptr2 = dma_array+10;
	uint8_t second_array[256] = "AaBbCcDdEeFfGgHhIiJjKkLlMmNnOoPp\0";
	uint8_t trial[256] = "abcdefghijklmnopqrstuvwxyz0123456789\0";
	LOG_0(dma_array,count2null(dma_array));
    my_newcharacter('\n',1);
    //my_memzero(dma_array_ptr2,18);
    //LOG_0(dma_array,count2null(dma_array));
    //my_newcharacter('\n',1);

    my_memmove(dma_array_ptr1,dma_array_ptr2,20);

    LOG_0(dma_array,count2null(dma_array));
    my_newcharacter('\n',1);
    my_memmove(dma_array_ptr2,dma_array_ptr1,20);
    LOG_0(dma_array,count2null(dma_array));
    my_newcharacter('\n',1);
    my_newcharacter('\n',1);

    my_memzero(dma_array_ptr2,18);
    LOG_0(dma_array,count2null(dma_array));
    my_newcharacter('\n',1);

    my_memmove(second_array,dma_array_ptr1 + 3,count2null(second_array));
    my_newcharacter('\n',1);
	LOG_0(dma_array,count2null(dma_array));
    my_newcharacter('\n',1);
    my_memmove(trial+1,trial+9,15);
    LOG_0(trial,count2null(trial));
    my_newcharacter('\n',1);
    my_reverse(trial+2,14);
    LOG_0(trial,count2null(trial));

    profiler_tests();
    my_newcharacter('\n',2);

#endif
    RGB_init();



#ifdef PI
    // tests the receiving of a command
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
#endif

#ifdef PI
    // tests the sending of a command
    CI_Msg cmd2;
    uint8_t data[1] = {5};
    create_cmd(&cmd2, SET_COLOR, 1, data);
    send_cmd(&cmd2);
#endif
    CI_Msg cmd;
    uint8_t error;
    error = receive_cmd(&cmd);
    run_cmd(&cmd);
#else
    printf("\nAbout to set brightness\n");
    set_brightness(50);
    printf("\nAbout to set color\n");
    set_color(BLUE);
#endif
}
#endif
