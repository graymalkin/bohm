# include "stdio.h"
# define U(x) x
# define NLSTATE yyprevious=YYNEWLINE
# define BEGIN yybgin = yysvec + 1 +
# define INITIAL 0
# define YYLERR yysvec
# define YYSTATE (yyestate-yysvec-1)
# define YYOPTIM 1
# define YYLMAX BUFSIZ
# define output(c) putc(c,yyout)
# define input() (((yytchar=yysptr>yysbuf?U(*--yysptr):getc(yyin))==10?(yylineno++,yytchar):yytchar)==EOF?0:yytchar)
# define unput(c) {yytchar= (c);if(yytchar=='\n')yylineno--;*yysptr++=yytchar;}
# define yymore() (yymorfg=1)
# define ECHO fprintf(yyout, "%s",yytext)
# define REJECT { nstr = yyreject(); goto yyfussy;}
int yyleng; extern char yytext[];
int yymorfg;
extern char *yysptr, yysbuf[];
int yytchar;
FILE *yyin = {stdin}, *yyout = {stdout};
extern int yylineno;
struct yysvf { 
	struct yywork *yystoff;
	struct yysvf *yyother;
	int *yystops;};
struct yysvf *yyestate;
extern struct yysvf yysvec[], *yybgin;
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
 /***************************************************************/
 /* 1. Inclusion of header files.				*/
 /***************************************************************/
#include                <malloc.h>
#include                <string.h>
#include		"h/const.h"
#include		"h/types.h"
#include		"h/y.tab.h"
 /***************************************************************/
 /* 2. Inclusion of declarations that are being imported.	*/
 /***************************************************************/
#include		"e/sthandler.e"
#include		"e/errorhandler.e"
#include		"e/dynallhandler.e"
#include		"e/stringhandler.e"
#include		"e/lambda_parser.e"
 /***************************************************************/
 /* 3. Definitions of variables to be exported.			*/
 /***************************************************************/
int			lines;
int                     astringlen;
 /***************************************************************/
 /* 4. Regular definitions.					*/
 /***************************************************************/
 /***************************************************************/
 /* 5. Start Conditions.					*/
 /***************************************************************/
# define com 2
# define str 4
 /***************************************************************/
 /* 6. Rules.							*/
 /***************************************************************/
# define YYNEWLINE 10
yylex(){
int nstr; extern int yyprevious;
while((nstr = yylook()) >= 0)
yyfussy: switch(nstr){
case 0:
if(yywrap()) return(0); break;
case 1:
    {
                        /* comment */
                        if (loading_mode == 1) ECHO; 
                        BEGIN 0;
                   }
break;
case 2:
               {
                        /* comment beginning */
                        if (loading_mode == 1) ECHO; 
                        BEGIN com;
                   }
break;
case 3:
     {
                        if (loading_mode == 1) ECHO;
                        BEGIN 0;
                        astringlen=strlen(yytext);
                        yylval.astring=malloc(astringlen);
                        strncpy(yylval.astring,yytext,astringlen-1);
                        yylval.astring[astringlen-1]=0;
                        return ASTRING;
                    }
break;
case 4:
                {
                        if (loading_mode == 1) ECHO;
                        BEGIN str;
                   }
break;
case 5:
   {
			/* sequence of blanks */
                        if (loading_mode == 1) ECHO; 
		   }
break;
case 6:
	   {
			/* tab */
                        if (loading_mode == 1) ECHO; 
		   }
break;
case 7:
	   {
			/* newline */
                        if (loading_mode == 1) ECHO; 
                        lines++;
		   }
break;
case 8:
	   {
			/* identifier */
                        if (loading_mode == 1) ECHO; 
			search_bucket(&(yylval.st_bucket),
				      yytext);
			return(yylval.st_bucket->token);
		   }
break;
case 9:
	   {
			/* integer */
                        if (loading_mode == 1) ECHO; 
			yylval.num_const = to_nat_s(yytext);
			if (yylval.num_const == NUMOUTOFRANGE)
				signal_error(NUMOVERFLOW);
			return(NUMCONST);
		   }
break;
case 10:
  {
			/* one-character token */
                        if (loading_mode == 1) ECHO; 
			return(yytext[0]);
		   }
break;
case 11:
	   {
			/* end of expression  */
                        if (loading_mode == 1) ECHO; 
			return(EXPRDELIM);
		}
break;
case 12:
	   {
			/*  */
                        if (loading_mode == 1) ECHO; 
			return(EQUAL);
		}
break;
case 13:
	   {
			/*  */
                        if (loading_mode == 1) ECHO; 
			return(LEQUAL);
		}
break;
case 14:
	   {
			/*  */
                        if (loading_mode == 1) ECHO; 
			return(MEQUAL);
		}
break;
case 15:
	   {
			/*  */
                        if (loading_mode == 1) ECHO; 
			return(NOTEQUAL);
		}
break;
case 16:
{
			/* detection of an illegal character */
                        if (loading_mode == 1) ECHO; 
			signal_error(ILLEGALCHAR);
		}
break;
case -1:
break;
default:
fprintf(yyout,"bad switch yylook %d",nstr);
} return(0); }
/* end of yylex */

 /***************************************************************/
 /* 6. Auxiliary functions.					*/
 /***************************************************************/

