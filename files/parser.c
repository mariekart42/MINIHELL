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

/* function checks and returns outfile 
 * opens/creates file if it not exists
 * check later for permission issues if the file already exists(how lol?) */
int32_t check_outfile(t_hold *hold, char *file_name, int32_t type)
{
	int32_t file_id;
printf("file_name: %s\n", file_name);
	// get rid of double or single quotes
	if (type == SING_QUOTE || type == DOUBL_QUOTE)
		file_name = ft_substr(file_name, 1, ft_strlen(file_name)-2); // should substract quote at the beginning and at the end

	if (type == SING_CLOSE_REDIR)
	{
		printf("single redir\n");
		file_id = open(file_name, O_CREAT | O_WRONLY | O_TRUNC , 0644);
	}
	else
	{
		printf("double redir\n");
		file_id = open(file_name, O_CREAT, 0644);
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
	// t_parsed_chunk *pars = hold->parsed_list; 

	tmp_l = hold->lex_struct;
	tmp_p = hold->parsed_list;
	while (tmp_l != NULL)
	{
		if (tmp_p == NULL)
			tmp_p = add_node_pars(hold);
		else
			(last_node_pars(tmp_p))->next = add_node_pars(hold);
		if (tmp_l->macro == PIPE)
		{
			tmp_p = tmp_p->next;
			tmp_l = tmp_l->next;
		}
		else if (tmp_l->macro == SING_CLOSE_REDIR || tmp_l->macro == DOUBL_CLOSE_REDIR)
		{
			//redirect outfile
			tmp_p->outfile = check_outfile(hold, tmp_l->next->item, tmp_l->macro);
			tmp_l = tmp_l->next;
			tmp_l = tmp_l->next;
		}
		else if (tmp_l->macro == DOUBL_OPEN_REDIR)	// herdoc function <<
		{
			printf(MAG"DOUBL_CLOSE_REDIR -> add later\n"RESET);
			tmp_l = tmp_l->next;
		}
		else if (tmp_l->macro == SING_OPEN_REDIR) // add later
		{
			printf(MAG"SING_CLOSE_REDIR -> add later\n"RESET);
			tmp_l = tmp_l->next;
		}
		else
		{
			printf(MAG"should be a command: %s\n"RESET, tmp_l->item);
			tmp_l = tmp_l->next;
		}
	}
	printf("pars done: EXIT\n\n");
	// exit(0);
}

void parser(t_hold *hold)
{
    if (hold->exit_code != 0)
        return ;
	recognize_type(hold);

	create_parsed_list(hold);

}