/****************************************************************/
/*	                      GARBAGE.H 			*/
/****************************************************************/

#ifndef GARBAGE_H
#define GARBAGE_H

#include <sys/times.h>
#include "types.h"

/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

extern unsigned long er_count;
extern unsigned long cl_count;
extern FORM *del_head;
extern clock_t usr_garb_time;
extern clock_t sys_garb_time;

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

void init_garbage(void);
void ins_del(FORM *);
void clean(void);
void user(void);

#endif
