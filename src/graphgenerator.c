/****************************************************************/
/*		         GRAPHGENERATOR.C                       */
/****************************************************************/
/* This module contains routines for generating the graph       */
/* representation of lambda-terms.                              */
/* The translation which has been implemented is the one        */
/* described in "linear Logic, Comonads, and Optimal            */
/* Reductions", by A.Asperti, to appear in Fundamenta           */
/* Informaticae.                                                */
/* During the translation, each term is described by a record   */
/* with following fields:                                       */
/*  - rootf : the root form of the term;                        */
/*  - rootp : the root (positive) port of the root form;        */
/*  - vars:   a pointer to the list of free variables for the   */
/*            term.                                             */
/* Free variable of a same term are collected into a linked     */
/* list. Each entry for a free variable consists of:            */
/*  - a pointer to the next variable;                           */
/*  - a pointer to the last form associated to the variable.    */
/*  - a pointer to the symbol table bucket associated with the  */
/*    the variable.                                             */
/* The support of the implementation is an interaction net.     */
/* Each connection between forms of the interaction net has     */
/* been implemented by a double pointer. This is probably       */
/* a bit redundant and inefficient, but it greatly simplified   */
/* debugging, as it allows an easy inspection of the resulting  */
/* graph (see also the directive "inspect" of the language).    */
/* The following functions are external                         */
/*  - buildvarterm():  it builds the graph corresponding to a   */
/*                     a variable. If the variable has been     */
/*                     globally defined by a let instruction,   */
/*                     the corresponding graph is a (shared)    */
/*                     instance of the corresponding term.      */
/*  - buildlambdaterm(): it builds the graph corresponding to a */
/*                       a lambda abstraction.                  */
/*  - buildappterm(): it builds the graph corresponding to an   */
/*                    application                               */
/*  - buildletinterm(): it builds the graph corresponding to a  */
/*                      let_in instruction (it is equivalent to */
/*                      a partially evaluated lambda redex)     */
/*  - closeterm(): it adds a root node to a term 		*/
/*  - connect(): it connects two graphical forms at two         */
/*               specified ports.                               */
/*  - connect1():  it connects the port portf1 of form1 to the 	*/
/* 		   port portf2 of form2 and vice versa if the 	*/
/*		   form2 is not a NIL, INT, True or False form.	*/
/*  - int_connect(): it connects only the port portf1 of form1	*/
/*		    to the port portf2 of form2, becouse form2  */
/*		    is a INT.					*/
/*  - bool_connect(): it connects only the port portf1 of form1	*/
/* 		      to the port portf2 of form2, becouse 	*/
/*		      form2 is a NIL, True or False.		*/
/*  - myfree():  it is used to handle a free list containig     */
/*               all forms removed from the graph.              */
/*		 These forms will be used for future            */
/*		 allocations.                                   */
/*  - allocate_form(): it allocates a new graphical form.       */
/* The functions buildvarterm(), buildlambdaterm(),             */
/* buildappterm() and buildletinterm() etc. are called by the   */
/* parser.                                                      */
/* The functions connect() and allocate_form() are also used    */
/* during reduction.                                            */
/* The following functions are local to the module:             */
/*  - allocate_var(): it allocates a new entry for a variable.  */
/*  - allocate_term(): it allocates a new entry for a term.     */
/*  - buildglobaldefvarterm(): it shares the term corresponding */
/*                             to the globally defined variable */
/*                             (by adding a FAN on top of the   */
/*                             term). One branch of this fan is */
/*                             returned as result; the other    */
/*                             branch is the new root of the    */
/*                             globally declared variable       */
/*  - makebox(): it builds a box around a term.                 */
/*  - addbrackets(): it adds a sequence of brackets of          */
/*                   specified index along a sequence of        */
/*                   variables.                                 */
/*  - share(): it shares the free variables of two terms, by    */
/*             adding suitable FANS.                            */
/*  - lookfor(): it searches for a variable inside a list.      */
/*  - remv(): it removes a variable from a list.                */
/****************************************************************/

/****************************************************************/
/* 1. Inclusion of header files.				*/
/****************************************************************/

#include <inttypes.h>
#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "copy.h"
#include "destroyer.h"
#include "dynallhandler.h"
#include "graphgenerator.h"
#include "menu.h"
#include "types.h"

/****************************************************************/
/* 2. Inclusion of declarations that are being imported.        */
/****************************************************************/

/****************************************************************/
/* 3. Definitions of variables to be exported.			*/
/****************************************************************/

unsigned int num_nodes, max_nodes;
BOOLEAN is_global_var;
FORM *headfree = NULL; /* pointer to the head of the free-form list */

/****************************************************************/
/* 4. Declaration of functions strictly local to the module.	*/
/****************************************************************/

static void allocate_var(VARENTRY **, STBUCKET *, FORM *, VARENTRY *);
static void allocate_term(TERM **, FORM *, int, VARENTRY *);

static TERM *makebox(int, TERM *);

