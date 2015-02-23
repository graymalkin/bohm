#include <stdio.h>
#include <string.h>
#include <readline/history.h>
#include <readline/readline.h>



#include "input.h"

static int globalReadOffset = 0;

int
readInputForLexer(char *buffer, int *result, int maxBytesToRead)
{
	if(globalReadOffset == 0) {
		int numBytesRead = 0;
		char *line = readline ("bohm> ");
		add_history (line);

		numBytesRead = strlen(line);
		if(numBytesRead < maxBytesToRead)
			strcpy(buffer, line);
		*result = 1;

	}
	return 0;
}
