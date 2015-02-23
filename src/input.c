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
	if(globalReadOffset == 0) 
	{
		int numBytesRead = 0;
		char *line = readline ("opt> ");
		add_history (line);

		if(line)
		{
			numBytesRead = strlen(line);
			if(numBytesRead <= maxBytesToRead)
			{
				strncpy(buffer, line, maxBytesToRead);
				free(line);
				*result = numBytesRead;
			}
			else 
			{
				prev_line = line;
				strncpy(buffer, line, maxBytesToRead);
				globalReadOffset += maxBytesToRead;
				*result = maxBytesToRead;
			}
		}
		else
		{
			result = 0;
		}
	}
	else
	{
		/*Copy from the buffer the previous line.*/
		strncpy(buffer, prev_line+globalReadOffset, maxBytesToRead);
		globalReadOffset -= maxBytesToRead;
		*result = strlen(buffer);
		if(globalReadOffset <= 0)
		{
			globalReadOffset = 0;
			free(prev_line);
		}
	}
	return 0;
}