static VARENTRY *addbrackets(int, VARENTRY *);
static VARENTRY *share(int, VARENTRY *, VARENTRY *);
static VARENTRY *lookfor(STBUCKET *, VARENTRY *);
static VARENTRY *remv(STBUCKET *, VARENTRY *);
static VARENTRY *remvp(VARLIST *, VARENTRY *);

static void closeglobalvars(VARENTRY *);
static void intelligent_connect(FORM *, int, FORM *);
static void inspect_connect(FORM *, int, FORM *, int);

static BOOLEAN membervarlist(BINDINGID *, VARLIST *);

/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

 /* The following function creates the graph representation of */
 /* a variable */
TERM *
buildvarterm(int level, STBUCKET *id)
{
	TERM *t;          /* pointer to the term to be created */
	FORM *newf;       /* pointer to the new form to be created */
	VARENTRY *newvar; /* pointer to the new free variable entry */

	allocate_form(&newf,TRIANGLE,level);
	newf->nlevel[1] = -1;
	allocate_var(&newvar,id,newf,NULL);
	allocate_term(&t,newf,1,newvar);
	return(t);
}

 /* The following function creates the graph representation of */
 /* a true constant */
TERM *
buildtrueterm(int level)
{
	TERM *t;     /* pointer to the term to be created */

	allocate_term(&t,NULL,T,NULL);
	return(t);
}

 /* The following function creates the graph representation of */
 /* a false constant */
TERM *
buildfalseterm(int level)
{
	TERM *t;     /* pointer to the term to be created */

	allocate_term(&t,NULL,F,NULL);
	return(t);
}

 /* The following function creates the graph representation of */
 /* a numerical constant */
TERM *
buildintterm(int level, intptr_t value)
{
	TERM *t;     /* pointer to the term to be created */

	allocate_term(&t,(FORM *)value,INT,NULL);
	return(t);
}


 /* The following function creates the graph representation of a */
 /* lambda-abstraction */
TERM *
buildlambdaterm(int level, STBUCKET *id, TERM *body)
{
	TERM 	*t;         /* pointer to the new term to be created */
	FORM    *newf1;     /* pointers to the new forms to be created */
	VARENTRY *boundvar; /* pointer to the entry for the bound variable */
	FORM    *varform;   /* pointer to the bound variable form */


	boundvar = lookfor(id,body->vars);
	if (boundvar != NULL) {
	  allocate_form(&newf1,LAMBDA,level);
	  varform = boundvar->var;
	  if ((varform->name == TRIANGLE) && (varform->nlevel[1] == 0)) {
	    connect(varform->nform[1],
		    varform->nport[1],
		    newf1,2);
	    myfree(varform);
	  }
	  else
	    connect(varform,0,newf1,2);
	  connect(newf1,1,body->rootf,body->rootp);
	  allocate_term(&t,newf1,0,remv(id,body->vars));
	}
	else {
	  allocate_form(&newf1,LAMBDAUNB,level);
	  allocate_term(&t,newf1,0,body->vars);
	  connect1(newf1,1,body->rootf,body->rootp);
	}
	free(body);
	return(t);
}

TERM *
buildplambdaterm(int level, PATTERN *pattern, TERM *body)
{
	TERM 	*t;         /* pointer to the new term to be created */
        VARLIST *vp;
	FORM    *newf1, *newf2;     /* pointers to the new forms to be created */
	VARENTRY *boundvar; /* pointer to the entry for the bound variable */
	FORM    *varform;   /* pointer to the bound variable form */
        BOOLEAN boundp;

        for(vp=pattern->var_list,boundp=FALSE;vp;vp=vp->next)
          if(lookfor(vp->id->id,body->vars)) {
            boundp=TRUE;
            break;
          }

	if (boundp) {
	  allocate_form(&newf1,LAMBDA,level);
          connect(pattern->term->rootf,0,newf1,2);
          for(vp=pattern->var_list;vp;vp=vp->next) {
            if((boundvar=lookfor(vp->id->id,body->vars))==0) {
              allocate_form(&newf2,ERASE,level);
              connect(newf2,0,vp->id->form->nform[0],vp->id->form->nport[0]);
            } else {
              if((varform=boundvar->var)==NULL) {
                fprintf(stderr,"You lose\n");
                exit(1974);
              }
              if ((varform->name == TRIANGLE) && (varform->nlevel[1] == 0)) {
                connect(varform->nform[1],
                        varform->nport[1],
                        vp->id->form->nform[0],
                        vp->id->form->nport[0]);
                myfree(varform);
              } else {
                connect(varform,0,		    
                        vp->id->form->nform[0],
                        vp->id->form->nport[0]);
              }
            }
            myfree(vp->id->form);
          } /* for */
          allocate_term(&t,newf1,0,remvp(pattern->var_list,body->vars));
          connect(newf1,1,body->rootf,body->rootp);
	} else {
          /* apparent memory leak, but there's the destroyer */
	  allocate_form(&newf1,LAMBDAUNB,level);
	  allocate_term(&t,newf1,0,body->vars);
	  connect1(newf1,1,body->rootf,body->rootp);
	}
	free(body);
	return(t);
}

 /* The following function creates the graph representation of a */
 /* recursive definition. */
