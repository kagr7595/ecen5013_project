/***************************************************************************
*
*  	Filename: memory.c
*	Description: Basic memory movement options
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _MEMORY_C
#define _MEMORY_C

#include <stdint.h>
#include <stdio.h>
#include "memory.h"
#ifdef FRDM
#include "dma.h"
#endif

// Take two pointers (one source and one destination) and a length of bytes
// to move from one location to the other
// Checks overlapped areas between the two memory blocks
// Returns error if move failed
int8_t my_memmove(uint8_t * src, uint8_t * dst, uint32_t length)
{
    uint32_t i;
    //uint8_t orig_copy_src[length];
    
    // if src pointer is NULL
    if (src == NULL) {return 1;}
    // if dst pointer is NULL
    else if (dst == NULL) {return 2;}
    // if length is less than or equal to 0
    else if (length <= 0 ) {return 3;}
    // if the memory locations for both both arrays aren't distinct, return 5
    else if (src == dst) {return 0;}//do nothing as the data is the same and not worth it to waste clock cycles
    //else if (((src+length-1 >= dst) && (src+length-1 <= dst+length-1)) || ((dst+length-1 >= src) && (dst+length-1 <= src+length-1))) {return 5;}
    else if ((src < dst) && (src + length-1 > dst)) //src addresses overlap with dst (where src occurs first before dst)
	{
#ifdef MY_DMA
    	dma_transfer(src+(dst-src),dst+(dst-src),length-(uint32_t)(dst-src));
    	dma_transfer(src,dst,(uint32_t)(dst-src));
#else
    	//if there are transfers that can do 32 bits at once, do them first
    	for(i = 0; i< length/4; i++)
    	{
    		*(dst +(length-1)- 0 - i*4) = *(src +(length-1) - 0 - i*4);
    		*(dst +(length-1)- 1 - i*4) = *(src +(length-1) - 1 - i*4);
    		*(dst +(length-1)- 2 - i*4) = *(src +(length-1) - 2 - i*4);
    		*(dst +(length-1)- 3 - i*4) = *(src +(length-1) - 3 - i*4);
    	}
    	src = src-i*4;
    	dst = dst-i*4;
    	for (i = 0; i < length%4; i++)
    	{
    		*(dst +(length-1)- i) = *(src +(length-1) - i);
    	}
    	// move bytes from src array to dst array
		//for (i = 0; i < length; i++)
		//{
		//	*(dst+(length-1)-i) = *(src+(length-1)-i);
		//}
#endif
	}
    // if no condition matches take pointer and length and reverse byte order
    else 
    {
#ifdef MY_DMA
    	dma_transfer(src,dst,length);
#else
    	//if there are transfers that can do 32 bits at once, do them first
    	for(i = 0; i< length/4; i++)
    	{
    		*(dst + 0 + i*4) = *(src + 0 + i*4);
    		*(dst + 1 + i*4) = *(src + 1 + i*4);
    		*(dst + 2 + i*4) = *(src + 2 + i*4);
    		*(dst + 3 + i*4) = *(src + 3 + i*4);
    	}
    	src = src+i*4;
    	dst = dst+i*4;
    	for (i = 0; i < length%4; i++)
    	{
    		*(dst + i) = *(src + i);
    	}
    	// move bytes from src array to dst array
        //for (i = 0; i < length; i++)
        //{
        //    *(dst+i) = *(src + i);
        //}
#endif
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
#ifdef MY_DMA
    	uint8_t zero [4] = "0000";
    	uint32_t num_transfers = 0;
    	if(length%4) { num_transfers = length/4 + 1; }
    	else { num_transfers = length/4; }

    	for (i = 0; i< num_transfers; i++)
    	{
    		if(length >= 4) {
    			dma_transfer(zero,src+i*4,4);
    			length = length - 4;
    		} else
    			dma_transfer(zero,src+i*4,length);
    	}
#else
    	//if there are transfers that can do 32 bits at once, do them first
    	for(i = 0; i< length/4; i++)
    	{
    		*(src + 0 + i*4) = '0';
    		*(src + 1 + i*4) = '0';
    		*(src + 2 + i*4) = '0';
    		*(src + 3 + i*4) = '0';
    	}
    	src = src+i*4;
        for (i = 0; i < length%4; i++)
        {
            *(src + i) = '0';
        }
#endif
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
        for (i = 0; i < length/2; i++)
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

#endif
