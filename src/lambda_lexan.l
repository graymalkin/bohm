 /***************************************************************/
 /*		          LAMBDA_LEXAN   			*/
 /***************************************************************/
 /* This module is the lex specification of the lexical         */
 /* analyzer.			                                */
 /* It is able to recognize the following tokens:		*/
 /* - ID: a sequence of letters and digits beginning with a     */
 /*	  letter, and possibly containing one or more           */
 /*       occurrences of "/".                                   */
 /*       The pointer to the symbol table bucket 	        */
 /*       associated with the identifier is returned in yylval; */
 /*	  keywords are treated as special identifiers           */
 /*	  (to limit the automaton space complexity),	        */
 /*	  each of which has a corresponding token;		*/
 /*       (see also the symbol table handler)                   */
 /* - NUMCONST: (unused) a sequence of digits; its numerical    */
 /*		value is returned in yylval;			*/
 /* - CHARCONST: a character other than single quote sorrounded */
 /*		 by single quotes; the character itself is	*/
 /*		 returned in yylval;				*/
 /* - STRINGCONST: a sequence of characters, all lying in a	*/
 /*		   line and different from single quote,	*/
 /*		   sorrounded by single quotes; the pointer to	*/
 /*		   the first character of the string is		*/
 /*		   returned in yylval;				*/
 /* - EXPRDELIM: the symbol ';;'				*/
 /* - One character tokens: '=', '(' ')' '\' and '#'. 		*/
 /*   The character itself is passed to the parser.             */
 /*                                                             */
 /* Comments must be enclosed in "{" and "}".                   */
 /***************************************************************/

%option noinput
%option nounput

 /***************************************************************/
 /* 1. Inclusion of header files.				*/
 /***************************************************************/

%{
#include <stdlib.h>
#include <string.h>
#include "const.h"
#include "types.h"
#include "y.tab.h"
%}


 /***************************************************************/
 /* 2. Inclusion of declarations that are being imported.	*/
 /***************************************************************/

%{
#include "dynallhandler.h"
#include "errorhandler.h"
#include "lambda_parser.h"
#include "sthandler.h"
#include "stringhandler.h"
#include "input.h"
%}

 /***************************************************************/
 /* 3. Definitions of variables to be exported.			*/
 /***************************************************************/

%{
int lines;
int astringlen;
%}

%{
#undef YY_INPUT
#define YY_INPUT(b,r,s) readInputForLexer(b,&(r),s)
%}

 /***************************************************************/
 /* 4. Regular definitions.					*/
 /***************************************************************/

letter			[A-Za-z\_]
digit			[0-9]
illegal_char		[^A-Za-z0-9 \t\n\/;.=()#\\+<>\-\*\[\],\_]
id			{letter}(\/|{letter}|{digit})*
num			{digit}+
blanks			(" ")+
one_char_token          [=()\\.#+<>\-\*\[\],\|]
comment                 [^\}]*\}
string                  [^\"]*\"

 /***************************************************************/
 /* 5. Start Conditions.					*/
 /***************************************************************/

%start com
%start str              

 /***************************************************************/
 /* 6. Rules.							*/
 /***************************************************************/

%%

<com>{comment}     {
                        /* comment */
                        /*if (loading_mode == 1) ECHO; */
                        BEGIN 0;
                   }

"{"                {
                        /* comment beginning */
                        /*if (loading_mode == 1) ECHO; */
                        BEGIN com;
                   }

<str>{string}      {
                        /*if (loading_mode == 1) ECHO;*/
                        BEGIN 0;
                        astringlen=strlen(yytext);
                        yylval.astring=malloc(astringlen);
                        strncpy(yylval.astring,yytext,astringlen-1);
                        yylval.astring[astringlen-1]=0;
                        return ASTRING;
                    }
\"                 {
                        /*if (loading_mode == 1) ECHO;*/
                        BEGIN str;
                   }

{blanks}	   {
			/* sequence of blanks */
                        /*if (loading_mode == 1) ECHO; */
		   }

\t		   {
			/* tab */
                        /*if (loading_mode == 1) ECHO; */
		   }

\n		   {
			/* newline */
                        /*if (loading_mode == 1) ECHO; */
                        lines++;
		   }

{id}		   {
			/* identifier */
                        /*if (loading_mode == 1) ECHO; */
			search_bucket(&(yylval.st_bucket),
				      yytext);
			return(yylval.st_bucket->token);
		   }

{num}		   {
			/* integer */
                        /*if (loading_mode == 1) ECHO; */
			yylval.num_const = to_nat_s(yytext);
			if (yylval.num_const == NUMOUTOFRANGE)
				signal_error(NUMOVERFLOW);
			return(NUMCONST);
		   }

{one_char_token}   {
			/* one-character token */
                        /*if (loading_mode == 1) ECHO; */
			return(yytext[0]);
		   }


";;"		   {
			/* end of expression  */
                        /*if (loading_mode == 1) ECHO; */
			return(EXPRDELIM);
		}

"=="		   {
			/*  */
                        /*if (loading_mode == 1) ECHO; */
			return(EQUAL);
		}

"<="		   {
			/*  */
                        /*if (loading_mode == 1) ECHO; */
			return(LEQUAL);
		}

">="		   {
			/*  */
                        /*if (loading_mode == 1) ECHO; */
			return(MEQUAL);
		}
"<>"		   {
			/*  */
                        /*if (loading_mode == 1) ECHO; */
			return(NOTEQUAL);
		}


{illegal_char}	{
			/* detection of an illegal character */
                        /*if (loading_mode == 1) ECHO; */
			signal_error(ILLEGALCHAR);
		}


%%

 /***************************************************************/
 /* 6. Auxiliary functions.					*/
 /***************************************************************/

int
yywrap(void)
{
	return(NOMOREINPUT);
}












