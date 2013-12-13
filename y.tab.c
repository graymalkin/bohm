extern char *malloc(), *realloc();

# line 101 "lambda_parser.y"
#include                <malloc.h>
#include		<stdio.h>
#include		"h/const.h"
#include		"h/types.h"

# line 113 "lambda_parser.y"
#include		"e/lambda_lexan.e"
#include		"e/graphgenerator.e"
#include		"e/sthandler.e"
#include		"e/errorhandler.e"
#include		"e/scope_analysis.e"
#include		"e/reducer.e"
#include		"e/inspect.e"
#include		"e/loader.e"
#include		"e/garbage.e"
#include		"e/menu.e"
#include		"e/destroyer.e"
#include		"e/save.e"


# line 134 "lambda_parser.y"
BOOLEAN			error_detected,
			       /* flag indicating whether an *
			       /* error has been detected */
			       /* during the analysis of the */
			       /* P source file */
			quit,
			       /* flag indicating quit request */
			loading_mode;
			       /* flag indicating if parsing is */
			       /* done after a load directive */
FORM                    *lastinputterm;
			       /* pointer to the root of the */
			       /* term in input */

# line 154 "lambda_parser.y"
int                    app_nesting_depth;
PATTERN                *pattmp;

# line 162 "lambda_parser.y"
typedef union 	{
		STBUCKET	*st_bucket;
					/* pointer to a symbol */
					/* table bucket */
		int		num_const;
					/* numerical constant */
		TERM		*term;
					/* graph representation */
					/* of the term */
		FORM		*root;
					/* root_form  */
                char            *astring;
                PATTERN         *pattern;
	} YYSTYPE;
# define EXPRDELIM 257
# define ID 258
# define NUMCONST 259
# define EQUAL 260
# define LEQUAL 261
# define MEQUAL 262
# define NOTEQUAL 263
# define LETKW 400
# define INKW 401
# define INSPECTKW 402
# define QUITKW 403
# define LOADKW 404
# define LETRECKW 405
# define TRUEKW 406
# define FALSEKW 407
# define IFKW 408
# define THENKW 409
# define ELSEKW 410
# define ANDKW 411
# define ORKW 412
# define NOTKW 413
# define DIVKW 414
# define MODKW 415
# define CONSKW 416
# define HEADKW 417
# define TAILKW 418
# define TESTNILKW 419
# define DEFKW 420
# define SHAREKW 421
# define NILKW 422
# define GARBAGEKW 423
# define OPTIONKW 424
# define INFOKW 425
# define SAVEKW 426
# define ASTRING 427
# define NEG 292
#define yyclearin yychar = -1
#define yyerrok yyerrflag = 0
extern int yychar;
extern int yyerrflag;
#ifndef YYMAXDEPTH
#define YYMAXDEPTH 150
#endif
YYSTYPE yylval, yyval;
# define YYERRCODE 256

# line 712 "lambda_parser.y"


 /***************************************************************/
 /* 11. Auxiliary functions.					*/
 /***************************************************************/

HIDDEN
retract_token()
{
	yyless(0);
}

HIDDEN
yyerror()
{
	signal_error(SINTAXERROR);
	yyerrok;
}



int yyexca[] ={
-1, 0,
	0, 4,
	-2, 2,
-1, 1,
	0, -1,
	-2, 0,
	};
# define YYNPROD 73
# define YYLAST 891
int yyact[]={

    16,    29,    30,    31,    75,    10,    71,   110,   111,    69,
    58,    47,    45,    57,    46,    53,   129,   109,   108,    74,
    96,    16,    32,    33,    34,    35,    10,    73,    72,    70,
    51,    50,    47,   119,   118,   114,    99,    98,    66,     9,
    89,    16,   132,   143,   135,   150,    10,   134,    90,   117,
    64,    28,    17,    63,    62,    61,    91,     4,   121,   149,
   120,    16,   116,    56,   112,     3,    21,    54,     7,     5,
    68,     2,    28,    17,    65,     1,    47,    45,   106,    46,
   147,    47,    45,     0,    46,     0,     0,     0,    47,    45,
    93,    46,    28,    17,    39,     0,    42,    47,    45,    39,
    46,    42,     0,     0,    47,    45,    39,    46,    42,     0,
     0,     0,    28,    17,     0,    39,     0,    42,    47,    45,
   131,    46,    39,     0,    42,     0,     0,   105,   126,    47,
    45,   113,    46,   125,    47,    45,    39,    46,    42,     0,
     0,     0,   124,    47,    45,   127,    46,    39,   140,    42,
     0,   133,    39,     0,    42,     0,     0,     0,   107,     0,
     0,    39,     0,    42,     0,     0,     0,   141,     0,     0,
   144,     0,    47,    45,   123,    46,     0,   148,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    39,     0,    42,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,    47,    45,     0,    46,     8,     0,    15,    14,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    39,     0,    42,     0,     0,     0,     0,     0,    97,    15,
    14,     0,     0,     0,    47,    45,    92,    46,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
    14,     0,    39,     0,    42,    47,    45,     0,    46,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    15,
    14,     0,     0,    39,     0,    42,     0,     0,     0,     0,
     0,     0,     0,     0,    40,    43,    44,    41,     0,    40,
    43,    44,    41,     0,     0,     0,    40,    43,    44,    41,
    47,    45,     0,    46,     0,    40,    43,    44,    41,     0,
     0,     0,    40,    43,    44,    41,     0,     0,    39,     0,
    42,     0,     0,     0,     0,     0,    40,    43,    44,    41,
     0,     0,     0,     0,     0,     0,     0,    40,    43,    44,
    41,     0,    40,    43,    44,    41,     0,     0,     0,     0,
    18,    40,    43,    44,    41,    19,    12,    13,    20,     0,
     0,     0,     0,    22,     0,     0,    23,    24,    25,    26,
    11,    18,    27,    48,    49,     0,    19,    12,    13,    20,
    40,    43,    44,    41,    22,     0,    94,    23,    24,    25,
    26,    18,    95,    27,    48,    49,    19,    12,    13,    20,
     0,     0,     0,     0,    22,     0,     0,    23,    24,    25,
    26,    18,     0,    27,     0,     0,    19,    12,    13,    20,
    40,    43,    44,    41,    22,     0,     0,    23,    24,    25,
    26,     0,     0,    27,     0,    37,    38,   145,    48,    49,
    37,    38,     0,    48,    49,     0,     0,    37,    38,     0,
    48,    49,    40,    43,    44,    41,    37,    38,     0,    48,
    49,     0,   138,    37,    38,     0,    48,    49,     0,     0,
    36,     0,     0,    40,    43,    44,    41,    37,    38,     0,
    48,    49,     0,     0,     0,     0,     0,     0,    37,    38,
     0,    48,    49,    37,    38,     0,    48,    49,     0,     0,
     0,     0,    37,    38,     0,    48,    49,    47,    45,     0,
    46,     0,     0,     0,     0,     0,     0,     0,    40,    43,
    44,    41,     0,     0,     0,    39,     0,    42,     0,     0,
     0,    37,    38,     0,    48,    49,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,   100,
     0,    37,    38,    67,    48,    49,     0,     6,     0,     0,
     0,     0,     0,     0,    52,     0,     0,     0,     0,     0,
    55,     0,     0,     0,    59,     0,    60,     0,     0,     0,
     0,     0,     0,    37,    38,     0,    48,    49,     0,     0,
     0,    76,    77,    78,    79,    80,    81,    82,    83,    84,
    85,    86,    87,    88,    37,    38,     0,    48,    49,     0,
     0,     0,     0,     0,     0,   101,   102,   103,   104,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,   115,     0,     0,    37,
    38,     0,    48,    49,   122,     0,     0,     0,     0,     0,
     0,   128,     0,     0,     0,     0,   130,     0,     0,     0,
     0,     0,     0,     0,   136,   137,     0,   139,     0,     0,
     0,     0,     0,     0,     0,   115,   142,     0,     0,     0,
     0,     0,   146,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,   151,     0,    40,    43,    44,    41,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,    48,
    49 };
int yypact[]={

    22, -1000, -1000,   -40,  -401, -1000,   223,  -226,  -227, -1000,
     1,  -243, -1000, -1000, -1000, -1000,     1, -1000,  -245,  -248,
     1, -1000,     1,    15,    14,    13,    10, -1000,   -19,  -249,
  -228,  -421,  -229,  -230,  -238,  -423, -1000,     1,     1,     1,
     1,     1,     1,     1,     1,     1,     1,     1,     1,     1,
 -1000, -1000, -1000,   -21,     7,   202,   -20,   -24,   -25,   170,
   475,     1,     1,     1,     1, -1000, -1000,    34,  -239, -1000,
 -1000,  -240, -1000, -1000, -1000,  -250,   475,   475,   -31,   -31,
   -31,   -31,   -31,   -31,   -10,   -10, -1000, -1000, -1000, -1000,
 -1000,    21,     1, -1000,     9, -1000,   -20, -1000, -1000, -1000,
     1,   130,   101,    92,    87, -1000,     1,     1, -1000, -1000,
 -1000,  -241,     1, -1000, -1000,    76,    -4,   -20,     6,     0,
     1,     1,    62,     1, -1000, -1000, -1000, -1000,    55, -1000,
   268,     1,     1,    -1, -1000,   -20,    46,   268,     1,    39,
 -1000, -1000,   268,   -20, -1000, -1000,   268, -1000,     4,     1,
 -1000,   268 };
int yypgo[]={

     0,    75,    71,    70,    69,    68,   583,    39,    67,    35,
    38,    66,    33,    34,    65,    64,    63,    62,    60,    59,
    58,    56 };
int yyr1[]={

     0,     1,    14,     1,     1,     2,     2,     2,     2,     2,
     2,     2,     2,     3,     3,     4,     4,    15,     5,     6,
     6,     6,     6,     6,     6,     6,     6,     6,     6,     6,
     6,     6,     6,     6,     7,     7,     7,     7,     7,    16,
    17,     7,    18,    19,     7,    20,     7,     7,     7,     7,
     7,     7,     7,     7,    11,    11,    11,    10,    10,    10,
     8,     8,    21,     8,     9,     9,    13,    13,    12,    12,
    12,    12,     4 };
int yyr2[]={

     0,     2,     1,     5,     1,     9,     7,     9,     7,     7,
     7,     9,    11,     1,     3,     5,     5,     1,    11,     3,
     5,     7,     7,     7,     7,     7,     7,     7,     7,     7,
     7,     7,     7,     7,     3,     3,     3,     3,     7,     1,
     1,    13,     1,     1,    17,     1,    11,    13,     3,     5,
    13,     9,     9,     9,     3,     5,     5,     5,     7,     9,
     2,     7,     1,     7,     3,     7,     3,     7,    13,     3,
     7,     3,     5 };
