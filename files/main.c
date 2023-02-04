#include "../head/minishell.h"

bool builtin(char *node)
{
	if (ft_strncmp(node, "echo", 4) == 0)
		return (true);
	else if (ft_strncmp(node, "pwd", 3) == 0)
		return (true);
	else if (ft_strncmp(node, "unset", 5) == 0)
		return (true);
	else if (ft_strncmp(node, "env", 3) == 0)
		return (true);
	else if (ft_strncmp(node, "export", 6) == 0)
		return (true);
	else if (ft_strncmp(node, "cd", 2) == 0)
		return (true);
	else if (ft_strncmp(node, "exit", 4) == 0)
		return (true);
	else
		return (false);
}

/* function appends specific macro to each node of 'lexed_list'
 * 	Macros: QUOTES, PIPE, (SINGLE-/DOUBLE) REDIRECTION */
void recognize_type(t_hold *hold)
{
	t_lexing *tmp;

	tmp = hold->lexed_list;
	while (tmp != NULL)
	{
		if (builtin(tmp->item) == true)
			tmp->macro = BUILTIN;
		else if (ft_strncmp(tmp->item, "|", 1) == 0)
			tmp->macro = PIPE;
		else if (ft_strncmp(tmp->item, "'", 1) == 0)
			tmp->macro = SING_QUOTE;
		else if (ft_strncmp(tmp->item, """", 1) == 0)
			tmp->macro = DOUBL_QUOTE;
		else if (ft_strncmp(tmp->item, "<<", 2) == 0)
			tmp->macro = DOUBL_OPEN_REDIR;
		else if (ft_strncmp(tmp->item, ">>", 2) == 0)
			tmp->macro = DOUBL_CLOSE_REDIR;
		else if (ft_strncmp(tmp->item, "<", 1) == 0)
			tmp->macro = SING_OPEN_REDIR;
		else if (ft_strncmp(tmp->item, ">", 1) == 0)
			tmp->macro = SING_CLOSE_REDIR;
		else
			tmp->macro = WORD;
		tmp = tmp->next;
	}
}

void parser(t_hold *hold)
{
	recognize_type(hold);
}

int main(int32_t argc, char **argv, char **env)
{
	t_hold	*hold = NULL;
	(void)argc++;
	(void)argv++;
	(void)env++;

	hold = (t_hold*)malloc(sizeof(t_hold));
	if (!hold)
		return (1);
	hold->lexed_list = (t_lexing*)malloc(sizeof(t_lexing));
	if (!hold->lexed_list)
		return (1);
	hold->lexed_list = NULL;
	// using signal function here to catch signal if eg ctr-c is used
	while (1)
	{
		hold->line = readline("MINIHELL> ");
		if (!hold->line)
			break ;

		lexer(hold);
		parser(hold);
		print_macro_list(hold->lexed_list);
		
		// if (line && *line)	// if line exist and is not empty, stuff gets saved in history list
		// 	add_history(line);

		freeList(hold->lexed_list);
		hold->lexed_list = NULL;
		free(hold->line);

	}
	//free(line);
}


//GENERAL:
// - change from exiting on errors to return to main loop
//		-> set flag in struct, do nothing in lexer, parser, executer and return to main loop

// - add history stuff


//LEXER:


//PARSER:
// !do env/export shit in parser first

// - redir function throw error if redir signs at the very end --> do it in parser


//EXECUTER: