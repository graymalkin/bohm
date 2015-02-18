/****************************************************************/
/*		         ERRORHANDLER.C			        */
/****************************************************************/
/* This module supplies routines for error handling.		*/
/* Upon error detection, the corresponding error message is	*/
/* printed on the screen.                                	*/
/* - signal_error(): it signals lexical, syntax and semantic	*/
/*		     errors;					*/
/* - signal_warning(): it signals warnings.			*/
/****************************************************************/

/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include <stdio.h>

#include "const.h"
#include "types.h"

/****************************************************************/
/* 2. Inclusion of declarations that are being imported.        */
/****************************************************************/

#include "errorhandler.h"
#include "lambda_lexan.h"

/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/

BOOLEAN error_detected; /* flag indicating whether an error has been detected */

/****************************************************************/
/* 4. Definitions of variables strictly local to the module.	*/
/****************************************************************/

#include "errormsgs.i"

/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function signals lexical, syntax and semantic */
 /* errors. */
void
signal_error(int error_msg_num)
{
	error_detected = TRUE;
	fprintf(stderr,
		"line %-5d\t--->\t%s\n",
		lines,
		error_msgs[error_msg_num]);
}

 /* The following function signals warnings. */
void
signal_warning(int warning_msg_num)
{
	fprintf(stderr,
		"line %-5d\t--->\t%s\n",
		lines,
		warning_msgs[warning_msg_num]);
}

/****************************************************************/
/* 6. Definitions of functions strictly local to the module.	*/
/****************************************************************/