int yychk[]={

 -1000,    -1,    -2,   -14,    35,    -4,    -6,    -5,   256,    -7,
    45,   420,   406,   407,   259,   258,    40,    92,   400,   405,
   408,   -11,   413,   416,   417,   418,   419,   422,    91,   402,
   403,   404,   423,   424,   425,   426,   257,   411,   412,    60,
   260,   263,    62,   261,   262,    43,    45,    42,   414,   415,
   257,   257,    -6,   258,    -8,    -6,   -16,   258,   258,    -6,
    -6,    40,    40,    40,    40,    93,   -10,    -6,    -3,   258,
   257,   427,   257,   257,   257,   427,    -6,    -6,    -6,    -6,
    -6,    -6,    -6,    -6,    -6,    -6,    -6,    -6,    -6,    61,
    41,   -21,    44,   -12,   416,   422,    40,   258,    61,    61,
   409,    -6,    -6,    -6,    -6,    93,    44,   124,   257,   257,
   257,   258,   -15,    -7,    -9,    -6,   -17,    40,   -13,   -12,
   -18,   -20,    -6,    44,    41,    41,    41,   -10,    -6,   257,
    -6,    44,    46,   -12,    41,    44,    -6,    -6,   410,    -6,
    93,    -9,    -6,    44,   -13,   401,    -6,    41,   -12,   -19,
    41,    -6 };
int yydef[]={

    -2,    -2,     1,     0,     0,     3,     0,     0,     0,    19,
     0,     0,    34,    35,    36,    37,     0,    39,     0,     0,
     0,    48,     0,     0,     0,     0,     0,    54,     0,    13,
     0,     0,     0,     0,     0,     0,    15,     0,     0,     0,
     0,     0,     0,     0,     0,     0,     0,     0,     0,     0,
    16,    72,    20,     0,    62,    60,     0,     0,     0,     0,
    49,     0,     0,     0,     0,    55,    56,     0,     0,    14,
     6,     0,     8,     9,    10,     0,    21,    22,    23,    24,
    25,    26,    27,    28,    29,    30,    31,    32,    33,    17,
    38,     0,     0,    40,     0,    69,     0,    71,    42,    45,
     0,     0,     0,     0,     0,    57,     0,     0,     5,     7,
    11,     0,     0,    63,    61,    64,     0,     0,     0,    66,
     0,     0,     0,     0,    51,    52,    53,    58,     0,    12,
    18,     0,     0,     0,    70,     0,     0,    46,     0,     0,
    59,    65,    41,     0,    67,    43,    47,    50,     0,     0,
    68,    44 };
typedef struct { char *t_name; int t_val; } yytoktype;
#ifndef YYDEBUG
#	define YYDEBUG	0	/* don't allow debugging */
#endif

#if YYDEBUG

yytoktype yytoks[] =
{
	"EXPRDELIM",	257,
	"ID",	258,
	"NUMCONST",	259,
	"EQUAL",	260,
	"LEQUAL",	261,
	"MEQUAL",	262,
	"NOTEQUAL",	263,
	"LETKW",	400,
	"INKW",	401,
	"INSPECTKW",	402,
	"QUITKW",	403,
	"LOADKW",	404,
	"LETRECKW",	405,
	"TRUEKW",	406,
	"FALSEKW",	407,
	"IFKW",	408,
	"THENKW",	409,
	"ELSEKW",	410,
	"ANDKW",	411,
	"ORKW",	412,
	"NOTKW",	413,
	"DIVKW",	414,
	"MODKW",	415,
	"CONSKW",	416,
	"HEADKW",	417,
	"TAILKW",	418,
	"TESTNILKW",	419,
	"DEFKW",	420,
	"SHAREKW",	421,
	"NILKW",	422,
	"GARBAGEKW",	423,
	"OPTIONKW",	424,
	"INFOKW",	425,
	"SAVEKW",	426,
	"ASTRING",	427,
	".",	46,
	"=",	61,
	"<",	60,
	">",	62,
	"+",	43,
	"-",	45,
	"*",	42,
	"NEG",	292,
	"-unknown-",	-1	/* ends search */
};