HIDDEN
yywrap()
{
	return(NOMOREINPUT);
}












int yyvstop[] = {
0,

16,
0,

6,
0,

7,
0,

5,
0,

4,
16,
0,

10,
0,

9,
0,

10,
0,

10,
0,

10,
0,

8,
0,

2,
16,
0,

10,
16,
0,

16,
0,

6,
0,

7,
0,

5,
0,

4,
16,
0,

10,
0,

9,
0,

10,
0,

10,
0,

10,
0,

8,
0,

2,
16,
0,

10,
16,
0,

1,
16,
0,

16,
0,

6,
0,

7,
0,

5,
0,

3,
4,
16,
0,

10,
0,

9,
0,

10,
0,

10,
0,

10,
0,

8,
0,

2,
16,
0,

10,
16,
0,

11,
0,

13,
0,

15,
0,

12,
0,

14,
0,

1,
0,

11,
0,

13,
0,

15,
0,

12,
0,

14,
0,

3,
0,

11,
0,

13,
0,

15,
0,

12,
0,

14,
0,
0};
# define YYTYPE char
struct yywork { YYTYPE verify, advance; } yycrank[] = {
0,0,	0,0,	1,7,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	1,8,	1,9,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	2,9,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	1,10,	4,23,	1,11,	
1,12,	10,10,	24,24,	40,40,	
2,10,	0,0,	3,21,	6,39,	
0,0,	0,0,	0,0,	0,0,	
1,0,	1,13,	3,22,	3,23,	
28,28,	44,44,	0,0,	2,0,	
4,24,	0,0,	0,0,	0,0,	
1,14,	1,15,	1,16,	1,17,	
14,52,	6,40,	1,18,	2,14,	
2,15,	2,16,	2,17,	4,27,	
16,55,	3,24,	17,56,	3,25,	
3,26,	15,53,	15,54,	29,58,	
6,43,	31,61,	5,37,	4,29,	
4,30,	4,31,	4,32,	32,62,	
3,27,	3,28,	5,38,	5,39,	
6,45,	6,46,	6,47,	6,48,	
30,59,	30,60,	45,64,	47,67,	
3,29,	3,30,	3,31,	3,32,	
33,33,	33,33,	3,33,	46,65,	
46,66,	48,68,	0,0,	0,0,	
0,0,	5,40,	0,0,	5,41,	
5,42,	49,49,	49,49,	0,0,	
0,0,	0,0,	33,33,	0,0,	
1,19,	1,20,	1,7,	0,0,	
5,43,	5,44,	0,0,	2,19,	
0,0,	0,0,	0,0,	49,49,	
0,0,	0,0,	0,0,	0,0,	
5,45,	5,46,	5,47,	5,48,	
0,0,	0,0,	5,49,	4,34,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
6,50,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
3,34,	3,35,	3,36,	13,13,	
13,13,	13,13,	13,13,	13,13,	
13,13,	13,13,	13,13,	13,13,	
13,13,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
0,0,	0,0,	0,0,	0,0,	
5,50,	5,51,	5,37,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	0,0,	0,0,	0,0,	
0,0,	18,18,	0,0,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	18,18,	18,18,	18,18,	
18,18,	21,27,	0,0,	37,43,	
0,0,	0,0,	0,0,	0,0,	
0,0,	21,27,	0,0,	37,43,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	21,27,	21,27,	
37,63,	37,43,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
21,27,	0,0,	37,43,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	21,27,	0,0,	37,43,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
0,0,	0,0,	0,0,	0,0,	
21,27,	21,57,	37,43,	37,43,	
0,0};
struct yysvf yysvec[] = {
0,	0,	0,
yycrank+-1,	0,		0,	
yycrank+-8,	yysvec+1,	0,	
yycrank+-41,	0,		0,	
yycrank+-24,	yysvec+3,	0,	
yycrank+-81,	0,		0,	
yycrank+-33,	yysvec+5,	0,	
yycrank+0,	0,		yyvstop+1,
yycrank+0,	0,		yyvstop+3,
yycrank+0,	0,		yyvstop+5,
yycrank+5,	0,		yyvstop+7,
yycrank+0,	0,		yyvstop+9,
yycrank+0,	0,		yyvstop+12,
yycrank+119,	0,		yyvstop+14,
yycrank+5,	0,		0,	
yycrank+16,	0,		yyvstop+16,
yycrank+11,	0,		yyvstop+18,
yycrank+13,	0,		yyvstop+20,
yycrank+142,	0,		yyvstop+22,
yycrank+0,	0,		yyvstop+24,
yycrank+0,	0,		yyvstop+27,
yycrank+-264,	0,		yyvstop+30,
yycrank+0,	yysvec+21,	yyvstop+32,
yycrank+0,	yysvec+21,	yyvstop+34,
yycrank+-6,	yysvec+21,	yyvstop+36,
yycrank+0,	yysvec+21,	yyvstop+38,
yycrank+0,	yysvec+21,	yyvstop+41,
yycrank+0,	yysvec+21,	0,	
yycrank+-4,	yysvec+21,	yyvstop+43,
yycrank+-20,	yysvec+21,	0,	
yycrank+-35,	yysvec+21,	yyvstop+45,
yycrank+-20,	yysvec+21,	yyvstop+47,
yycrank+-26,	yysvec+21,	yyvstop+49,
yycrank+-57,	yysvec+21,	yyvstop+51,
yycrank+0,	yysvec+21,	yyvstop+53,
yycrank+0,	yysvec+21,	yyvstop+56,
yycrank+0,	0,		yyvstop+59,
yycrank+-266,	0,		yyvstop+62,
yycrank+0,	yysvec+37,	yyvstop+64,
yycrank+0,	yysvec+37,	yyvstop+66,
yycrank+-7,	yysvec+37,	yyvstop+68,
yycrank+0,	0,		yyvstop+70,
yycrank+0,	yysvec+37,	yyvstop+74,
yycrank+0,	yysvec+37,	0,	
yycrank+-5,	yysvec+37,	yyvstop+76,
yycrank+-39,	yysvec+37,	0,	
yycrank+-46,	yysvec+37,	yyvstop+78,
yycrank+-38,	yysvec+37,	yyvstop+80,
yycrank+-48,	yysvec+37,	yyvstop+82,
yycrank+-70,	yysvec+37,	yyvstop+84,
yycrank+0,	yysvec+37,	yyvstop+86,
yycrank+0,	yysvec+37,	yyvstop+89,
yycrank+0,	0,		yyvstop+92,
yycrank+0,	0,		yyvstop+94,
yycrank+0,	0,		yyvstop+96,
yycrank+0,	0,		yyvstop+98,
yycrank+0,	0,		yyvstop+100,
yycrank+0,	0,		yyvstop+102,
yycrank+0,	yysvec+21,	yyvstop+104,
yycrank+0,	yysvec+21,	yyvstop+106,
yycrank+0,	yysvec+21,	yyvstop+108,
yycrank+0,	yysvec+21,	yyvstop+110,
yycrank+0,	yysvec+21,	yyvstop+112,
yycrank+0,	0,		yyvstop+114,
yycrank+0,	yysvec+37,	yyvstop+116,
yycrank+0,	yysvec+37,	yyvstop+118,
yycrank+0,	yysvec+37,	yyvstop+120,
yycrank+0,	yysvec+37,	yyvstop+122,
yycrank+0,	yysvec+37,	yyvstop+124,
0,	0,	0};
struct yywork *yytop = yycrank+391;
struct yysvf *yybgin = yysvec+1;
char yymatch[] = {
00  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,011 ,011 ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
01  ,01  ,01  ,01  ,01  ,01  ,01  ,01  ,
011 ,01  ,'"' ,'#' ,01  ,01  ,01  ,01  ,
'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,'#' ,011 ,
'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,'0' ,
'0' ,'0' ,01  ,011 ,'#' ,'#' ,'#' ,01  ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'#' ,'#' ,'#' ,01  ,'A' ,
01  ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,'A' ,
'A' ,'A' ,'A' ,01  ,'|' ,'}' ,01  ,01  ,
0};
char yyextra[] = {
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0,0,0,0,0,0,0,0,
0};
#ifndef lint
static	char ncform_sccsid[] = "@(#)ncform 1.6 88/02/08 SMI"; /* from S5R2 1.2 */
#endif

