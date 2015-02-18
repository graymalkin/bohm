/****************************************************************/
/*		     	  LAMBDA_PARSER.H 			*/
/****************************************************************/

#ifndef LAMBDA_PARSER_H
#define LAMBDA_PARSER_H

#include "types.h"

/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

extern int yyparse(void);

extern int error_detected;
extern int quit;
extern int loading_mode;

extern FORM *lastinputterm;

#endif
