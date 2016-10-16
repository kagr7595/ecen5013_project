/***************************************************************************
*
*  	Filename: project_2.c
*	Description: All requirements for Project 2 are run through this file
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/

#ifndef _PROJECT_2_C
#define _PROJECT_2_C

#include "log.h"
#include "error.h"
#include "data.h"
#include "memory.h"
#include "circbuf.h"
#include "timer.h"
#include "ftoa_utests.h"
#include "buf_utests.h"
#include "profiler.h"

#ifdef FRDM
#include "uart.h"
#include "RGB.h"
#endif

#include "project_2.h"


void project_2_report()
{
#ifdef FRDM
    init_uart();
#endif

#ifdef FTOATEST
    ftoa_unit_tests();
#endif


#ifdef CIRCBUFTESTS
    buffer_unit_tests();
#endif

#ifdef TEST_LOGGER
    uint8_t  n1 = 200;
    uint16_t n2 = 4096;
    uint32_t n3 = 123456;
    float f0 = 1543.321;
    uint8_t print_arr0[256] = "\nTesting123, Serial Print Test, no params\0";
    LOG_0(print_arr0,count2null(print_arr0));
    uint8_t print_arr1[256] ="\nThis is an integer number: \0";
    LOG_1(print_arr1,count2null(print_arr1),n1,UI8);
    uint8_t print_arr2[256] ="\nThis is an integer number: \0";
    LOG_1(print_arr2,count2null(print_arr2),n2,UI16);
    uint8_t print_arr3[256] ="\nThis is an integer number: \0";
    LOG_1(print_arr3,count2null(print_arr3),n3,UI32);
    uint8_t print_arr4[256] ="\nThis is a floating point number: \0";
    LOG_2(print_arr4,count2null(print_arr4),f0,FL32);
    my_newcharacter('\n',2);  
#endif

    profiler_tests();

#ifdef FRDM
    RGB_init();
    int8_t color = RED;
    uint8_t duty = 100;
    uint8_t msg[1];
    uart_rx_data(msg, 1);
    uart_tx_data(msg, 1);
    while(*msg != 'q') {
        if ((*msg == 'a') && (color > 0)) {
            color--;
        }
        else if ((*msg == 'w') && (duty < 100)) {
        	duty = duty + 10;
        }
        else if ((*msg == 's') && (duty > 0)) {
        	duty = duty - 10;
        }
        else if ((*msg == 'd') && (color < 7)) {
        	color++;
        }
        set_PWM_RGB(duty, color);
    	uart_rx_data(msg, 1);
    }

#endif
}
#endif
