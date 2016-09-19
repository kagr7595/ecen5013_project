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
    int8_t return_code = 0;
    
    
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
    return_code_error(return_code, MY_MEMZERO);
    
    
    /* Use memmove to move 8 bytes from aptr_1 to aptr_3 */
    return_code = my_memmove(aptr_1, aptr_3, 8);
    return_code_error(return_code, MY_MEMMOVE);

    
    /* Use memmove to move 16 bytes from aptr_2 to aptr_1 */
    return_code = my_memmove(aptr_2, aptr_1, 16);
    return_code_error(return_code, MY_MEMMOVE);

    
    /* Use reverse on aptr_1 to reverse the entire 32 bytes */
    return_code = my_reverse(aptr_1, ARRAY_LENGTH);
    return_code_error(return_code, MY_REVERSE);
#ifndef FRDM    
    printf("Modified array=\n");
    for (i = 0; i < ARRAY_LENGTH; i++)
    {
        printf(" array[%02d]: %d\n",i,*(array+i));
        if (((i+1)%4)==0) {printf("\n");}
    }
    
    dump_memory(aptr_1, ARRAY_LENGTH);
#endif
    
    uint32_t endian_convert = 0x89ABCDEF;
    uint32_t convert_big_to_little = big_to_little(endian_convert);
    uint32_t convert_little_to_big = little_to_big(convert_big_to_little);

#ifndef FRDM
    printf("Performing a big_to_little endian:\n");
    printf("Original: %x\n", endian_convert);
    printf("After big_to_little: %x\n\n", convert_big_to_little);

    printf("Converting back with little_to_big endian:\n");
    printf("After little_to_big: %x\n\n", convert_little_to_big);
#endif


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
    int8_t strtest1[4] = "123\0";
    int8_t strtest2[5] = "-123\0";
    int8_t strtest3[3] = "72\0";
    int8_t strtest4[4] = "-72\0";
    int8_t test_atoi1 = my_atoi(strtest1); 
    int8_t test_atoi2 = my_atoi(strtest2);
    int8_t test_atoi3 = my_atoi(strtest3);
    int8_t test_atoi4 = my_atoi(strtest4);

#ifndef FRDM
    printf("Testing atoi:\n");
    printf(" Starting string: 123\n");
    printf(" Integer value: %d\n\n", test_atoi1);
    printf(" Starting string: -123\n");
    printf(" Integer value: %d\n\n", test_atoi2);
    printf(" Starting string: 72\n");
    printf(" Integer value: %d\n\n", test_atoi3);
    printf(" Starting string: -72\n");
    printf(" Integer value: %d\n\n", test_atoi4);
#endif
}


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
    
