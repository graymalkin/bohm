#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#include <readline/history.h>
#include <readline/readline.h>



#include "input.h"

static int globalReadOffset = 0;
char * prev_line;

int
readInputForLexer(char *buffer, int *result, int maxBytesToRead)
{
	if(globalReadOffset == 0) {
		int numBytesRead = 0;
		char *line = readline ("bohm> ");
		add_history (line);

		numBytesRead = strlen(line);
		if(numBytesRead < maxBytesToRead)
		{
			strncpy(buffer, line, maxBytesToRead);
			free(line);
		}
		else 
		{
			prev_line = line;
			strncpy(buffer, line, maxBytesToRead);
			globalReadOffset += maxBytesToRead;
		}
		*result = numBytesRead;
	}
	else
	{
		/*Copy from the buffer the previous line.*/
		strncpy(buffer+globalReadOffset, prev_line, maxBytesToRead);
		globalReadOffset -= maxBytesToRead;
		if(globalReadOffset <= 0)
			globalReadOffset = 0;
	}
	return 0;
}