TERM *
build_mu_term(int level, STBUCKET *id, TERM *body)
{
	TERM            *t,
		   /* pointer to the new term to be created */
			*temp;
	FORM            *newf1;
		   /* pointers to the new forms to be created */
	VARENTRY        *boundvar;
		   /* pointer to the entry for the bound variable */
	FORM            *varform;
		   /* pointer to the bound variable form */

	boundvar = lookfor(id,body->vars);
	if (boundvar != NULL)
	   {
	      allocate_form(&newf1,FAN,level);
	      newf1->nlevel[1] = -1;
	      newf1->nlevel[2] = 1;
	      varform = boundvar->var;

	      if ((varform->name == TRIANGLE) &&
		  (varform->nlevel[1] == 0))
		{
		  connect(varform->nform[1],
			  varform->nport[1],
			  newf1,2);
		  myfree(varform);
		}
	      else intelligent_connect(newf1,2,varform);
	      allocate_term(&temp,newf1,1,remv(id,body->vars));
	      t = makebox(level,temp);
	      connect(newf1,0,body->rootf,body->rootp);

	   }
	else
	  {
	      allocate_form(&newf1,TRIANGLE,level);
	      newf1->nlevel[1] = -1;
	      connect1(newf1,0,body->rootf,body->rootp);
	      allocate_term(&temp,newf1,1,body->vars);
	      t = makebox(level,temp);
	  }
	free(body);
	return(t);
}

 /* The following function creates the graph representation of */
 /* an application */
TERM *
buildappterm(int level, TERM *fun, TERM *arg)
{
	TERM            *t,
		    /* pointer to the term to be created */
			*temp;
		    /* pointer to the temporary term obtained by */
		    /* building a box around the argument */
	VARENTRY        *newvars;
		    /* free variables of the application */
	FORM            *newf;
		    /* pointer to the new form to be created */

	temp = makebox(level,arg);

	allocate_form(&newf,APP,level);

	connect1(newf,0,fun->rootf,fun->rootp);
	connect1(newf,2,temp->rootf,temp->rootp);
	newvars = share(level,fun->vars,temp->vars);

	allocate_term(&t,newf,1,newvars);
	free(arg);
	free(fun);
	return(t);
}

 /* The following function creates the graph representation of */
 /* an if_then_else term */
TERM *
buildifelseterm(int level, TERM *arg1, TERM *arg2, TERM *arg3)
{
	TERM            *t;
		    /* pointer to the term to be created */
	VARENTRY        *newvars,*tempvars;
		    /* free variables of the application */
	FORM            *newf,
			*newf1;
		    /* pointers to the new forms */


	allocate_form(&newf,IFELSE,level);
	allocate_form(&newf1,CONS,level);

	connect1(newf,0,arg1->rootf,arg1->rootp);
	connect(newf,2,newf1,0);
	connect1(newf1,1,arg2->rootf,arg2->rootp);
	connect1(newf1,2,arg3->rootf,arg3->rootp);

	tempvars = share(level,arg2->vars,arg3->vars);
	newvars = share(level,tempvars,arg1->vars);

	allocate_term(&t,newf,1,newvars);
	free(arg1);
	free(arg2);
	free(arg3);
	return(t);
}

 /* The following function creates the graph representation of */
 /* a let_in expression*/
TERM *
buildletinterm(int level, STBUCKET *id, TERM *arg1, TERM *arg2)
{
	TERM            *temp;

	temp = buildlambdaterm(level,id,arg2);
	return(buildappterm(level,temp,arg1));
}

 /* The following function creates the graph representation of */
 /* a boolean and-expression */
TERM *
buildandterm(int level, TERM *arg1, TERM *arg2)
{
	TERM            *t;
		    /* pointer to the term to be created */
	VARENTRY        *newvars;
		    /* free variables of the application */
	FORM            *newf;
		    /* pointer to the new form to be created */


	allocate_form(&newf,AND,level);

	connect1(newf,0,arg1->rootf,arg1->rootp);
	connect1(newf,2,arg2->rootf,arg2->rootp);

	newvars = share(level,arg1->vars,arg2->vars);

	allocate_term(&t,newf,1,newvars);
	free(arg1);
	free(arg2);
	return(t);
}

 /* The following function creates the graph representation of */
 /* a boolean or-expression */
TERM *
buildorterm(int level, TERM *arg1, TERM *arg2)
{
	TERM            *t;
		    /* pointer to the term to be created */
	VARENTRY        *newvars;
		    /* free variables of the application */
	FORM            *newf;
		    /* pointer to the new form to be created */


	allocate_form(&newf,OR,level);

	connect1(newf,0,arg1->rootf,arg1->rootp);
	connect1(newf,2,arg2->rootf,arg2->rootp);

	newvars = share(level,arg1->vars,arg2->vars);

	allocate_term(&t,newf,1,newvars);
	free(arg1);
	free(arg2);
	return(t);
}

 /* The following function creates the graph representation of */
 /* a boolean not-expression */
