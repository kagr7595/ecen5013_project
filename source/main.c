/***************************************************************************
*
*  	Filename: main.c
*	Description: 
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/
#include "project_1.c"
#ifdef FRDM
#pragma GCC poison printf
#endif

int main()
{
    project_1_report();

    return 0;
}
