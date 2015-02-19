#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "destroyer.h"
#include "garbage.h"
#include "lambda_lexan.h"
#include "lambda_parser.h"
#include "loader.h"
#include "options.h"
#include "sthandler.h"

static void usage(const char *);

unsigned int limit;
int option;
bool seetime;
bool seenode;
bool seegarb;

int
main(int argc, char **argv)
{
	int i = 0;
	char *p;

	seetime = false;
	seenode = false;
	seegarb = false;

	for(i = 1; i < argc; i++) {
		if(!strcmp(argv[i], "--gc")) {
			if(++i == argc)
				usage(argv[0]);
			else if(!strcmp(argv[i], "always"))
				option = 1;
			else if(!strcmp(argv[i], "never"))
				option = 3;
			else {
				option = 2;
				limit = strtol(argv[i+1], &p, 0);
				if(*p)
					usage(argv[0]);
			}
		}
		else if(!strcmp(argv[i], "--seetime"))
			seetime = true;
		else if(!strcmp(argv[i], "--seenode"))
			seenode = true;
		else if(!strcmp(argv[i], "--seegarb"))
			seegarb = true;
		else {
			if(!strcmp(argv[i], "--"))
				i++;
			break;
		}
	}

	init_symbol_table();
	init_destroy();
	init_garbage();
	lines = 0;
	error_detected = false;
	quit = false;
	loading_mode = false;
	lastinputterm = NULL;
	error_detected = false;

	puts("Welcome to bohm-ng " VERSION);

	for(; i < argc; i++)
		if(!compile(argv[i]))
			return 1;

	while(!quit) {
		fputs("> ", stdout);
		yyparse();
		error_detected = false;
		lines = 0;
	}
	return 0;
}

void
usage(const char *argv0)
{
	fprintf(stderr, "usage: %s [--gc always|never|<limit>] [--seetime] [--seenode] [--seegarb]\n", argv0);
	exit(2);
}
