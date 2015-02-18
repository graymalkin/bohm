/****************************************************************/
/*		         DYNALLHANDLER.C			*/
/****************************************************************/
/* This module supplies routines for dynamic allocation.	*/
/* It consists of the following functions:			*/
/* - malloc_da(): it allocates a given amount of bytes; if it	*/
/*		  is unable to allocate, it signals this fact;	*/
/* - strdup_da(): it allocates a given string; if it is unable	*/
/*		  to allocate, it signals this fact.		*/
/****************************************************************/

/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include <string.h>
#include <stdlib.h>

#include "const.h"
#include "types.h"

/****************************************************************/
/* 2. Inclusion of declarations that are being imported.        */
/****************************************************************/

#include "crashhandler.h"

/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/

/****************************************************************/
/* 4. Definitions of variables strictly local to the module.	*/
/****************************************************************/

/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function implements a control interface for the */
 /* library function malloc(). */
void *
malloc_da(size_t size)
{
	void *p;

	if(!(p = malloc(size)))
		signal_crash(NOTENOUGHMEMORY);
	return p;
}

 /* The following function implements a control interface for the */
 /* library function strdup(). */
char *
strdup_da(char *s)
{
	char *p;

	if(!(p = strdup(s)))
		signal_crash(NOTENOUGHMEMORY);
	return p;
}

/****************************************************************/
/* 6. Definitions of functions strictly local to the module.	*/
/****************************************************************/