TERM *
buildnotterm(int level, TERM *arg)
{
	TERM            *t;
		    /* pointer to the term to be created */

	FORM            *newf;
		    /* pointer to the new form to be created */

	allocate_form(&newf,NOT,level);

	connect1(newf,0,arg->rootf,arg->rootp);

	allocate_term(&t,newf,1,arg->vars);
	free(arg);
	return(t);
}

 /* The following function creates the graph representation of */
 /* a mat-expression */
TERM *
buildmatterm(int level, TERM *arg1, TERM *arg2, int op)
{
	TERM            *t;
		    /* pointer to the term to be created */
	VARENTRY        *newvars;
		    /* free variables of the application */
	FORM            *newf;
		    /* pointer to the new form to be created */


	allocate_form(&newf,op,level);
	if (arg1->rootp==INT) {
	  newf->num_safe=(intptr_t)arg1->rootf;
	  switch(newf->name) {
		case ADD: 
		  newf->name=ADD1;
		  break;
		case SUB:
		  newf->name=SUB1;
		  break;
		case PROD: 
		  newf->name=PROD1;
		  break;
		case DIV: 
		  newf->name=DIV1;
		  break;
		case MOD: 
		  newf->name=MOD1;
		  break;
	  } 
	  connect1(newf,0,arg2->rootf,arg2->rootp);
	  allocate_term(&t,newf,1,arg2->vars);
        }
	else {
	  if (arg2->rootp==INT && op!=DIV && op!=MOD) {
	    newf->num_safe=(intptr_t)arg2->rootf; 
	    switch(newf->name) {
		case ADD: 
		  newf->name=ADD1;
		  break;
		case SUB:
		  newf->name=ADD1;
	          newf->num_safe=-(intptr_t)arg2->rootf; 
		  break;
		case PROD: 
		  newf->name=PROD1;
		  break;
	    } 
	    connect1(newf,0,arg1->rootf,arg1->rootp);
	    allocate_term(&t,newf,1,arg1->vars);
          }
	  else {
	    connect1(newf,0,arg1->rootf,arg1->rootp);
	    connect1(newf,2,arg2->rootf,arg2->rootp);
	    newvars = share(level,arg1->vars,arg2->vars);
	    allocate_term(&t,newf,1,newvars);
	  }
	}
	free(arg1);
	free(arg2);
	return(t);
}

 /* The following function creates the graph representation of */
 /* a unary minus-expression */
TERM *
buildminusterm(int level, TERM *arg1)
{
	TERM            *t;
		    /* pointer to the term to be created */
	FORM            *newf;
		    /* pointer to the new form to be created */


	if (arg1->rootp==INT) {
	  arg1->rootf=(FORM *)(-((intptr_t)arg1->rootf));
	  t=arg1;
	} 
	else {
	  allocate_form(&newf,SUB1,level);
	  newf->num_safe=0;
	  connect1(newf,0,arg1->rootf,arg1->rootp);
	  allocate_term(&t,newf,1,arg1->vars);
	  free(arg1);
        }
	return(t);
}

 /* The following function creates the graph representation of */
 /* a relop-expression */
TERM *
buildrelopterm(int level, TERM *arg1, TERM *arg2, int relop)
{
	TERM            *t;
		    /* pointer to the term to be created */
	VARENTRY        *newvars;
		    /* free variables of the application */
	FORM            *newf;
		    /* pointer to the new form to be created */


	allocate_form(&newf,relop,level);
	if (arg1->rootp==INT) {
	  newf->num_safe=(intptr_t)arg1->rootf; 
	  switch(newf->name) {
		case LESS: 
		  newf->name=LESS1;
		  break;
		case EQ: 
		  newf->name=EQ1;
		  break;
		case MORE: 
		  newf->name=MORE1;
		  break;
		case LEQ: 
		  newf->name=LEQ1;
		  break;
		case MEQ: 
		  newf->name=MEQ1;
		  break;
		case NOTEQ: 
		  newf->name=NOTEQ1;
		  break;
	  } 
	  connect1(newf,0,arg2->rootf,arg2->rootp);
	  allocate_term(&t,newf,1,arg2->vars);
        }
	else {
	  if (arg2->rootp==INT) {
	    newf->num_safe=(intptr_t)arg2->rootf; 
	    switch(newf->name) {
		case LESS: 
		  newf->name=MORE1;
		  break;
		case EQ: 
		  newf->name=EQ1;
		  break;
		case MORE: 
		  newf->name=LESS1;
		  break;
		case LEQ: 
		  newf->name=MEQ1;
		  break;
		case MEQ: 
		  newf->name=LEQ1;
		  break;
		case NOTEQ: 
		  newf->name=NOTEQ1;
		  break;
	    } 
	    connect1(newf,0,arg1->rootf,arg1->rootp);
	    allocate_term(&t,newf,1,arg1->vars);
          }
	  else {
	    connect1(newf,0,arg1->rootf,arg1->rootp);
	    connect1(newf,2,arg2->rootf,arg2->rootp);
	    newvars = share(level,arg1->vars,arg2->vars);
	    allocate_term(&t,newf,1,newvars);
	  }
	}
	free(arg1);
	free(arg2);
	return(t);
}

