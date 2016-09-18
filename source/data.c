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
    uint32_t temp; 
    uint16_t i; 
    uint16_t num_elements; 
    uint8_t return_code = 0;
    
    
    if(str == NULL) {return 1;}
    else if(base > 16 || base < 2) {return 2;}    

    // if data is a negative number
    if(data < 0)
    {
        temp = ~data+1;
    } else
    {
        temp = data;
    }

    //switch from numbers to ascii characters
    for (num_elements = 0; temp != 0; num_elements++)
    {
        //assign remainder into the str pointer
        if(temp%base < 10)
        {
            *(str + num_elements) = temp%base + '0';
        } else
        {
            *(str + num_elements) = temp%base + ('a'-10);
        }
        temp = temp/base;
    }

    // if data is negative, change the largest bit (sign bit) in str to 1
    if (data < 0)
    {
        *(str+num_elements) = '-';  
        num_elements++;
    }

    //reverse array of remainders to get ascii string of data without sign
    return_code = my_reverse(str, num_elements);
    if(return_code != 0){return 3;}

    *(str+num_elements) = '\0';  
    num_elements++;

    printf("Given data: %d, new base: %d\nASCII str:",data,base);
    for (i = 0; i<num_elements; i++)
    {
        printf("%c",*(str+i));
    }                                  
    printf("\n");
    
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
    if(start == NULL) {printf("ERROR: src pointer is NULL in dump_array\n");}
    else if (length <= 0) {printf("ERROR: length is less than or equal to 0 in dump_array\n");}
    else
    {
        printf("Dump array:\n");
        for (i = 0; i < length; i++) 
        {
            printf(" array[%d]:0x%x%x\n",i,*(start+i)>>4,(*(start+i)&0x0f));
            if (((i+1)%4)==0) {printf("\n");}
        }
    }
}
