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

BOOLEAN defined(STBUCKET *st)
{
        return((st->curr_binding) != NULL);
}