TERM *
buildnillist(int level)
{
	TERM *t;
		     /* pointer to the term to be created */

	allocate_term(&t,NULL,NIL,NULL);
	return(t);
}

TERM *
buildlist(int level, TERM *arg1, TERM *arg2)
{
	TERM            *t;
		    /* pointer to the term to be created */
	FORM            *newf1;
		    /* pointer to the new form to be created */
	VARENTRY	*newvars;

	if(arg2 != NULL){

		allocate_form(&newf1,CONS,level);

		connect1(newf1,1,arg1->rootf,arg1->rootp);
		connect1(newf1,2,arg2->rootf,arg2->rootp);

		newvars = share(level,arg1->vars,arg2->vars);

		allocate_term(&t,newf1,0,newvars);
	}else{
		allocate_form(&newf1,CONS,level);

		connect1(newf1,1,arg1->rootf,arg1->rootp);
		bool_connect(newf1,2,NIL);

		allocate_term(&t,newf1,0,arg1->vars);
	}

	free(arg1);
	free(arg2);
	return(t);
}

TERM *
buildlist1(int level, TERM *arg1, TERM *arg2)
{
	TERM            *t;
		    /* pointer to the term to be created */
	FORM            *newf1;
		    /* pointer to the new form to be created */
	VARENTRY	*newvars;

	if(arg2 != NULL){

		allocate_form(&newf1,CONS1,level);

		connect1(newf1,1,arg1->rootf,arg1->rootp);
		connect1(newf1,2,arg2->rootf,arg2->rootp);

		newvars = share(level,arg1->vars,arg2->vars);

		allocate_term(&t,newf1,0,newvars);
	}else{
		allocate_form(&newf1,CONS1,level);

		connect1(newf1,1,arg1->rootf,arg1->rootp);
		bool_connect(newf1,2,NIL);

		allocate_term(&t,newf1,0,arg1->vars);
	}

	free(arg1);
	free(arg2);
	return(t);
}

TERM *
buildcarterm(int level, TERM *arg)
{
	TERM            *t;
		    /* pointer to the term to be created */

	FORM            *newf;
		    /* pointer to the new form to be created */

	allocate_form(&newf,CAR,level);

	connect1(newf,0,arg->rootf,arg->rootp);

	allocate_term(&t,newf,1,arg->vars);
	free(arg);
	return(t);
}

TERM *
buildcdrterm(int level, TERM *arg)
{
	TERM            *t;
		    /* pointer to the term to be created */

	FORM            *newf;
		    /* pointer to the new form to be created */

	allocate_form(&newf,CDR,level);

	connect1(newf,0,arg->rootf,arg->rootp);

	allocate_term(&t,newf,1,arg->vars);
	free(arg);
	return(t);
}

TERM *
buildtestnil(int level, TERM *arg)
{
	TERM            *t;
		    /* pointer to the term to be created */

	FORM            *newf;
		    /* pointer to the new form to be created */

	allocate_form(&newf,TESTNIL,level);

	connect1(newf,0,arg->rootf,arg->rootp);

	allocate_term(&t,newf,1,arg->vars);
	free(arg);
	return(t);
}

 /* the following function adds a root node to a term */
FORM *
closeterm(int level, TERM *t)
{
       FORM       *newroot;
       if(t!=NULL){
	   if(level==1)
		is_global_var=TRUE;
	   else
		is_global_var=FALSE;

	   allocate_form(&newroot,ROOT,0);

	   connect1(newroot,0,t->rootf,t->rootp);

	   if (level == 1)
	       t->vars = addbrackets(0,t->vars);
	   closeglobalvars(t->vars);
	   return newroot;
	}
	return 0;
}

 /* the following function allocate a new graphical form */
 /* and initialize the name and index fields */
void
allocate_form(FORM **form, int name, int index)
{
	FORM	*dep;
	int	i;

	if(headfree->next == NULL) {
	       headfree->next = dep = malloc_da(sizeof(FORM)*FORM_NUM);
	       dep->next=dep+1;
	       dep->prev=headfree;
	       dep=dep->next;
	       for(i=2;i<FORM_NUM;i++) {
		 dep->next=dep+1;
		 dep->prev=dep-1;
		 dep=dep->next;
	       }
	       dep->next=NULL;
	       dep->prev=dep-1;
	}
	(*form) = headfree;
	headfree=headfree->next;
	num_nodes++;
	if(num_nodes>max_nodes)
		max_nodes=num_nodes;
	(*form)->name = name;
	(*form)->index = index;
	(*form)->nform[0]=NULL;
	(*form)->nform[1]=NULL;
	(*form)->nform[2]=NULL;
	(*form)->num_safe=TRUE;   /* initially, all operators are safe */
}

