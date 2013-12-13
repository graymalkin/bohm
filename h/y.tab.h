
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
extern YYSTYPE yylval;
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
