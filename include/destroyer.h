/****************************************************************/
/*     		         DESTROYER.H				*/
/****************************************************************/

#ifndef DESTROYER_H
#define DESTROYER_H

#include "types.h"

/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

extern FORM *headfree;

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

void init_destroy(void);
void destroy(void);
void no_destroy(void);

#endif