char * yyreds[] =
{
	"-no such reduction-",
	"input : directive",
	"input : /* empty */",
	"input : term",
	"input : /* empty */",
	"directive : '#' INSPECTKW arg EXPRDELIM",
	"directive : '#' QUITKW EXPRDELIM",
	"directive : '#' LOADKW ASTRING EXPRDELIM",
	"directive : '#' GARBAGEKW EXPRDELIM",
	"directive : '#' OPTIONKW EXPRDELIM",
	"directive : '#' INFOKW EXPRDELIM",
	"directive : '#' SAVEKW ASTRING EXPRDELIM",
	"directive : '#' SAVEKW ASTRING ID EXPRDELIM",
	"arg : /* empty */",
	"arg : ID",
	"term : expr EXPRDELIM",
	"term : global_decl EXPRDELIM",
	"global_decl : DEFKW ID '='",
	"global_decl : DEFKW ID '=' expr",
	"expr : expr0",
	"expr : '-' expr",
	"expr : expr ANDKW expr",
	"expr : expr ORKW expr",
	"expr : expr '<' expr",
	"expr : expr EQUAL expr",
	"expr : expr NOTEQUAL expr",
	"expr : expr '>' expr",
	"expr : expr LEQUAL expr",
	"expr : expr MEQUAL expr",
	"expr : expr '+' expr",
	"expr : expr '-' expr",
	"expr : expr '*' expr",
	"expr : expr DIVKW expr",
	"expr : expr MODKW expr",
	"expr0 : TRUEKW",
	"expr0 : FALSEKW",
	"expr0 : NUMCONST",
	"expr0 : ID",
	"expr0 : '(' applist ')'",
	"expr0 : '\\'",
	"expr0 : '\\' pattern",
	"expr0 : '\\' pattern '.' expr",
	"expr0 : LETKW ID '='",
	"expr0 : LETKW ID '=' expr INKW",
	"expr0 : LETKW ID '=' expr INKW expr",
	"expr0 : LETRECKW ID '='",
	"expr0 : LETRECKW ID '=' expr",
	"expr0 : IFKW expr THENKW expr ELSEKW expr",
	"expr0 : list",
	"expr0 : NOTKW expr",
	"expr0 : CONSKW '(' expr ',' expr ')'",
	"expr0 : HEADKW '(' expr ')'",
	"expr0 : TAILKW '(' expr ')'",
	"expr0 : TESTNILKW '(' expr ')'",
	"list : NILKW",
	"list : '[' ']'",
	"list : '[' exprlist",
	"exprlist : expr ']'",
	"exprlist : expr ',' exprlist",
	"exprlist : expr '|' expr ']'",
	"applist : expr",
	"applist : expr ',' comlist",
	"applist : applist",
	"applist : applist expr0",
	"comlist : expr",
	"comlist : expr ',' comlist",
	"comlistpat : pattern",
	"comlistpat : pattern ',' comlistpat",
	"pattern : CONSKW '(' pattern ',' pattern ')'",
	"pattern : NILKW",
	"pattern : '(' comlistpat ')'",
	"pattern : ID",
	"term : error EXPRDELIM",
};
#endif /* YYDEBUG */
#line 1 "/usr/lib/yaccpar"
/*	@(#)yaccpar 1.10 89/04/04 SMI; from S5R3 1.10	*/

/*
** Skeleton parser driver for yacc output
*/

/*
** yacc user known macros and defines
*/
#define YYERROR		goto yyerrlab
#define YYACCEPT	{ free(yys); free(yyv); return(0); }
#define YYABORT		{ free(yys); free(yyv); return(1); }
#define YYBACKUP( newtoken, newvalue )\
{\
	if ( yychar >= 0 || ( yyr2[ yytmp ] >> 1 ) != 1 )\
	{\
		yyerror( "syntax error - cannot backup" );\
		goto yyerrlab;\
	}\
	yychar = newtoken;\
	yystate = *yyps;\
	yylval = newvalue;\
	goto yynewstate;\
}
#define YYRECOVERING()	(!!yyerrflag)
#ifndef YYDEBUG
#	define YYDEBUG	1	/* make debugging available */
#endif

/*
** user known globals
*/
int yydebug;			/* set to 1 to get debugging */

/*
** driver internal defines
*/
#define YYFLAG		(-1000)

/*
** static variables used by the parser
*/
static YYSTYPE *yyv;			/* value stack */
static int *yys;			/* state stack */

static YYSTYPE *yypv;			/* top of value stack */
static int *yyps;			/* top of state stack */

static int yystate;			/* current state */
static int yytmp;			/* extra var (lasts between blocks) */

int yynerrs;			/* number of errors */

int yyerrflag;			/* error recovery flag */
int yychar;			/* current input token number */


