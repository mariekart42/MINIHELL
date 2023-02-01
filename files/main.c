#include "../head/minishell.h"

// void parser(t_hold *hold)
// {

// }

int main(int32_t argc, char **argv)
{
	t_hold	*hold;

	hold = (t_hold*)malloc(sizeof(t_hold));
	if (!hold)
		return (1);

	// using signal function here to catch signal if eg ctr-c is used
argc++;
argv++;
	while (1)
	{
		// read content from terminal
		hold->line = readline("MINIHELL> ");
		if (!hold->line)
			break ;

		lexer(hold);
		// parser(hold);
		print_list(hold->lexed_list, "yee");
		
		// if (line && *line)	// if line exist and is not empty, stuff gets saved in history list
		// 	add_history(line);

		freeList(hold->lexed_list);
		hold->lexed_list = NULL;
		free(hold->line);
		// break;
		
	}
	//free(line);
}

// wfidh""qiuhdf>efd<      ->>> gives not correct output!


// how do i exit from failed command but not out of whole minishell

// add $? as single node


// (redir function throw error if redir signs at the very end --> do it in parser)