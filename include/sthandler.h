/****************************************************************/
/*	                     STHANDLER.H			*/
/****************************************************************/

#ifndef STHANDLER_H
#define STHANDLER_H

#include "types.h"

/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

extern STBUCKET *dictionary[];

extern LOCALENVENTRY *curr_local_env;

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

void init_symbol_table(void);
void search_bucket(STBUCKET **, char *);
void push_local_env(void);
void pop_local_env(void);
void pop_all_local_env(void);
void create_variable_binding(STBUCKET *, FORM *, int);
void create_binding_for_undef_id(STBUCKET *, FORM *);
void allocate_bucket(STBUCKET **, char *);
void move_bucket(STBUCKET *, int);

#endif
