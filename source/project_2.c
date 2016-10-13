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
    LOG_0("Testing123, Serial Print Test, no params\n",41);
    my_itoa(array,(int32_t)n1,10);
    LOG_1("This is an integer number: ",27,array,count2null(array));
    my_itoa(array,(int32_t)n2,10);
    LOG_1("This is an integer number: ",27,array,count2null(array));
    my_itoa(array,n3,10);
    LOG_1("This is an integer number: ",27,array,count2null(array));
    my_ftoa(array,f0);
    LOG_1("This is a floating point number: ",33,array,count2null(array));
#endif


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
