/***************************************************************************
*
*  	Filename: data.c
*	Description: Basic data manipulation
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#include "data.h"
// Convert data from a standard integer type into an asci string
// Need to handle signed data
int8_t my_itoa(uint8_t * str, int32_t data, int32_t base)
{

    return 0;
}

// Convert data from an ascii represented string into an integer type
// Need to handle signed data
int32_t my_atoi(uint8_t * str)
{

    return 0;
}

// Convert data types in memory from a big endian representation to 
// little endian
uint32_t big_to_little(uint32_t data)
{

    return 0;
}

// Convert data types in memory from a little endian representation to 
// big endian
uint32_t little_to_big(uint32_t data)
{

    return 0;
}

// Takes pointer to memory and length of bytes to print 
// and prints the hex output
void dump_memory(uint8_t * start, uint32_t length)
{
    uint32_t i;

    printf("Dump array:\n");
    for (i = 0; i < length; i++) 
    {
        printf(" array[%d]:0x%x%x\n",i,*(start+i)>>4,(*(start+i)&0x0f));
        if (((i+1)%4)==0) {printf("\n");}
    }
}
