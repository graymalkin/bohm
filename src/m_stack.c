/****************************************************************/
/*		              M_STACK.C                         */
/****************************************************************/
/* This module implements the auxiliary stack used during       */
/* the reduction of a term.                                     */
/****************************************************************/

/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include		<stdio.h>
#include		"const.h"
#include		"types.h"
#include		"graphgenerator.h"

/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/

FORM       *stack[STACK_SIZE];
int        next;

FORM *pop()
{ 
   return(stack[--next]);
}

void push(f)
     FORM    *f;
{
     stack[next++] = f;
     if(next>STACK_SIZE){
	printf("Stack Overflow . . .\n");
	getchar();getchar();
     }
}
