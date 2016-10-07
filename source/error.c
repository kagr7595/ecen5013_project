/***************************************************************************
*
*  	Filename: error.c
*	Description: Print error codes for each function
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/

#include "error.h"

void return_code_error(int8_t return_code, uint8_t function_name)
{
    
#ifndef FRDM
    if(return_code != 0) 
    {
        switch(function_name)
        {
        case 1:
            // print out statement of what error occurred in my_memmove function
            switch(return_code)
            {
            case 1: printf("ERROR: src pointer is NULL in my_memmove\n");
                break;
            case 2: printf("ERROR: dst pointer is NULL in my_memmove\n");
                break;
            case 3: printf("ERROR: length is less than or equal to 0 in my_memmove\n");
                break;
            case 4: printf("ERROR: src and dst pointers did not compare correctly in my_memmove\n");
                break;
            default: printf("ERROR: Something unexpected occurred in my_memmove\n");
                break;
            }
            break;
        case 2:
            // print out statement of what error occurred in my_memzero function
            switch(return_code)
            {
            case 1: printf("ERROR: src pointer is NULL in my_memzero\n");
                break;
            case 2: printf("ERROR: length is less than or equal to 0 in my_memzero\n");
                break;
            case 3: printf("ERROR: An pointer element did not change to zero in my_memzero\n");
                break;
            default: printf("ERROR: Something unexpected occurred in my_memzero\n");
                break;
            }
            break;
        case 3:
            // print out statement of what error occurred in my_reverse function
            switch(return_code)
            {
            case 1: printf("ERROR: src pointer is NULL in my_reverse\n");
                break;
            case 2: printf("ERROR: length is less than or equal to 0 in my_reverse\n");
                break;
            case 3: printf("ERROR: my_memmove failed in my_reverse\n");
                break;
            case 4: printf("ERROR: src and orig_copy_src were not reverse of each other in my_reverse\n");
                break;
            default: printf("ERROR: Something unexpected occurred in my_reverse\n");
                break;
            }        
            break;
        case 4:
            // print out statement of what error occurred in my_itoa function
            switch(return_code)
            {
            case 1: printf("ERROR: src pointer is NULL in my_itoa\n");
                break;
            case 2: printf("ERROR: base is needs to be between 2 and 16 inclusive in my_itoa\n");
                break;
            case 3: printf("ERROR: error in my_reverse call in my_itoa\n");
                break;
            default: printf("ERROR: Something unexpected occurred in my_reverse\n");
                break;
            }   
            break;
        default:
            // Something went wrong if it got in here
            printf("ERROR: Something unexpected occurred in return_code_error function\n");
            break;
        }
    }
#endif
}
    
