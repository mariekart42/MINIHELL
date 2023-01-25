#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// libs for readline
#include <readline/readline.h>
#include <readline/history.h>

int main()
{
	char *line = NULL;


	line = readline("HELL> ");
	if (!line)
		printf("contr D\n");
	printf("first letter: %c\n", line[0]);
	if (line[0] == 97)
	{
		printf("pressed letter a\n");
	}
	else
		printf("yeah no nothing\n");

	free(line);
}