/*
** yyparse - return 0 if worked, 1 if syntax error not recovered from
*/
int
yyparse()
{
	register YYSTYPE *yypvt;	/* top of value stack for $vars */
	unsigned yymaxdepth = YYMAXDEPTH;

	/*
	** Initialize externals - yyparse may be called more than once
	*/
	yyv = (YYSTYPE*)malloc(yymaxdepth*sizeof(YYSTYPE));
	yys = (int*)malloc(yymaxdepth*sizeof(int));
	if (!yyv || !yys)
	{
		yyerror( "out of memory" );
		return(1);
	}
	yypv = &yyv[-1];
	yyps = &yys[-1];
	yystate = 0;
	yytmp = 0;
	yynerrs = 0;
	yyerrflag = 0;
	yychar = -1;

	goto yystack;
	{
		register YYSTYPE *yy_pv;	/* top of value stack */
		register int *yy_ps;		/* top of state stack */
		register int yy_state;		/* current state */
		register int  yy_n;		/* internal state number info */

		/*
		** get globals into registers.
		** branch to here only if YYBACKUP was called.
		*/
	yynewstate:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;
		goto yy_newstate;

		/*
		** get globals into registers.
		** either we just started, or we just finished a reduction
		*/
	yystack:
		yy_pv = yypv;
		yy_ps = yyps;
		yy_state = yystate;

		/*
		** top of for (;;) loop while no reductions done
		*/
	yy_stack:
		/*
		** put a state and value onto the stacks
		*/
#if YYDEBUG
		/*
		** if debugging, look up token value in list of value vs.
		** name pairs.  0 and negative (-1) are special values.
		** Note: linear search is used since time is not a real
		** consideration while debugging.
		*/
		if ( yydebug )
		{
			register int yy_i;

			(void)printf( "State %d, token ", yy_state );
			if ( yychar == 0 )
				(void)printf( "end-of-file\n" );
			else if ( yychar < 0 )
				(void)printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				(void)printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ++yy_ps >= &yys[ yymaxdepth ] )	/* room on stack? */
		{
			/*
			** reallocate and recover.  Note that pointers
			** have to be reset, or bad things will happen
			*/
			int yyps_index = (yy_ps - yys);
			int yypv_index = (yy_pv - yyv);
			int yypvt_index = (yypvt - yyv);
			yymaxdepth += YYMAXDEPTH;
			yyv = (YYSTYPE*)realloc((char*)yyv,
				yymaxdepth * sizeof(YYSTYPE));
			yys = (int*)realloc((char*)yys,
				yymaxdepth * sizeof(int));
			if (!yyv || !yys)
			{
				yyerror( "yacc stack overflow" );
				return(1);
			}
			yy_ps = yys + yyps_index;
			yy_pv = yyv + yypv_index;
			yypvt = yyv + yypvt_index;
		}
		*yy_ps = yy_state;
		*++yy_pv = yyval;

		/*
		** we have a new state - find out what to do
		*/
	yy_newstate:
		if ( ( yy_n = yypact[ yy_state ] ) <= YYFLAG )
			goto yydefault;		/* simple state */
#if YYDEBUG
		/*
		** if debugging, need to mark whether new token grabbed
		*/
		yytmp = yychar < 0;
#endif
		if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
			yychar = 0;		/* reached EOF */
#if YYDEBUG
		if ( yydebug && yytmp )
		{
			register int yy_i;

			(void)printf( "Received token " );
			if ( yychar == 0 )
				(void)printf( "end-of-file\n" );
			else if ( yychar < 0 )
				(void)printf( "-none-\n" );
			else
			{
				for ( yy_i = 0; yytoks[yy_i].t_val >= 0;
					yy_i++ )
				{
					if ( yytoks[yy_i].t_val == yychar )
						break;
				}
				(void)printf( "%s\n", yytoks[yy_i].t_name );
			}
		}
#endif /* YYDEBUG */
		if ( ( ( yy_n += yychar ) < 0 ) || ( yy_n >= YYLAST ) )
			goto yydefault;
		if ( yychk[ yy_n = yyact[ yy_n ] ] == yychar )	/*valid shift*/
		{
			yychar = -1;
			yyval = yylval;
			yy_state = yy_n;
			if ( yyerrflag > 0 )
				yyerrflag--;
			goto yy_stack;
		}

	yydefault:
		if ( ( yy_n = yydef[ yy_state ] ) == -2 )
		{
#if YYDEBUG
			yytmp = yychar < 0;
#endif
			if ( ( yychar < 0 ) && ( ( yychar = yylex() ) < 0 ) )
				yychar = 0;		/* reached EOF */
#if YYDEBUG
			if ( yydebug && yytmp )
			{
				register int yy_i;

				(void)printf( "Received token " );
				if ( yychar == 0 )
					(void)printf( "end-of-file\n" );
				else if ( yychar < 0 )
					(void)printf( "-none-\n" );
				else
				{
					for ( yy_i = 0;
						yytoks[yy_i].t_val >= 0;
						yy_i++ )
					{
						if ( yytoks[yy_i].t_val
							== yychar )
						{
							break;
						}
					}
					(void)printf( "%s\n", yytoks[yy_i].t_name );
				}
			}
#endif /* YYDEBUG */
			/*
			** look through exception table
			*/
			{
				register int *yyxi = yyexca;

				while ( ( *yyxi != -1 ) ||
					( yyxi[1] != yy_state ) )
				{
					yyxi += 2;
				}
				while ( ( *(yyxi += 2) >= 0 ) &&
					( *yyxi != yychar ) )
					;
				if ( ( yy_n = yyxi[1] ) < 0 )
					YYACCEPT;
			}
		}

		/*
		** check for syntax error
		*/
		if ( yy_n == 0 )	/* have an error */
		{
			/* no worry about speed here! */
			switch ( yyerrflag )
			{
			case 0:		/* new error */
				yyerror( "syntax error" );
				goto skip_init;
			yyerrlab:
				/*
				** get globals into registers.
				** we have a user generated syntax type error
				*/
				yy_pv = yypv;
				yy_ps = yyps;
				yy_state = yystate;
				yynerrs++;
			skip_init:
			case 1:
			case 2:		/* incompletely recovered error */
					/* try again... */
				yyerrflag = 3;
				/*
				** find state where "error" is a legal
				** shift action
				*/
				while ( yy_ps >= yys )
				{
					yy_n = yypact[ *yy_ps ] + YYERRCODE;
					if ( yy_n >= 0 && yy_n < YYLAST &&
						yychk[yyact[yy_n]] == YYERRCODE)					{
						/*
						** simulate shift of "error"
						*/
						yy_state = yyact[ yy_n ];
						goto yy_stack;
					}
					/*
					** current state has no shift on
					** "error", pop stack
					*/
#if YYDEBUG
#	define _POP_ "Error recovery pops state %d, uncovers state %d\n"
					if ( yydebug )
						(void)printf( _POP_, *yy_ps,
							yy_ps[-1] );
#	undef _POP_
#endif
					yy_ps--;
					yy_pv--;
				}
				/*
				** there is no state on stack with "error" as
				** a valid shift.  give up.
				*/
				YYABORT;
			case 3:		/* no shift yet; eat a token */
#if YYDEBUG
				/*
				** if debugging, look up token in list of
				** pairs.  0 and negative shouldn't occur,
				** but since timing doesn't matter when
				** debugging, it doesn't hurt to leave the
				** tests here.
				*/
				if ( yydebug )
				{
					register int yy_i;

					(void)printf( "Error recovery discards " );
					if ( yychar == 0 )
						(void)printf( "token end-of-file\n" );
					else if ( yychar < 0 )
						(void)printf( "token -none-\n" );
					else
					{
						for ( yy_i = 0;
							yytoks[yy_i].t_val >= 0;
							yy_i++ )
						{
							if ( yytoks[yy_i].t_val
								== yychar )
							{
								break;
							}
						}
						(void)printf( "token %s\n",
							yytoks[yy_i].t_name );
					}
				}
#endif /* YYDEBUG */
				if ( yychar == 0 )	/* reached EOF. quit */
					YYABORT;
				yychar = -1;
				goto yy_newstate;
			}
		}/* end if ( yy_n == 0 ) */
		/*
		** reduction by production yy_n
		** put stack tops, etc. so things right after switch
		*/
#if YYDEBUG
		/*
		** if debugging, print the string that is the user's
		** specification of the reduction which is just about
		** to be done.
		*/
		if ( yydebug )
			(void)printf( "Reduce by (%d) \"%s\"\n",
				yy_n, yyreds[ yy_n ] );
#endif
		yytmp = yy_n;			/* value to switch over */
		yypvt = yy_pv;			/* $vars top of value stack */
		/*
		** Look in goto table for next state
		** Sorry about using yy_state here as temporary
		** register variable, but why not, if it works...
		** If yyr2[ yy_n ] doesn't have the low order bit
		** set, then there is no action to be done for
		** this reduction.  So, no saving & unsaving of
		** registers done.  The only difference between the
		** code just after the if and the body of the if is
		** the goto yy_stack in the body.  This way the test
		** can be made before the choice of what to do is needed.
		*/
		{
			/* length of production doubled with extra bit */
			register int yy_len = yyr2[ yy_n ];

			if ( !( yy_len & 01 ) )
			{
				yy_len >>= 1;
				yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
				yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
					*( yy_ps -= yy_len ) + 1;
				if ( yy_state >= YYLAST ||
					yychk[ yy_state =
					yyact[ yy_state ] ] != -yy_n )
				{
					yy_state = yyact[ yypgo[ yy_n ] ];
				}
				goto yy_stack;
			}
			yy_len >>= 1;
			yyval = ( yy_pv -= yy_len )[1];	/* $$ = $1 */
			yy_state = yypgo[ yy_n = yyr1[ yy_n ] ] +
				*( yy_ps -= yy_len ) + 1;
			if ( yy_state >= YYLAST ||
				yychk[ yy_state = yyact[ yy_state ] ] != -yy_n )
			{
				yy_state = yyact[ yypgo[ yy_n ] ];
			}
		}
					/* save until reenter driver code */
		yystate = yy_state;
		yyps = yy_ps;
		yypv = yy_pv;
	}
	/*
	** code supplied by user is placed in this switch
	*/
	switch( yytmp )
	{
		
case 2:
# line 267 "lambda_parser.y"
{
				   app_nesting_depth = 0;
				   destroy();
				   lastinputterm=NULL;
				} break;
case 3:
# line 273 "lambda_parser.y"
{
				   yyval.root = yypvt[-0].root;
				} break;
case 4:
# line 277 "lambda_parser.y"
{
				   quit = TRUE;
				   YYACCEPT;
				} break;
case 5:
# line 284 "lambda_parser.y"
{
				   yyval.root = yypvt[-1].root;
				   inspect_driver(yypvt[-1].root);
				   YYACCEPT;
				} break;
case 6:
# line 290 "lambda_parser.y"
{
				   quit = TRUE;
				   YYACCEPT;
				} break;
case 7:
# line 295 "lambda_parser.y"
{
				   compile(yypvt[-1].astring);
                                   free(yypvt[-1].astring);
				   YYACCEPT;
				} break;
case 8:
# line 301 "lambda_parser.y"
{
				   user();
				   YYACCEPT;
				} break;
case 9:
# line 306 "lambda_parser.y"
{
				   menu();
				   YYACCEPT;
				} break;
case 10:
# line 311 "lambda_parser.y"
{
				   info();
				   YYACCEPT;
				} break;
case 11:
# line 316 "lambda_parser.y"
{
				   save(yypvt[-1].astring,lastinputterm,NULL);
                                   free(yypvt[-1].astring);
				   YYACCEPT;
				} break;
case 12:
# line 322 "lambda_parser.y"
{
				   if (defined(yypvt[-1].st_bucket))
				      save(yypvt[-2].astring,yypvt[-1].st_bucket->curr_binding->root,yypvt[-1].st_bucket->id);
				   else
				      {
					 signal_error(UNBOUND_VARIABLE);
					 YYACCEPT;
				      }
                                   free(yypvt[-2].astring);
				   YYACCEPT;
				} break;
case 13:
# line 336 "lambda_parser.y"
{
				   yyval.root = lastinputterm;
				} break;
case 14:
# line 340 "lambda_parser.y"
{
				   if (defined(yypvt[-0].st_bucket))
				      yyval.root = yypvt[-0].st_bucket->curr_binding->root;
				   else
				      {
					 signal_error(UNBOUND_VARIABLE);
					 YYACCEPT;
				      }
				 } break;
case 15:
# line 352 "lambda_parser.y"
{
				  lastinputterm = closeterm(0,yypvt[-1].term);
				  yyval.root = lastinputterm;
				  reduce_term(yyval.root);
				  YYACCEPT;
				} break;
case 16:
# line 359 "lambda_parser.y"
{
				  no_destroy();
				  YYACCEPT;
				} break;
case 17:
# line 373 "lambda_parser.y"
{
				  app_nesting_depth++;
				} break;
case 18:
# line 377 "lambda_parser.y"
{
				  app_nesting_depth--;
				  lastinputterm = closeterm(1,yypvt[-0].term);
				  yyval.root = lastinputterm;
				  create_variable_binding(yypvt[-3].st_bucket,yyval.root,DEF);
				} break;
case 19:
# line 401 "lambda_parser.y"
{
                                  yyval.term = yypvt[-0].term;
                                } break;
case 20:
# line 405 "lambda_parser.y"
{
		 		  yyval.term = buildminusterm(app_nesting_depth, yypvt[-0].term);
				} break;
case 21:
# line 409 "lambda_parser.y"
{
				  yyval.term = buildandterm(app_nesting_depth,
						       yypvt[-2].term,yypvt[-0].term);
				} break;
case 22:
# line 414 "lambda_parser.y"
{
				  yyval.term = buildorterm(app_nesting_depth,
						       yypvt[-2].term,yypvt[-0].term);
				} break;
case 23:
# line 419 "lambda_parser.y"
{
		 		  yyval.term = buildrelopterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,LESS);
		 		} break;
case 24:
# line 424 "lambda_parser.y"
{
		 		  yyval.term = buildrelopterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,EQ);
		 		} break;
