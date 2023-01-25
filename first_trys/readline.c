#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

// libs for readline
#include <readline/readline.h>
#include <readline/history.h>

// with readline we can read a line from the terminal (similar to scanf)
// -> https://de.wikipedia.org/wiki/GNU_readline
// readline function mallocs -> needs to get freed in the end
// flag to compile readline correctly: -lreadline

// functions we can use:
// rl_clear_history

int main(int ac, char **av)
{
	// get a line from the user:
	char *line = NULL;
	printf("in here lol\n");
	line = readline("");
	if (line && *line)
		printf("content: %s\n", line);
	else
		printf("gimme input lol\n");

	free(line);
}
