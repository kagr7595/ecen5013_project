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

#include "project_2.h"


void project_2_report()
{
    uint32_t i;
    int8_t return_code = 0;
    
    
    /* Create unsigned array of 70 bytes */
    uint8_t array[ARRAY_LENGTH_70];
    
    float f1 = -7.5;
    float f2 = 1543.321;
    float f3 = -4.0E37;
    float f4 = 4.0E37;
    float f5 = 1.65432E-2;
    float f6 = .001;
    float f7 = -0.00001;
    float f8 = 1.132654325544517632E17;
    float f9 = .0005;

//    my_ftoa1(array,0xC0F00000);
//
//    my_ftoa1(array,f1);
//    my_ftoa1(array,f2);
//    my_ftoa1(array,f3);
//    my_ftoa1(array,f4);
//    my_ftoa1(array,f5);
//    my_ftoa1(array,f6);
//    my_ftoa1(array,f7);
//    my_ftoa1(array,f8);
//    my_ftoa1(array,f9);

    return_code = my_ftoa(array,f1);
    //return_code_error(return_code, MY_FTOA);
    if(!return_code)
      my_ftoa_out(array,f1);

    return_code = my_ftoa(array,f2); 
    //return_code_error(return_code, MY_FTOA);
    if(!return_code)
      my_ftoa_out(array,f2);

    return_code = my_ftoa(array,f3); 
    //return_code_error(return_code, MY_FTOA);
    if(!return_code)
      my_ftoa_out(array,f3);

    return_code = my_ftoa(array,f4); 
    //return_code_error(return_code, MY_FTOA);
    if(!return_code)
      my_ftoa_out(array,f4);

    return_code = my_ftoa(array,f5); 
    //return_code_error(return_code, MY_FTOA);
    if(!return_code)
      my_ftoa_out(array,f5);

    return_code = my_ftoa(array,f6); 
    //return_code_error(return_code, MY_FTOA);
    if(!return_code)
      my_ftoa_out(array,f6);

    return_code = my_ftoa(array,f7); 
    //return_code_error(return_code, MY_FTOA);
    if(!return_code)
      my_ftoa_out(array,f7);

    return_code = my_ftoa(array,f8); 
    //return_code_error(return_code, MY_FTOA);
    if(!return_code)
      my_ftoa_out(array,f8);

    return_code = my_ftoa(array,f9); 
    //return_code_error(return_code, MY_FTOA);
    if(!return_code)
      my_ftoa_out(array,f9);

}

#endif 
