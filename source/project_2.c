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

    /* Create unsigned array of 32 bytes */
    uint8_t array[32];
    
    // Try small data value itoa conversions
    int32_t int_convert = 643;
    int8_t convert_itoa1 = my_itoa(array,int_convert,2);
    my_itoa_out(array,int_convert,2);
    return_code_error(convert_itoa1, MY_ITOA);

    int8_t convert_itoa2 = my_itoa(array,int_convert,16);
    my_itoa_out(array,int_convert,16);
    return_code_error(convert_itoa2, MY_ITOA);

    // Try large data value itoa conversions
    int_convert = 3315643;
    int8_t convert_itoa3 = my_itoa(array,int_convert,10);
    my_itoa_out(array,int_convert,10);
    return_code_error(convert_itoa3, MY_ITOA);

    int8_t convert_itoa4 = my_itoa(array,int_convert,13);
    my_itoa_out(array,int_convert,13);
    return_code_error(convert_itoa4, MY_ITOA);

    // Try negative itoa conversions
    int_convert = -43;
    int8_t convert_itoa5 = my_itoa(array,int_convert,6);
    my_itoa_out(array,int_convert,6);
    return_code_error(convert_itoa5, MY_ITOA);

    int8_t convert_itoa6 = my_itoa(array,int_convert,8);
    my_itoa_out(array,int_convert,8);
    return_code_error(convert_itoa6, MY_ITOA);



    // Tests a few values in atoi
    uint8_t strtest1[4] = "123\0";
    uint8_t strtest2[5] = "-123\0";
    uint8_t strtest3[6] = "10536\0";
    uint8_t strtest4[7] = "-10536\0";
    int32_t test_atoi1 = my_atoi(strtest1); 
    int32_t test_atoi2 = my_atoi(strtest2);
    int32_t test_atoi3 = my_atoi(strtest3);
    int32_t test_atoi4 = my_atoi(strtest4);
    
    uint8_t print_atoi1[255] = "ATOI: Starting string:    123 Integer value: ";
    uint8_t print_atoi2[255] = "ATOI: Starting string:   -123 Integer value: ";
    uint8_t print_atoi3[255] = "ATOI: Starting string:  10536 Integer value: ";
    uint8_t print_atoi4[255] = "ATOI: Starting string: -10536 Integer value: ";
    my_newcharacter('\n',1);  
    LOG_1(print_atoi1, count2null(print_atoi1), test_atoi1, I32);
    my_newcharacter('\n',1);  
    LOG_1(print_atoi2, count2null(print_atoi2), test_atoi2, I32);
    my_newcharacter('\n',1);  
    LOG_1(print_atoi3, count2null(print_atoi3), test_atoi3, I32);
    my_newcharacter('\n',1);  
    LOG_1(print_atoi4, count2null(print_atoi4), test_atoi4, I32);
    my_newcharacter('\n',1);  

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