case 25:
# line 429 "lambda_parser.y"
{
				  yyval.term = buildrelopterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,NOTEQ);
		 		} break;
case 26:
# line 434 "lambda_parser.y"
{
		 		  yyval.term = buildrelopterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,MORE);
				} break;
case 27:
# line 439 "lambda_parser.y"
{
		 		  yyval.term = buildrelopterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,LEQ);
		 		} break;
case 28:
# line 444 "lambda_parser.y"
{
		 		  yyval.term = buildrelopterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,MEQ);
		 		} break;
case 29:
# line 449 "lambda_parser.y"
{
				  yyval.term = buildmatterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,ADD);
				} break;
case 30:
# line 454 "lambda_parser.y"
{
		 		  yyval.term = buildmatterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,SUB);
				} break;
case 31:
# line 459 "lambda_parser.y"
{
		 		  yyval.term = buildmatterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,PROD);
				} break;
case 32:
# line 464 "lambda_parser.y"
{
		 		  yyval.term = buildmatterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,DIV);
				} break;
case 33:
# line 469 "lambda_parser.y"
{
				  yyval.term = buildmatterm(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term,MOD);
		 		} break;
case 34:
# line 476 "lambda_parser.y"
{
				  yyval.term = buildtrueterm(app_nesting_depth);
				} break;