int yylineno =1;
# define YYU(x) x
# define NLSTATE yyprevious=YYNEWLINE
char yytext[YYLMAX];
struct yysvf *yylstate [YYLMAX], **yylsp, **yyolsp;
char yysbuf[YYLMAX];
char *yysptr = yysbuf;
int *yyfnd;
extern struct yysvf *yyestate;
int yyprevious = YYNEWLINE;
yylook(){
	register struct yysvf *yystate, **lsp;
	register struct yywork *yyt;
	struct yysvf *yyz;
	int yych, yyfirst;
	struct yywork *yyr;
# ifdef LEXDEBUG
	int debug;
# endif
	char *yylastch;
	/* start off machines */
# ifdef LEXDEBUG
	debug = 0;
# endif
	yyfirst=1;
	if (!yymorfg)
		yylastch = yytext;
	else {
		yymorfg=0;
		yylastch = yytext+yyleng;
		}
	for(;;){
		lsp = yylstate;
		yyestate = yystate = yybgin;
		if (yyprevious==YYNEWLINE) yystate++;
		for (;;){
# ifdef LEXDEBUG
			if(debug)fprintf(yyout,"state %d\n",yystate-yysvec-1);
# endif
			yyt = yystate->yystoff;
			if(yyt == yycrank && !yyfirst){  /* may not be any transitions */
				yyz = yystate->yyother;
				if(yyz == 0)break;
				if(yyz->yystoff == yycrank)break;
				}
			*yylastch++ = yych = input();
			yyfirst=0;
		tryagain:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"char ");
				allprint(yych);
				putchar('\n');
				}
# endif
			yyr = yyt;
			if ( (int)yyt > (int)yycrank){
				yyt = yyr + yych;
				if (yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
# ifdef YYOPTIM
			else if((int)yyt < (int)yycrank) {		/* r < yycrank */
				yyt = yyr = yycrank+(yycrank-yyt);
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"compressed state\n");
# endif
				yyt = yyt + yych;
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transitions */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				yyt = yyr + YYU(yymatch[yych]);
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"try fall back character ");
					allprint(YYU(yymatch[yych]));
					putchar('\n');
					}
# endif
				if(yyt <= yytop && yyt->verify+yysvec == yystate){
					if(yyt->advance+yysvec == YYLERR)	/* error transition */
						{unput(*--yylastch);break;}
					*lsp++ = yystate = yyt->advance+yysvec;
					goto contin;
					}
				}
			if ((yystate = yystate->yyother) && (yyt= yystate->yystoff) != yycrank){
# ifdef LEXDEBUG
				if(debug)fprintf(yyout,"fall back to state %d\n",yystate-yysvec-1);
# endif
				goto tryagain;
				}
