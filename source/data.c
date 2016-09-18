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
int32_t my_atoi(uint32_t * str)
{

    return 0;
}

// Convert data types in memory from a big endian representation to 
// little endian
uint32_t big_to_little(uint32_t data)
{
    uint32_t data_out = 0x00000000;
    data_out = ((data & 0x000000FF) << 24);
    data_out |= ((data & 0x0000FF00) << 8);
    data_out |= ((data & 0x00FF0000) >> 8);
    data_out |= ((data & 0xFF000000) >> 24);
    return data_out;
}

// Convert data types in memory from a little endian representation to 
// big endian
uint32_t little_to_big(uint32_t data)
{
    uint32_t data_out = big_to_little(data);
    return data_out;
}

// Takes pointer to memory and length of bytes to print 
// and prints the hex output
void dump_memory(uint8_t * start, uint32_t length)
{
    uint32_t i;
    uint32_t j;
    uint8_t num_divides;
    uint8_t return_code = 0;
    uint8_t current_uint8;
    uint8_t rem_array[POWER_2_64];
    uint8_t hex_array[POWER_2_64];

    for (i = 0; i < length; i++) 
    {
        current_uint8 = *(start+i);
        num_divides = 0;
        while(current_uint8 != 0)
        {
            *(rem_array+num_divides) = current_uint8 % 2;
            current_uint8 = current_uint8 / 2;
            
            num_divides++;
        }
        printf("HEX output: ");
        for (j = 0;j<num_divides; j++)
        {
            printf("%x",*(rem_array+num_divides-j));
        }
                
    }

}
