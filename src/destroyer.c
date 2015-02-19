/******************************************************************/
/*                        DESTROYER.C                             */
/******************************************************************/
/* This module implements the destroyer operator, that is to be	  */
/* applied  at the end of a term. 				  */	
/* If the last term is a global defination the graph is stored,   */
/* otherwise each node is freed. In order to do this, each node   */
/* is kept in a bi-linked list that is provided with two access   */   
/* points: 							  */
/* - "headfull": pointer to the global definition's last element  */
/* - "headfree": pointer to the first idle node			  */
/* Only and all the last term's nodes are present between	  */
/* headfull and headfree. If the last term is a definition, 	  */
/* headfull has to be moved to the node preceding headfree, if 	  */
/* the last term is to be deleted, headfree is moved to the node  */
/* following headfull. 						  */
/* The following functions are external:                          */
/* - init_destroy(): Initialises the destroyer by allocating two  */
/*                   nodes (headfree and headfull) and linking    */
/*		     them together.                               */
/* - destroy(): Eliminates the preceding term, moving back        */
/*		headfree to the node following headfull, and      */
/*		doing so makes all the nodes available for	  */
/*		any furure usage				  */
/* - no_destroy(): Makes a graph associated to a global definition*/
/*                 permanent, by moving headfull to the node      */
/*                 preceding headfree.                            */
/******************************************************************/

/******************************************************************/
/* 1. Inclusion of header files                                   */
/******************************************************************/

#include <stdio.h>
#include <stdlib.h>

#include "const.h"
#include "destroyer.h"
#include "dynallhandler.h"
#include "garbage.h"
#include "graphgenerator.h"
#include "types.h"

/****************************************************************/
/* 2. Definitions of variables to be exported.			*/
/****************************************************************/

FORM *headfree;

/****************************************************************/
/* 3. Declaration of names strictly local to the module.	*/
/****************************************************************/

static FORM *headfull;
static unsigned int start_nodes;

/****************************************************************/
/* 4. Declaration of functions strictly local to the module.	*/
/****************************************************************/

/****************************************************************/
/* 5. Definitions of functions to be exported.			*/
/****************************************************************/

/* The following function initialises the destroyer by 	*/
/* allocating two nodes (headfree and headfull) and 	*/
/* linking them together.                               */
void
init_destroy(void)
{
  headfull = malloc_da(sizeof(FORM));
  headfree = malloc_da(sizeof(FORM));
  headfull->next=headfree;
  headfull->prev=NULL;
  headfree->next=NULL;
  headfree->prev=headfull;
  start_nodes=0;
}

/* The following function eliminates the preceding 	*/
/* term, moving back headfree to the node following 	*/
/* headfull, and doing so makes all the nodes available */
/* for any furure usage					*/
void
destroy(void)
{
  if(headfree!=headfull->next){
    num_nodes=start_nodes;
    headfree=headfull->next;
  }
  start_nodes=num_nodes;
  del_head->nform[1]=NULL;
}

/* The following function makes a graph associated to a	*/
/* global definition permanent, by moving headfull to 	*/
/* the node preceding headfree.				*/
void
no_destroy(void)
{
  headfull=headfree->prev;
}
