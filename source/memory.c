/***************************************************************************
*
*  	Filename: memory.c
*	Description: Basic memor movement options
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#include "memory.h"
// Take two pointers (one source and one destination) and a length of bytes
// to move from one location to the other
// Checks overlapped areas between the two memory blocks
// Returns error if move failed
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length)
{
    uint32_t i;
    uint8_t orig_copy_src[length];
    
    // if src pointer is NULL
    if (src == NULL) {return 1;}
    // if dst pointer is NULL
    else if (dst == NULL) {return 2;}
    // if length is less than or equal to 0
    else if (length <= 0 ) {return 3;}
    // if no condition matches take pointer and length and reverse byte order
    else 
    {
        // make a copy of the original src before modification
        // use this copy to compare the move function to the original data
        for (i = 0; i < length; i++)
        {
            *(orig_copy_src+i) = *(src+i);
        }
        
        // move bytes from src array to dst array
        for (i = 0; i < length; i++)
        {
            *(dst+i) = *(src + i);
        }
        
        // compare orig_copy_src (highest to lowest byte) to 
        // reversed src (lowest to highest byte)
        // output error if different
        for (i = 0; i < length; i++)
        {
            if (*(orig_copy_src+i) != *(dst+i)) {return 4;}
        }
    }
    
    return 0;
}


// Takes pointer to memory location and a length in bytes, 
// then zeros out all the memroy
// Returns error if the zeroing out failed
int8_t my_memzero(uint8_t * src, uint32_t length)
{
    uint32_t i;
    
    // if arraay pointer is NULL
    if (src == NULL) {return 1;}
    // if length is less than or equal to 0
    else if (length <= 0 ) {return 2;}
    // if no condition matches take pointer and length and reverse byte order
    else 
    {
        for (i = 0; i < length; i++) 
        {
            *(src + i) = 0;
            if (*(src + i) != 0) {return 3;}            
        }
    }
    return 0;
}


// Takes pointer to memory location and a length in bytes,
// then reverse order of all bytes
// Returns error if reverse failed
int8_t my_reverse(uint8_t * src, uint32_t length)
{
    uint32_t i;
    uint8_t temp;
    uint8_t return_code = 0;
    
    // if arraay pointer is NULL
    if (src == NULL) {return 1;}
    // if length is less than or equal to 0
    else if (length <= 0 ) {return 2;}
    // if no condition matches take pointer and length and reverse byte order
    else 
    {
        uint8_t orig_copy_src[length];
        // make a copy of the original src before modification
        // use this copy to compare the reverse function to the original data
        return_code = my_memmove(src, orig_copy_src, length);
        if (return_code != 0 ) {return 3;} 
        
        // reverse all the bytes in the src pointer
        for (i = 0; i <= length/2; i++)
        {
            temp = *(src+i);
            *(src+i) = *(src+(length-1-i));
            *(src+length-1-i) = temp;
        }
        
        // compare orig_copy_src (highest to lowest byte) to 
        // reversed src (lowest to highest byte)
        // output error if different
        for (i = 0; i < length; i++)
        {
            if (*(orig_copy_src+(length-1-i)) != *(src+i)) {return 4;}
        }
    }
    return 0;
}

