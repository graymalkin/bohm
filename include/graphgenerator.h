/****************************************************************/
/*	                GRAPHGENERATOR.H 			*/
/****************************************************************/

#ifndef GRAPHGENERATOR_H
#define GRAPHGENERATOR_H

#include "types.h"

/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/

extern unsigned int max_nodes, num_nodes;
extern BOOLEAN is_global_var;

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

FORM *closeterm(int, TERM *);

TERM *maketerm(FORM *);
TERM *buildvarterm(int, STBUCKET *);
TERM *buildtrueterm(int);
TERM *buildfalseterm(int);
TERM *buildintterm(int, intptr_t);
TERM *buildlambdaterm(int, STBUCKET *, TERM *);
TERM *buildplambdaterm(int, PATTERN *, TERM *);
TERM *build_mu_term(int, STBUCKET *, TERM *);
TERM *buildappterm(int, TERM *, TERM *);
TERM *buildifelseterm(int, TERM *, TERM *, TERM *);
TERM *buildletinterm(int, STBUCKET *, TERM *, TERM *);
TERM *buildandterm(int, TERM *, TERM *);
TERM *buildorterm(int, TERM *, TERM *);
TERM *buildnotterm(int, TERM *);
TERM *buildmatterm(int, TERM *, TERM *, int);
TERM *buildminusterm(int, TERM *);
TERM *buildrelopterm(int, TERM *, TERM *, int);
TERM *buildnillist(int);
TERM *buildlist(int, TERM *, TERM *);
TERM *buildlist1(int, TERM *, TERM *);
TERM *buildcarterm(int, TERM *);
TERM *buildcdrterm(int, TERM *);
TERM *buildtestnil(int, TERM *);
TERM *buildvoidterm(int);

void connect(FORM *, int, FORM *, int);
void connect1(FORM *, int, FORM *, int);
void int_connect(FORM *, int, intptr_t, int);
void bool_connect(FORM *, int, int);

void allocate_form(FORM **, int, int);
void myfree(FORM *);
void free_pattern(PATTERN *);

VARLIST *mergevarlist(VARLIST *, VARLIST *);
VARLIST *makevarlist(STBUCKET *, TERM *);

#endif