case 35:
# line 480 "lambda_parser.y"
{
				  yyval.term = buildfalseterm(app_nesting_depth);
				} break;
case 36:
# line 484 "lambda_parser.y"
{
				  yyval.term = buildintterm(app_nesting_depth,yypvt[-0].num_const);
				} break;
case 37:
# line 488 "lambda_parser.y"
{
				  if (defined(yypvt[-0].st_bucket))
				     yyval.term = buildvarterm(app_nesting_depth,yypvt[-0].st_bucket);
				  else
				     {
					signal_error(UNBOUND_VARIABLE);
					YYERROR;
				     }
				} break;
case 38:
# line 498 "lambda_parser.y"
{
				  yyval.term = yypvt[-1].term;
				} break;
case 39:
# line 512 "lambda_parser.y"
{
				  push_local_env();
                                  app_nesting_depth++;
				} break;
case 40:
# line 517 "lambda_parser.y"
{
                                  app_nesting_depth--;
                                } break;
case 41:
# line 521 "lambda_parser.y"
{
                                  pattmp=yypvt[-3].pattern;
                                  yyval.term = 
                                    buildplambdaterm(app_nesting_depth,yypvt[-3].pattern,yypvt[-0].term);
                                  free_pattern(pattmp);
				  pop_local_env();
				} break;
case 42:
# line 529 "lambda_parser.y"
{
				  app_nesting_depth++;
				} break;
case 43:
# line 533 "lambda_parser.y"
{
				  app_nesting_depth--;
				  push_local_env();
				  create_variable_binding(yypvt[-4].st_bucket,NULL,LOCAL);
				} break;
case 44:
# line 539 "lambda_parser.y"
{
				  yyval.term = buildletinterm(app_nesting_depth,
						      yypvt[-6].st_bucket,yypvt[-3].term,yypvt[-0].term);
				  pop_local_env();
				} break;
case 45:
# line 545 "lambda_parser.y"
{
				  push_local_env();
				  create_variable_binding(yypvt[-1].st_bucket,NULL,LOCAL);
				  app_nesting_depth++;
				 } break;
case 46:
# line 551 "lambda_parser.y"
{
				  yyval.term = build_mu_term(--app_nesting_depth,
						     yypvt[-3].st_bucket,yypvt[-0].term);
				  pop_local_env();
				 } break;
