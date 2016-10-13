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

void ftoa_unit_tests() {
/* Create unsigned array of 70 bytes */
    uint8_t array[ARRAY_LENGTH_70];
    uint8_t ftoa_string[6] = "FTOA: ";

    float f1 = -7.5;
    float f2 = 1543.321;
    float f3 = 4.0E18;
    float f4 = 3.402823E38;
    float f5 = 1.65432E-2;
    float f6 = .001;
    float f7 = -0.00001;
    float f8 = 1.132654325544517632E18;
    float f9 = .0005;

    return_code = my_ftoa(array,f1);
    return_code_error(return_code, MY_FTOA);
    if(!return_code)
    	LOG_1(ftoa_string, 6, array, count2null(array));

    return_code = my_ftoa(array,f2);
    return_code_error(return_code, MY_FTOA);
    if(!return_code)
    	LOG_1(ftoa_string,6,array,count2null(array));

    return_code = my_ftoa(array,f3);
    return_code_error(return_code, MY_FTOA);
    if(!return_code)
    	LOG_1(ftoa_string,6,array,count2null(array));

    return_code = my_ftoa(array,f4);
    return_code_error(return_code, MY_FTOA);
    if(!return_code)
    	LOG_1(ftoa_string,6,array,count2null(array));

    return_code = my_ftoa(array,f5);
    return_code_error(return_code, MY_FTOA);
    if(!return_code)
    	LOG_1(ftoa_string,6,array,count2null(array));

    return_code = my_ftoa(array,f6);
    return_code_error(return_code, MY_FTOA);
    if(!return_code)
    	LOG_1(ftoa_string,6,array,count2null(array));

    return_code = my_ftoa(array,f7);
    return_code_error(return_code, MY_FTOA);
    if(!return_code)
    	LOG_1(ftoa_string,6,array,count2null(array));

    return_code = my_ftoa(array,f8);
    return_code_error(return_code, MY_FTOA);
    if(!return_code)
    	LOG_1(ftoa_string,6,array,count2null(array));

    return_code = my_ftoa(array,f9);
    return_code_error(return_code, MY_FTOA);
    if(!return_code)
    	LOG_1(ftoa_string,6,array,count2null(array));
}

#endif
