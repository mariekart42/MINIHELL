#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// libs for readline
#include <readline/readline.h>
#include <readline/history.h>

// void parser(char *input)
// {

// }
// void executer(char *input)
// {

// }

int main()
{
	char *line = NULL;


	line = readline("HELL> ");
	if (line && *line)
	{
// here function that parses the input
		printf("content: %s\n", line);

		int return_val;
		parser(line);
		// bash: if command was executable, returns 0
		// bash: if not it returns 127
		// can parser already detect not valid args or are we doing this in executer?

		return_val = executer(line);
		// execute returns in case of error, error value (-> 127 (more error values??))
		// in case of successful execution returns 0
		return (22);
	}
	else
	{
		printf("gimme input lol\n");
		// bash: returns 0 if no input
		return (0);
	}
	free(line);
}