case 47:
# line 557 "lambda_parser.y"
{
				  yyval.term = buildifelseterm(app_nesting_depth,
						       yypvt[-4].term,yypvt[-2].term,yypvt[-0].term);
				} break;
case 48:
# line 562 "lambda_parser.y"
{
				  yyval.term = yypvt[-0].term;
				} break;
case 49:
# line 567 "lambda_parser.y"
{
				  yyval.term = buildnotterm(app_nesting_depth,
		 		  		       yypvt[-0].term);
				} break;
case 50:
# line 572 "lambda_parser.y"
{
		 		  yyval.term = buildlist(app_nesting_depth,
		 		  		       yypvt[-3].term,yypvt[-1].term);
		 		} break;
case 51:
# line 577 "lambda_parser.y"
{
		 		  yyval.term = buildcarterm(app_nesting_depth,
		 		  		       yypvt[-1].term);
		 		} break;
case 52:
# line 582 "lambda_parser.y"
{
				  yyval.term = buildcdrterm(app_nesting_depth,
		 		  		       yypvt[-1].term);
		 		} break;
case 53:
# line 587 "lambda_parser.y"
{
		 		  yyval.term = buildtestnil(app_nesting_depth,
		 		  		       yypvt[-1].term);
				} break;
case 54:
# line 594 "lambda_parser.y"
{
				  yyval.term = buildnillist(app_nesting_depth);
				} break;
case 55:
# line 598 "lambda_parser.y"
{
                                  yyval.term = buildnillist(app_nesting_depth);
				} break;
case 56:
# line 602 "lambda_parser.y"
{
				  yyval.term = yypvt[-0].term;
				} break;
case 57:
# line 607 "lambda_parser.y"
{
				  yyval.term = buildlist(app_nesting_depth,
						yypvt[-1].term,NULL);
				} break;
case 58:
# line 612 "lambda_parser.y"
{
				  yyval.term = buildlist(app_nesting_depth,
						yypvt[-2].term,yypvt[-0].term);
				} break;
case 59:
# line 617 "lambda_parser.y"
{
				  yyval.term = buildlist(app_nesting_depth,
						 yypvt[-3].term,yypvt[-1].term);
				} break;
case 61:
# line 625 "lambda_parser.y"
{
		 		  yyval.term = buildlist(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term);
                                } break;
case 62:
# line 630 "lambda_parser.y"
{
				  app_nesting_depth++;
				} break;
case 63:
# line 634 "lambda_parser.y"
{ app_nesting_depth--;
				  yyval.term = buildappterm(app_nesting_depth,yypvt[-2].term,yypvt[-0].term);
				} break;
case 64:
# line 641 "lambda_parser.y"
{
                                  yyval.term=yypvt[-0].term;
                                } break;
case 65:
# line 645 "lambda_parser.y"
{
		 		  yyval.term = buildlist(app_nesting_depth,
		 		  		       yypvt[-2].term,yypvt[-0].term);
                                } break;
case 66:
# line 652 "lambda_parser.y"
{
                                  yyval.pattern=yypvt[-0].pattern;
                                } break;
case 67:
# line 656 "lambda_parser.y"
{
                                  pattmp=(PATTERN *)malloc(sizeof(PATTERN));
                                  pattmp->term=
                                    buildlist1(app_nesting_depth,
                                              yypvt[-2].pattern->term,yypvt[-0].pattern->term);
                                  pattmp->var_list=
                                    mergevarlist(yypvt[-2].pattern->var_list,yypvt[-0].pattern->var_list);
                                  free(yypvt[-2].pattern);
                                  free(yypvt[-0].pattern);
                                  yyval.pattern=pattmp;
                                } break;
case 68:
# line 669 "lambda_parser.y"
{
                                  pattmp=(PATTERN *)malloc(sizeof(PATTERN));
                                  pattmp->term=
                                    buildlist1(app_nesting_depth,
                                              yypvt[-3].pattern->term,yypvt[-1].pattern->term);
                                  pattmp->var_list=
                                    mergevarlist(yypvt[-3].pattern->var_list,yypvt[-1].pattern->var_list);
                                  free(yypvt[-3].pattern);
                                  free(yypvt[-1].pattern);
                                  yyval.pattern=pattmp;
                                } break;
case 69:
# line 681 "lambda_parser.y"
{
                                  pattmp=(PATTERN *)malloc(sizeof(PATTERN));
                                  pattmp->term=buildnillist(app_nesting_depth);
                                  pattmp->var_list=NULL;
                                  yyval.pattern=pattmp;
                                } break;
case 70:
# line 688 "lambda_parser.y"
{
                                  yyval.pattern=yypvt[-1].pattern;
                                } break;
case 71:
# line 692 "lambda_parser.y"
{
                                  pattmp=(PATTERN *)malloc(sizeof(PATTERN));
                                  pattmp->term=
                                    buildvoidterm(app_nesting_depth);
                                  create_variable_binding(yypvt[-0].st_bucket,
                                                          NULL,
                                                          LOCAL);
                                  pattmp->var_list=
                                    makevarlist(yypvt[-0].st_bucket,pattmp->term);
                                  yyval.pattern=pattmp;
                                } break;
case 72:
# line 705 "lambda_parser.y"
{
                                  error_detected = TRUE;
                                  yyerrok;
                                  YYACCEPT;
				} break;
	}
	goto yystack;		/* reset registers in driver code */
}
