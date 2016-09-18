/***************************************************************************
*
*  	Filename: project_1.c
*	Description: 
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/

#include "project_1.h"

// Create unsigned array of 32 bytes
// Create three pointers to three various points in this array
// Initialize memroy at two of the pointers
// Use memmove to move8 bytes from aptr_1 to aptr_3
// Use memmove to t move 16 bytes from aptr_2 to aptr1
// Use reverse on aptr_1 to reverse the entire 32 bytes
// Use printf to print out the entire 32 byte array 
// printf statements should use the pragma to disable during 
// FRDM board related compilation 
void project_1_report()
{
    uint32_t i;
    uint8_t return_code = 0;
    uint8_t final_return = 0;
    
    
    /* Create unsigned array of 32 bytes */
    uint8_t array[ARRAY_LENGTH];
    
    
    /* Create three pointers to three various points in this array */
    uint8_t * aptr_1, * aptr_2, * aptr_3;
    
    // aptr_1: Initialize pointer address to 1st element of array
    aptr_1 = array+0;
    
    // aptr_2: Initialize pointer address to 9th element of array
    aptr_2 = array+8;
    
    // aptr_3: Initialize pointer address to 17th element of array
    aptr_3 = array+16;
    
    
    /* Initialize memory at two locations */
    // aptr_1: Initialize 16 bytes starting at this aptr_1
    // to the numbers from 31-46
    for (i = 0; i < 16; i++)
    {
        *(aptr_1 + i) = 31 + i;
    }
    
    // aptr_3: Initialize the contents of this pointer to the end of 
    // the array to zeros using memzero function
    return_code = my_memzero(aptr_3, 16);
    if(return_code != 0)
    {
        // print out statement of what error occurred 
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

        // reset return_code to 0 and increment final_return
        return_code = 0;
        final_return++;
    }
    
    
    /* Use memmove to move 8 bytes from aptr_1 to aptr_3 */
    return_code = my_memmove(aptr_1, aptr_3, 8);
    if(return_code != 0)
    {
        // print out statement of what error occurred 
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

        // reset return_code to 0 and increment final_return
        return_code = 0;
        final_return++;
    }
    
    
    /* Use memmove to move 16 bytes from aptr_2 to aptr_1 */
    return_code = my_memmove(aptr_2, aptr_1, 16);
    if(return_code != 0)
    {
        // print out statement of what error occurred 
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

        // reset return_code to 0 and increment final_return
        return_code = 0;
        final_return++;
    }
    
    
    /* Use reverse on aptr_1 to reverse the entire 32 bytes */
    return_code = my_reverse(aptr_1, 32);
    if(return_code != 0)
    {
        // print out statement of what error occurred 
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

        // reset return_code to 0 and increment final_return
        return_code = 0;
        final_return++;
    }
    
    if (final_return != 0)
    {
        // print out statement about how many errors occurred
        printf("%d Errors Occurred\n",final_return);
    }
}
