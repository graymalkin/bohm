/****************************************************************/
/*		        SCOPE_ANALYSIS.C			*/
/****************************************************************/

/****************************************************************/
/* Inclusion of header files.				*/
/****************************************************************/

#include		<stdio.h>

#include		"types.h"

/****************************************************************/
/* Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function checks if an identifier has been */
 /* previously declared */

BOOLEAN defined(st)
	STBUCKET	*st;
			      /* pointer to the bucket for the */
			      /* identifier */
{
        return((st->curr_binding) != NULL);
}
