/***************************************************************************
*
*  	Filename: error.c
*	Description: Print error codes for each function
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#include <stdint.h>
#include <stdio.h>
#include "log.h"
#include "data.h"
#include "memory.h"

void return_code_error(int8_t return_code, uint8_t function_name)
{
    if(return_code != 0) 
    {
    	uint8_t str[100] = "Error Return Code";
        switch(function_name)
        {
        case 1:
            // print out statement of what error occurred in my_memmove function
            switch(return_code)
            {
            case 1: my_memmove(str,"ERROR: src pointer is NULL in my_memmove\n\0",100);
                break;
            case 2: my_memmove(str,"ERROR: dst pointer is NULL in my_memmove\n\0",100);
                break;
            case 3: my_memmove(str,"ERROR: length is less than or equal to 0 in my_memmove\n\0",100);
                break;
            case 4: my_memmove(str,"ERROR: src and dst pointers did not compare correctly in my_memmove\n\0",100);
                break;
            default: my_memmove(str,"ERROR: Something unexpected occurred in my_memmove\n\0",100);
                break;
            }
            break;
        case 2:
            // print out statement of what error occurred in my_memzero function
            switch(return_code)
            {
            case 1: my_memmove(str,"ERROR: src pointer is NULL in my_memzero\n\0",100);
                break;
            case 2: my_memmove(str,"ERROR: length is less than or equal to 0 in my_memzero\n\0",100);
                break;
            case 3: my_memmove(str,"ERROR: An pointer element did not change to zero in my_memzero\n\0",100);
                break;
            default: my_memmove(str,"ERROR: Something unexpected occurred in my_memzero\n\0",100);
                break;
            }
            break;
        case 3:
            // print out statement of what error occurred in my_reverse function
            switch(return_code)
            {
            case 1: my_memmove(str,"ERROR: src pointer is NULL in my_reverse\n\0",100);
                break;
            case 2: my_memmove(str,"ERROR: length is less than or equal to 0 in my_reverse\n\0",100);
                break;
            case 3: my_memmove(str,"ERROR: my_memmove failed in my_reverse\n\0",100);
                break;
            case 4: my_memmove(str,"ERROR: src and orig_copy_src were not reverse of each other in my_reverse\n\0",100);
                break;
            default: my_memmove(str,"ERROR: Something unexpected occurred in my_reverse\n\0",100);
                break;
            }        
            break;
        case 4:
            // print out statement of what error occurred in my_itoa function
            switch(return_code)
            {
            case 1: my_memmove(str,"ERROR: src pointer is NULL in my_itoa\n\0",100);
                break;
            case 2: my_memmove(str,"ERROR: base is needs to be between 2 and 16 inclusive in my_itoa\n\0",100);
                break;
            case 3: my_memmove(str,"ERROR: error in my_reverse call in my_itoa\n\0",100);
                break;
            default: my_memmove(str,"ERROR: Something unexpected occurred in my_reverse\n\0",100);
                break;
            }   
            break;
        default:
            // Something went wrong if it got in here
            my_memmove(str,"ERROR: Something unexpected occurred in return_code_error function\n\0",100);
            break;
        }

        LOG_0(str,count2null(str));
    }
}
    
