/****************************************************************/
/*	                 STRINGHANDLER.H			*/
/****************************************************************/

#ifndef STRINGHANDLER_H
#define STRINGHANDLER_H

#include "types.h"

/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

void to_lower_s(char *);
int to_nat_s(char *);
int length_s(char *);
void concat_s(char *, char *, char *);
bool equal_s(char *, char *);

#endif
