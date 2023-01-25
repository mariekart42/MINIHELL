#include "../head/minishell.h"



int main(int32_t argc, char **argv)
{
	char *line = NULL;

	// using signal function here to catch signal if eg ctr-c is used


argc++;
argv++;
	while (1)
	{
		// read content from terminal
		line = readline("MINIHELL> ");
		if (!line)
			break ;
		printf("content before history: %s\n", line);
		if (line && *line)	// if line exist and is not empty, stuff gets saved in history list
		add_history(line);
		// parse_and_execute(line);
		printf("content after history: %s\n", line);
		free(line);
		
	}
	//free(line);
}

