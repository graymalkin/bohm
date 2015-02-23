#include <stdio.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>



#include "input.h"

static int globalReadOffset = 0;

int
readInputForLexer(char *buffer, int *numBytesRead, int maxBytesToRead)
{
	char *line = readline ("bohm> ");
	add_history (line);

	numBytesRead = strlen(line);
	strcpy(buffer, line);

    return 0;
}
