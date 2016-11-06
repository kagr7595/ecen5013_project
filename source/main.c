/***************************************************************************
*
*  	Filename: main.c
*	Description: Calls project_1_report and project_2_report and is the top level c file
*                    
*       Author: Kathy Grimes 
*               Dylan Way
*       
****************************************************************************/

#ifdef PROJECT_1
#include "project_1.h"
#endif

#ifdef PROJECT_2
#include "project_2.h"
#endif

#ifdef PROJECT_3
#include "project_3.h"
#endif

int main()
{
#ifdef PROJECT_1
  project_1_report();
#endif

#ifdef PROJECT_2
  project_2_report();
#endif

#ifdef PROJECT_3
  project_3_report();
#endif

    return 0;
}
