/****************************************************************/
/*		             MAIN.C          			*/
/****************************************************************/
/* This module implements the main function.			*/
/* It analizes the input parameters, initializes some variable,	*/
/* the symbol table, the destroyer, the garbage and call the 	*/
/* parser.							*/
/****************************************************************/

/****************************************************************/
/* Inclusion of header files.           			*/
/****************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include "include/const.h"
#include "include/types.h"
#include "i/lambda_lexan.i"
#include "i/lambda_parser.i"
#include "i/menu.i"
#include "i/destroyer.i"
#include "i/garbage.i"

/****************************************************************/
/* Main program.               			                */
/****************************************************************/

main(argc,argv)
int argc;
char *argv[];
{
  option=1;
  seetime=0;
  seenode=0;
  seegarb=0;
  if(argc>1)
      if(argc==2)
	    if (strcmp(argv[1],"-s")==0){
		/* do_menu4(); */
		menu();
	    }
	    else if (strcmp(argv[1],"-i")==0)
			info();
		 else{
			printf("Execution failed:Illegal option . . .\n");
			exit(1);
		}
      else if(argc==3)
		if(  ( (strcmp(argv[1],"-s")==0)&&
		       (strcmp(argv[2],"-i")==0) ) ||
		     ( (strcmp(argv[2],"-s")==0)&&
		       (strcmp(argv[1],"-i")==0) ) ){
			info();
			/* do_menu4(); */
			menu();
		}else{
			printf("Execution failed:Illegal option \n");
			printf("or duplicated option . . .\n");
			exit(1);
		}
	    else{
	       printf("Execution failed:Too many parameters . . .\n");
	       exit(1);
	       }
  printf("\n");
  printf("***********************************************************\n");
  printf("***                  Welcome to the                     ***\n");
  printf("***        Bologna Optimal Higher-order Machine         ***\n");
  printf("***       Version 1.1 by A. Asperti, J. Chroboczek,     ***\n");
  printf("***               C. Giovannetti, C. Laneve,            ***\n");
  printf("***              P. Gruppioni and A. Naletto.           ***\n");
  printf("***          Dipartimento di Matematica, Bologna        ***\n");
  printf("***********************************************************\n\n");

  init_symbol_table();
  init_destroy();
  init_garbage();
  lines = 0;
  error_detected = 0;
  quit = 0;
  loading_mode = 0;
  lastinputterm = NULL;
  error_detected = FALSE;

  while (quit == 0)
     {
	printf("opt>");
	yyparse();
	error_detected = FALSE;
	lines = 0;
     }
  printf("good bye\n");
  return 0;
}


