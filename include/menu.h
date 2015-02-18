/****************************************************************/
/*		              	MENU.H                          */
/****************************************************************/

#ifndef MENU_H
#define MENU_H

#include "types.h"

/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

extern int option;
extern unsigned int limit;
extern BOOLEAN seetime;
extern BOOLEAN seenode;
extern BOOLEAN seegarb;

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

void menu(void);
void info(void);

#endif
