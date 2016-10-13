/***************************************************************************
*
*  	Filename: ftoa_utests.c
*	Description: Runs the unit tests on the floating to ascii function
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _FTOA_UTESTS_C
#define _FTOA_UTESTS_C

#include <stdint.h>
#include "log.h"
#include "data.h"

#define ARRAY_LENGTH_70 70

void ftoa_unit_tests() {
    uint8_t ftoa_string[8] = "\nFTOA: \0";

    float f1 = -7.5;
    float f2 = 1543.321;
    float f3 = 4.0E18;
    float f4 = 3.402823E38;
    float f5 = 1.65432E-2;
    float f6 = .001;
    float f7 = -0.00001;
    float f8 = 1.132654325544517632E18;
    float f9 = .0005;

    LOG_2(ftoa_string, count2null(ftoa_string), f1, FL32);
    LOG_2(ftoa_string, count2null(ftoa_string), f2, FL32);
    LOG_2(ftoa_string, count2null(ftoa_string), f3, FL32);
    LOG_2(ftoa_string, count2null(ftoa_string), f4, FL32);
    LOG_2(ftoa_string, count2null(ftoa_string), f5, FL32);
    LOG_2(ftoa_string, count2null(ftoa_string), f6, FL32);
    LOG_2(ftoa_string, count2null(ftoa_string), f7, FL32);
    LOG_2(ftoa_string, count2null(ftoa_string), f8, FL32);
    LOG_2(ftoa_string, count2null(ftoa_string), f9, FL32);
    my_newcharacter('\n',2);  
}

#endif