/* the following function adds a graphical form to deallocate */
/* in a list of free forms (i.e a free-list of forms)         */
void
myfree(FORM *form)
{
	form->prev->next=form->next;
	form->next->prev=form->prev;
	num_nodes--;
	form->next=headfree->next;
	form->prev=headfree;
	if (headfree->next!=NULL)
	  headfree->next->prev=form;
	headfree->next=form;
}


 /* the following function connects together the port portf1 of */
 /* form1 to the port portf2 of form2 */
void
connect(FORM *form1, int portf1, FORM *form2, int portf2)
{
       form1->nport[portf1] = portf2;
       form1->nform[portf1] = form2;
       form2->nport[portf2] = portf1;
       form2->nform[portf2] = form1;
}

 /* the following function connects the port portf1 of form1 to	*/
 /* the port portf2 of form2 and vice versa if the form2 is not */
 /* a NIL, INT, True or False form.				*/
void
connect1(FORM *form1, int portf1, FORM *form2, int portf2)
{
       form1->nport[portf1] = portf2;
       form1->nform[portf1] = form2;
       if (portf2>=0) {
	 form2->nport[portf2] = portf1;
	 form2->nform[portf2] = form1;
       }
}

 /* the following function connects only the port portf1 of 	*/
 /* form1 to the port portf2 of form2, because form2 is a INT	*/
void
int_connect(FORM *form1, int portf1, intptr_t form2, int portf2)
{
       form1->nport[portf1] = portf2;
       form1->nform[portf1] = (FORM *)form2;
}

 /* the following function connects only the port portf1 of 	*/
 /* form1 to the port portf2 of form2, becouse form2 is a INT,	*/
 /* NIL, True or False.						*/
void
bool_connect(form1,portf1,portf2)
       FORM       *form1;
       int        portf1;
       int        portf2;
{
       form1->nport[portf1] = portf2;
}


/****************************************************************/
/* 6. Definitions of functions strictly local to the module.	*/
/****************************************************************/

 /* the following function allocate a new variable entry */
void
allocate_var(VARENTRY **newvar, STBUCKET *id, FORM *form, VARENTRY *nextvar)
{
       *newvar = malloc_da(sizeof(VARENTRY));
       (*newvar)->name = id;
       (*newvar)->var = form;
       (*newvar)->next = nextvar;
}


 /* the following function allocate a new term entry */
void
allocate_term(TERM **term, FORM *rootform, int rootport, VARENTRY *freevars)
{
       *term = malloc_da(sizeof(TERM));
       (*term)->rootf = rootform;
       (*term)->rootp = rootport;
       (*term)->vars = freevars;
}

 /* the following function build a box around a term  */
TERM *
makebox(int level, TERM *arg)
{
	arg->vars = addbrackets(level,arg->vars);
	return(arg);
}

 /* the following function add a sequence of square brackets of */
 /* given index at the free variables in listvar */
VARENTRY *
addbrackets(int index, VARENTRY *listvar)
{
       if (listvar == NULL) return(NULL);
       else
       {
	    VARENTRY      *res;
		       /* resulting variable entry list  */
	    FORM          *variab;
	    FORM          *bracket;
		       /* new form to be created */

	    variab = listvar->var;
	    if (variab->name!=CONS1) {
	      switch(variab->name){
		case TRIANGLE:
		  variab->index = index;
		  variab->nlevel[1] = variab->nlevel[1]+1;
		  break;
		case CDR1:
		case CAR1:
		case TESTNIL1:
		case FAN:
		  variab->index--;
		  variab->nlevel[1] = variab->nlevel[1]+1;
		  variab->nlevel[2] = variab->nlevel[2]+1;
		  break;
		};
		listvar->next=addbrackets(index,listvar->next);
		return(listvar);
	      }
	    else {

	      allocate_form(&bracket,TRIANGLE,index);
	      bracket->nlevel[1] = 1;
	      connect(bracket,1,variab,0);
	      allocate_var(&res,
			   listvar->name,
			   bracket,
			   addbrackets(index,listvar->next));
	      return(res);
	    }
       }
}

 /* The following function shares the free variables of	*/
 /* two terms, by adding suitable FANS.  		*/
VARENTRY *
share(int index, VARENTRY *l1, VARENTRY *l2)
{
       if (l1 == NULL) return l2;
       else
       {
	      VARENTRY      *res;
	      FORM          *fan;
	      VARENTRY      *var;

	      var = lookfor(l1->name,l2);
	      if (var == NULL)
		 {
		     res = l1;
		     res->next = share(index,l1->next,l2);
		     return res;
		 }
	      else
		 {
		     allocate_form(&fan,FAN,index);
		     fan->nlevel[1] = 0;
		     fan->nlevel[2] = 0;

		     intelligent_connect(fan,1,l1->var);
		     intelligent_connect(fan,2,var->var);

		     res = l1;
		     res->name = l1->name;
		     res->var = fan;
		     res->next = share(index,l1->next,remv(l1->name,l2));
		     return res;
		 }
       }
}


 /* The following function searches for a variable inside a list. */
