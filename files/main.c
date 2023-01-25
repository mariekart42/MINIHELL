#include "../head/minishell.h"



int main(int32_t argc, char **argv)
{
	char *line = NULL;
argc++;
argv++;
	while (1)
	{
		// read content from terminal
		line = readline("MINIHELL> ");
		parse_and_execute(line);
		printf("content: %s\n", line);
		free(line);
		break ;
		
	}
	free(line);
}