/****************************************************************/
/*	       	     	    LAMBDA_LEXAN.H 			*/
/****************************************************************/

#ifndef LAMBDA_LEXAN_H
#define LAMBDA_LEXAN_H

/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

extern int yyleng, lines;

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

extern int yylex(void);
extern int readInputForLexer(char* buffer,int *numBytesRead,int maxBytesToRead);

#endif