VARENTRY *
lookfor(STBUCKET *id, VARENTRY *listvar)
{
      if (listvar == NULL)
	  return NULL;
      else if (listvar->name == id)
	  return listvar;
      else return (lookfor(id,listvar->next));
}


 /* the following function remove an identifier form a list */
 /* of variables */
VARENTRY *
remv(STBUCKET *id, VARENTRY *listvar)
{
      VARENTRY *temp;
      if (listvar == NULL)
	  return NULL;
      else if (id == listvar->name) {
	  temp=listvar->next;
	  free(listvar);
	  return(temp);
      }
      else
	  {
	     listvar->next = remv(id,listvar->next);
	     return listvar;
	  }
}

/* the following functions does the set substraction of two variable lists */
/* it runs in quadratic time, but who cares? */
VARENTRY *
remvp(VARLIST *vl, VARENTRY *listvar)
{
  VARLIST *v;
  for(v=vl;v;v=v->next)
    listvar=remv(v->id->id,listvar);
  return listvar;
}


 /* The following function copys all the graph of the global */
 /* definition.	*/
void
closeglobalvars(VARENTRY *listvar)
{
      FORM           *formvar,
		     *formterm,
		     *newf;
      if (listvar != NULL)
	  {
	     formvar = listvar->var;
	     formterm = ((listvar->name)->curr_binding)->root;
	     if (formvar->name == TRIANGLE)
	       {
		 newf = copy(formterm->nform[0],
			     formterm->nport[0],
			     formvar->nlevel[1]);
		 connect1(formvar->nform[1], formvar->nport[1],
			 newf, formterm->nport[0]);
	       }
	     else
	       {
		 newf = copy(formterm->nform[0],formterm->nport[0],0);
		 connect1(formvar,0,
                          newf,formterm->nport[0]);
	       }
	     closeglobalvars(listvar->next);
	  }
}

/* The following function tries to merge two forms into a single one. */
/* If failing doing so, connects them normally        		      */
void
intelligent_connect(FORM *f1, int port, FORM *f2)
{
  int dep;
  FORM *new;

  switch (f1->name) {
    case FAN:
      switch (f2->name) {
	case TRIANGLE:
	  f1->nlevel[port] += f2->nlevel[1];
	  inspect_connect(f1,port,f2->nform[1],f2->nport[1]);
	  myfree(f2);
	  break;
	case TESTNIL:
	  f1->name = TESTNIL1;
	  f1->index = f2->index - f1->nlevel[port];
	  if (port == 2) {
	    dep=f1->nlevel[1];
	    f1->nlevel[1]=f1->nlevel[2];
	    f1->nlevel[2]=dep;
	    inspect_connect(f1,2,f1->nform[1],f1->nport[1]);
	  }
	  inspect_connect(f1,1,f2->nform[1],f2->nport[1]);
	  myfree(f2);
	  break;
	case CAR:
	  f1->name = CAR1;
	  f1->index = f2->index - f1->nlevel[port];
	  if (port == 2) {
	    dep=f1->nlevel[1];
	    f1->nlevel[1]=f1->nlevel[2];
	    f1->nlevel[2]=dep;
	    inspect_connect(f1,2,f1->nform[1],f1->nport[1]);
	  }
	  inspect_connect(f1,1,f2->nform[1],f2->nport[1]);
	  myfree(f2);
	  break;
	case CDR:
	  f1->name = CDR1;
	  f1->index = f2->index - f1->nlevel[port];
	  if (port == 2) {
	    dep=f1->nlevel[1];
	    f1->nlevel[1]=f1->nlevel[2];
	    f1->nlevel[2]=dep;
	    inspect_connect(f1,2,f1->nform[1],f1->nport[1]);
	  }
	  inspect_connect(f1,1,f2->nform[1],f2->nport[1]);
	  myfree(f2);
	  break;
	default:
	  connect(f1,port,f2,0);
	  break;
      }
      break;
    case TESTNIL1:
      switch (f2->name) {
	case TRIANGLE:
	  f1->nlevel[port] += f2->nlevel[1];
	  inspect_connect(f1,port,f2->nform[1],f2->nport[1]);
	  myfree(f2);
	  break;
	default:
	  connect(f1,port,f2,0);
	  break;
      }
      break;
    case CAR1:
      switch (f2->name) {
	case TRIANGLE:
	  f1->nlevel[port] += f2->nlevel[1];
	  inspect_connect(f1,port,f2->nform[1],f2->nport[1]);
	  myfree(f2);
	  break;
	case CDR:
	  if (port==2) {
	    f1->name=CONS1;
	    if (f1->nlevel[1]!=0) {
	      allocate_form(&new,TRIANGLE,f1->index-1);
	      new->nlevel[1]=f1->nlevel[1];
	      connect1(new,1,f1->nform[1],f1->nport[1]);
	      connect(f1,1,new,0);
	    }
	    if (f1->nlevel[2]!=0) {
	      f2->name=TRIANGLE;
	      f2->nlevel[1]=f1->nlevel[2];
	      f2->index=f1->index-1;
	      connect(f1,2,f2,0);
	    }
	    else {
	      connect1(f1,2,f2->nform[1],f2->nport[1]);
	      myfree(f2);
	    }
	  }
	  else
	    connect(f1,port,f2,0);
	  break;
	case TESTNIL:
	  if (port==2) {
	    f1->name=TESTNIL1;
	    f2->name=CAR;
	    dep=f2->index;
	    f2->index=f1->index+f1->nlevel[1];
	    f1->index=dep-f1->nlevel[2];
	    dep=f1->nlevel[1];
	    f1->nlevel[1]=f1->nlevel[2];
	    f1->nlevel[2]=dep;
	    new=f1->nform[1];
	    dep=f1->nport[1];
	    connect1(f1,1,f2->nform[1],f2->nport[1]);
	    connect1(f2,1,new,dep);
	    connect(f2,0,f1,2);
	  }
	  else
	    connect(f1,port,f2,0);
	  break;
	default:
	  connect(f1,port,f2,0);
	  break;
      }
      break;
    case CDR1:
      switch (f2->name) {
	case TRIANGLE:
	  f1->nlevel[port] += f2->nlevel[1];
	  inspect_connect(f1,port,f2->nform[1],f2->nport[1]);
	  myfree(f2);
	  break;
	case CAR:
	  if (port==2) {
	    f1->name=CONS1;
	    if (f1->nlevel[1]!=0) {
	      allocate_form(&new,TRIANGLE,f1->index-1);
	      new->nlevel[1]=f1->nlevel[1];
	      connect1(new,1,f1->nform[1],f1->nport[1]);
	      connect(f1,2,new,0);
	    }
	    else
	      connect(f1,2,f1->nform[1],f1->nport[1]);
	    if (f1->nlevel[2]!=0) {
	      f2->name=TRIANGLE;
	      f2->nlevel[1]=f1->nlevel[2];
	      f2->index=f1->index-1;
	      connect(f1,1,f2,0);
	    }
	    else {
	      connect1(f1,1,f2->nform[1],f2->nport[1]);
	      myfree(f2);
	    }
	  }
	  else
	    connect(f1,port,f2,0);
	  break;
	case TESTNIL:
	  if (port==2) {
	    f1->name=TESTNIL1;
	    f2->name=CDR;
	    dep=f2->index;
	    f2->index=f1->index+f1->nlevel[1];
	    f1->index=dep-f1->nlevel[2];
	    dep=f1->nlevel[1];
	    f1->nlevel[1]=f1->nlevel[2];
	    f1->nlevel[2]=dep;
	    new=f1->nform[1];
	    dep=f1->nport[1];
	    connect1(f1,1,f2->nform[1],f2->nport[1]);
	    connect1(f2,1,new,dep);
	    connect(f2,0,f1,2);
	  }
	  else
	    connect(f1,port,f2,0);
	  break;
	default:
	  connect(f1,port,f2,0);
	  break;
      }
      break;
    default:
      connect(f1,port,f2,0);
      break;
  }
}