# endif
			else
				{unput(*--yylastch);break;}
		contin:
# ifdef LEXDEBUG
			if(debug){
				fprintf(yyout,"state %d char ",yystate-yysvec-1);
				allprint(yych);
				putchar('\n');
				}
# endif
			;
			}
# ifdef LEXDEBUG
		if(debug){
			fprintf(yyout,"stopped at %d with ",*(lsp-1)-yysvec-1);
			allprint(yych);
			putchar('\n');
			}
# endif
		while (lsp-- > yylstate){
			*yylastch-- = 0;
			if (*lsp != 0 && (yyfnd= (*lsp)->yystops) && *yyfnd > 0){
				yyolsp = lsp;
				if(yyextra[*yyfnd]){		/* must backup */
					while(yyback((*lsp)->yystops,-*yyfnd) != 1 && lsp > yylstate){
						lsp--;
						unput(*yylastch--);
						}
					}
				yyprevious = YYU(*yylastch);
				yylsp = lsp;
				yyleng = yylastch-yytext+1;
				yytext[yyleng] = 0;
# ifdef LEXDEBUG
				if(debug){
					fprintf(yyout,"\nmatch ");
					sprint(yytext);
					fprintf(yyout," action %d\n",*yyfnd);
					}
# endif
				return(*yyfnd++);
				}
			unput(*yylastch);
			}
		if (yytext[0] == 0  /* && feof(yyin) */)
			{
			yysptr=yysbuf;
			return(0);
			}
		yyprevious = yytext[0] = input();
		if (yyprevious>0)
			output(yyprevious);
		yylastch=yytext;
# ifdef LEXDEBUG
		if(debug)putchar('\n');
# endif
		}
	}
yyback(p, m)
	int *p;
{
if (p==0) return(0);
while (*p)
	{
	if (*p++ == m)
		return(1);
	}
return(0);
}
	/* the following are only used in the lex library */
yyinput(){
	return(input());
	}
yyoutput(c)
  int c; {
	output(c);
	}
yyunput(c)
   int c; {
	unput(c);
	}
