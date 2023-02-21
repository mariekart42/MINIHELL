#include "../head/minishell.h"

bool builtin_parser(char *node)
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

/* function appends specific macro to each node of 'lex_struct'
 * 	Macros: QUOTES, PIPE, (SINGLE-/DOUBLE) REDIRECTION, BUILTIN */
void recognize_type(t_hold *hold)
{
	t_lexing *tmp;
	// char *stupid = ft_substr("\"", 0, 2);
	// printf(RED"stupid: %s\n"RESET, stupid);
	// exit(0);
	// printf("check in rec\n");
// printf("list: %s\n", hold->lex_struct->item);
	tmp = hold->lex_struct;
	while (tmp != NULL)
	{
		if (builtin_parser(tmp->item) == true)
		{
				// printf("builtin: %s\n", tmp->item);
			tmp->macro = BUILTIN;
		}
		else if (ft_strncmp(tmp->item, "|", 1) == 0)
			tmp->macro = PIPE;
		else if (ft_strncmp(tmp->item, "'", 1) == 0)
			tmp->macro = SING_QUOTE;
		else if (ft_strncmp(tmp->item, "\"", 1) == 0)
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

/* function checks and returns outfile 
 * opens/creates file if it not exists
 * check later for permission issues if the file already exists(how lol?) */
int32_t check_outfile(t_hold *hold, t_lexing *file_node, int32_t type)
{
	int32_t file_id;

	// get rid of double or single quotes
	if (file_node->macro == SING_QUOTE || file_node->macro == DOUBL_QUOTE)
		file_node->item = ft_substr(file_node->item, 1, ft_strlen(file_node->item)-2);

// not 100% sure about opening macros (in both open calls)
	if (type == SING_CLOSE_REDIR)
	{
		// printf("single redir\n");
		file_id = open(file_node->item, O_CREAT | O_WRONLY | O_TRUNC , 0644);
	}
	else
	{
		// printf("double redir\n");
		file_id = open(file_node->item, O_CREAT, 0644);
	}

	if (file_id < 0)
		exit_status(hold, "Error!: unable to open outfile (in check_outfile func)\n", 69);
	return (file_id);
	
}

/* function creates 'parsed list' with the content of struct 'parsed_chunk'
 * the content of one chunk is always a pipegroup, with in/outfile, arguments and commandpath */
void create_parsed_list(t_hold *hold)
{
	t_lexing *tmp_l;
	t_parsed_chunk *tmp_p;
	char *args;
	args = malloc(sizeof(char));
	args = "\0";

	tmp_l = hold->lex_struct;
	tmp_p = hold->parsed_list;
	while (tmp_l != NULL)
	{
		if (tmp_p == NULL)
			tmp_p = add_node_pars(hold);
		else
			(last_node_pars(tmp_p))->next = add_node_pars(hold);
		if (tmp_l->macro != PIPE)
		{
			if (tmp_l->macro == BUILTIN)
			{
				printf("HANDLE BUILTIN IN PARSER! -> add later\n");
			}
			else if (tmp_l->macro == SING_CLOSE_REDIR || tmp_l->macro == DOUBL_CLOSE_REDIR)
			{
				//redirect outfile
				tmp_p->outfile = check_outfile(hold, tmp_l->next, tmp_l->macro);
				printf("OUTFILE: %s\n", tmp_l->next->item);
				tmp_l = tmp_l->next;
			}
			else if (tmp_l->macro == DOUBL_OPEN_REDIR)	// herdoc function <<
			{
				printf(MAG"DOUBL_CLOSE_REDIR -> add later\n"RESET);
			}
			else if (tmp_l->macro == SING_OPEN_REDIR) // add later
			{
				printf(MAG"SING_CLOSE_REDIR -> add later\n"RESET);
			}
			else
			{


				// char *tmp;
				args = ft_strjoin(args, " ");
				// if (args != NULL)
				// 	free(args);
				// args = NULL;
				// args = ft_strjoin(args, " ");
				args = ft_strjoin(args, tmp_l->item);
				// free(tmp);
				// tmp = NULL;
				// printf(MAG"command: %s\n"RESET, tmp_l->item);
				printf("ARGS: %s\n", args);

			}
				tmp_l = tmp_l->next;
		}
		else
			tmp_p = tmp_p->next;
	}
	printf("args in struct:\n");
	if (hold->parsed_list->outfile == 0)
		printf("args is nULL\n");
	// char **tmp = NULL;
	// tmp = ft_split(args, ' ');
	// printf("tmp: %s\n", tmp[0]);
	// printf("tmp: %s\n", tmp[1]);
	// printf("tmp: %s\n", tmp[2]);
	// // hold->parsed_list->args = ft_s
	// hold->parsed_list->args = ft_split(args, ' ');
	// printf("%s\n", hold->parsed_list->args[0]);
	// printf("%s\n", hold->parsed_list->args[1]);
	// printf("%s\n", hold->parsed_list->args[2]);
	printf("\npars done: EXIT\n\n");
	exit(0);
}

void parser(t_hold *hold)
{
    if (hold->exit_code != 0)
        return ;
	recognize_type(hold);



	create_parsed_list(hold);

}