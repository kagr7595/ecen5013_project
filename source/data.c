/***************************************************************************
*
*  	Filename: data.c
*	Description: Basic data manipulation
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#ifndef _DATA_C
#define _DATA_C

#include "data.h"


// Convert data from a standard float type into an asci string
// Always 3 decimal places are printed out if there is any decimal portion
int8_t my_ftoa(uint8_t * str, float data)
{
    uint64_t fint = 0;
    float ffract = 0;
    uint16_t ffract_int = 0;
    uint16_t num_elements; 
    uint8_t fsign = 0;
    uint8_t base = 10;
    int8_t return_code;
    
    // if pointer is NULL, error
    if(str == NULL) {return 1;}
    
    if(data<0)
    {
	fsign = 1;
	data = data * -1;
    }
    if (data<.0001f)
    {
	fint = 0;
	ffract = 0.000;
	// change sign to 0 as 0.000 is neither negative or positive
	fsign = 0;
    } else if (data>LARGEST_FLOAT_HANDLED)
    {
	if (fsign == 1)
	{
	    // large negative number rounds to zero
	    // TODO: add a return code print statement to the return_error_code function
	    printf("Given data = %0lf",data);
	    printf("\n   ERROR: Negative float is too small to compute for this ftoa function\n\n");
	    return 2;
	} else 
	{
	    // TODO: add a return code print statement to the return_error_code function
	    printf("Given data = %0lf",data);
	    printf("\n   ERROR: Float is too large to compute for this ftoa function\n\n");
	    return 3;
	}
    } else
    {    
	//Changing the full float number into an integer (so we only get integer portion and not the decimal)
	fint = (uint64_t)data;
	//now that we have the integer portion, Subtract the integer portion from the full float data to get the decimal/fraction portion
	ffract = data - (float)fint; 
    }
    
    // add .0005 for rounding.  The .0001 place will be cut off as rounding to 3 decimal places 
    ffract = ffract + .0005;
    
    // Finished getting correct sign, integer, and fraction parts of float number
    // Now to change from a number into an ascii and put into pointer str
    
    ffract_int = ffract*1000;
    
    //***printf("\n   float sign = %0d\n",fsign);
    //***printf("    float int = %0ld\n",fint);
    //***printf("  float fract = %0d\n",ffract_int);
    
    
    /* Switch from numbers to ascii characters */
    if (ffract_int > 0)
    {
        // add fraction portion first, LSB->MSB
        for (num_elements = 0; ffract_int != 0; num_elements++)
        {
            *(str + num_elements) = ffract_int%base + '0';
            ffract_int = ffract_int/base;
        }
        // if the ffract_int is not over 99, it will need an 0.  Same with over 9 (will need two 0s)
        while (num_elements < 3)
	{
            *(str + num_elements) = '0';
            num_elements++;
	}
        
        // add decimal sign
        *(str + num_elements) = '.';
        num_elements++;
    }  
    if (fint > 0)
    {
        // add int portion LSB->MSB
        for (; fint != 0; num_elements++)
        {
            *(str + num_elements) = fint%base + '0';
            fint = fint/base;
        }
    } else
    {	
        *(str + num_elements) = '0';
	num_elements++;
    }
    
    // if data is negative, change the largest bit (sign bit) in str to 1
    if (fsign)
    {
        *(str + num_elements) = '-';  
        num_elements++;
    }
    
    //reverse array of remainders to get ascii string of data without sign
    return_code = my_reverse(str, num_elements);
    if(return_code != 0){return 4;}
    
    *(str + num_elements) = '\0';  
    num_elements++;
    
    return 0;
}




// Convert data from a standard integer type into an asci string
// Need to handle signed data
int8_t my_itoa(uint8_t * str, int32_t data, int32_t base)
{
    uint32_t temp; 
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
	// TODO: add a return code print statement to the return_error_code function
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
    
    return 0;
}

// Convert data from an ascii represented string into an integer type
// Assumes the ascii is a number represented in base 10
// Need to handle signed data
int32_t my_atoi(uint8_t * str)
{    
    uint32_t out_value = 0; 
    uint16_t element_num = 0; 
    uint8_t neg = 0;
    
    //returns 0 if there is no str
    if(str == NULL) {return 0;}
    
    // if data is a negative number
    if(*str == '-')
    {
        neg = 1;
        element_num++;
    }
    
    //switch from numbers to ascii characters
    while (*(str + element_num) != '\0')
    {
        out_value *= 10;
	out_value += (*(str + element_num)) - '0';        
        element_num++;
    }
    
    // if data is negative, convert to two's comp
    if (neg)
    {
        out_value = ~(out_value - 1); 
    }
    
    return out_value;
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

#ifndef FRDM
    uint32_t i;
    if(start == NULL) {printf("ERROR: src pointer is NULL in dump_array\n");}
    else if (length <= 0) {printf("ERROR: length is less than or equal to 0 in dump_array\n");}
    else
    {
        printf("Dump array:\n");
        for (i = 0; i < length; i++) 
        {
            printf(" array[%02d]:0x%x%x\n",i,*(start+i)>>4,(*(start+i)&0x0f));
            if (((i+1)%4)==0) {printf("\n");}
        }
    }
#endif
}


void my_ftoa_out(uint8_t * string, float data)
{    
#ifndef FRDM
    uint8_t i;

    printf("Given data: %f\n ASCII str: ",data);
    for (i = 0; *(string+i)!='\0'; i++)
    {
        printf("%c",*(string+i));
    }                       
    printf("\n\n");
#endif
}


void my_itoa_out(uint8_t * string, int32_t data, int32_t base)
{    
#ifndef FRDM
    uint8_t i;

    printf("Given data: %d, base: %d\nASCII str:",data,base);
    for (i = 0; *(string+i)!='\0'; i++)
    {
        printf("%c",*(string+i));
    }                       
    printf("\n\n");
#endif
}


#endif
