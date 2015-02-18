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

extern void yyerror(const char *);
extern int yyparse(void);
extern void yyrestart(FILE *);

extern int error_detected;
extern int quit;
extern int loading_mode;

extern FORM *lastinputterm;

extern FILE *yyin;

#endif
