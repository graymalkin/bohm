#include <stdio.h>
#include "const.h"
#include "lambda_parser.h"
#include "types.h"

bool
compile(char *file)
{
	FILE *fp;

	if(!(fp = fopen(file, "r"))) {
		fprintf(stderr, "Error loading ");
		perror(file);
		return false;
	}

	yyrestart(fp);
	loading_mode = true;

	while(!quit && !error_detected)
		yyparse();
	if(error_detected) {
		fprintf(stderr, "Error loading %s: Compilation error\n", file);
		error_detected = false;
		return false;
	}

	fprintf(stderr, "Loaded %s\n", file);

	quit = false;
	loading_mode = false;
	yyrestart(stdin);
	fclose(fp);

	return true;
}
