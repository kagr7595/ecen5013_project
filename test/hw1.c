#include "hw1.h"

/*This function takes a pointer to an array of chars and the length of the array.
  It returns a 1 if the pointer is NULL, a 2 if the length is less than or equal 
  to 0, or returns 0 if the array is reversed.*/
char reverse(char * str, int length)
{
	//array pointer is NULL
	if(str == NULL) {return 1;}
	//length is less than or equal to 0
	if(length <= 0) {return 2;}
	//decrement length since array starts at 0
	length--;
	char temp;
	int i;
	//reverses array
	for(i = 0; i <= length/2; i++)
	{
		temp = *(str+i);
		*(str+i) = *(str+(length-i));
		*(str+length-i) = temp;
	}
	return 0;
}