/* The following function checks whether it's possible to apply      */
/* function intelligent_connect. Otherwise applies a normal connect. */
void
inspect_connect(FORM *f1, int p1, FORM *f2, int p2)
{
  if (p2==0)
    intelligent_connect(f1,p1,f2);
  else
    connect1(f1,p1,f2,p2);
}

BOOLEAN
membervarlist(BINDINGID *e, VARLIST *l)
{
  while(l)
    if (e->id==l->id->id)
      return TRUE;
    else
      l=l->next;
  return FALSE;
}
  

VARLIST *
mergevarlist(VARLIST *l1, VARLIST *l2)
{
  VARLIST *p;
  if(l1) {
    for(p=l1;p->next;p=p->next) {
      if(membervarlist(p->id,l2)) {
      fprintf(stderr,"Pattern is not linear - expect garbage out!\n");
      }
    }
    if(membervarlist(p->id,l2)) {
    fprintf(stderr,"Pattern is not linear - expect garbage out!\n");
  }
    p->next=l2;
    return l1;
  } else
    return l2;
}

VARLIST *
makevarlist(STBUCKET *e, TERM *t)
{
  BINDINGID *bid;
  VARLIST *vl;
  bid=(BINDINGID*)malloc(sizeof(BINDINGID));
  bid->id=e;
  bid->form=t->rootf;
  vl=(VARLIST*)malloc(sizeof(VARLIST));
  vl->next=NULL;
  vl->id=bid;
  return vl;
}

TERM *
maketerm(FORM *f)
{
  TERM *t;
  t=(TERM*)malloc(sizeof(TERM));
  t->rootf=f;
  t->rootp=0;
  t->vars=NULL;
  return t;
}

TERM *
buildvoidterm(int level)
{
  FORM *newf;
  TERM *t;
  allocate_form(&newf,TRIANGLE,level);
  newf->nlevel[1]=0;
  allocate_term(&t,newf,0,NULL);
  return t;
}
    
void
free_pattern(PATTERN *p)
{
  VARLIST *vl,*vln;
  for(vl=p->var_list;vl;vl=vln) {
    vln=vl->next;
    free(vl);
  }
  free(p);
}
