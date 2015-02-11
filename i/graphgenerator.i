/****************************************************************/
/*	                GRAPHGENERATOR.I 			*/
/****************************************************************/


/****************************************************************/
/* 1. Declarations of variables.				*/
/****************************************************************/
extern unsigned		max_nodes,num_nodes;
extern BOOLEAN		is_global_var;
extern int		rec_er;

/****************************************************************/
/* 2. Declarations of functions.				*/
/****************************************************************/

extern 		FORM	*closeterm();
extern 		TERM    *buildvarterm(),
        		*buildlambdaterm(),
        		*buildplambdaterm(),
        		*buildappterm(),
        		*buildletinterm(),
                        *build_mu_term(),
                        *buildtrueterm(),
                        *buildfalseterm(),
                        *buildifelseterm(),
			*buildandterm(),
			*buildorterm(),
			*buildnotterm(),
			*buildrelopterm(),
			*buildmatterm(),
			*buildminusterm(),
			*buildintterm(),
			*buildlist(),
			*buildlist1(),
			*buildcarterm(),
			*buildcdrterm(),
			*buildtestnil(),
			*buildnillist(),
                        *buildvoidterm();
extern                  connect(),
			int_connect(),
			bool_connect(),
			connect1();
extern                  allocate_form();
extern                  myfree();
extern                  free_varlist();
VARLIST                 *mergevarlist(),
                        *makevarlist();
TERM                    *maketerm();
