#include "minishell.h"

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

	tmp = hold->lex_struct;
	while (tmp != NULL)
	{
		if (builtin_parser(tmp->item) == true)
			tmp->macro = BUILTIN;
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

/* function checks and returns outfile on success
 * opens/creates file if it not exists
 * check later for permission issues if the file already exists(how lol?) */
int32_t check_outfile(t_hold *hold, t_lexing *file_node, int32_t type)
{
	int32_t file_id;

	// // get rid of double or single quotes
	// if (file_node->macro == SING_QUOTE || file_node->macro == DOUBL_QUOTE)
	// 	file_node->item = ft_substr(file_node->item, 1, ft_strlen(file_node->item)-2);

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

/* function checks and returns infile on success
 * input file must exist and be readable by the user running the command
 * file_node is the current node in parsed_list	*/
int32_t check_infile(t_hold *hold, t_lexing *file_node)
{
	int32_t file_id;

	// // get rid of double or single quotes
	// if (file_node->macro == SING_QUOTE || file_node->macro == DOUBL_QUOTE)
	// 	file_node->item = ft_substr(file_node->item, 1, ft_strlen(file_node->item)-2);

// not 100% sure about opening macros
	file_id = open(file_node->item, O_RDONLY);
	if (file_id < 0)
		exit_status(hold, "Error!: unable to open infile (in check_infile func)\n", 69);
	return (file_id);
}

/* function counts and returns amount of pipegroups in 'lexed_list' */
int32_t count_pipegroups(t_lexing *lex)
{
	t_lexing *tmp;
	int32_t	pipegroup;

	pipegroup = 1;
	tmp = lex;
	while (tmp != NULL)
	{
		if (tmp->macro == PIPE)
			pipegroup++;
		tmp = tmp->next;
	}
	return (pipegroup);
}

/* function appends command from 'parsed_list' at the end of
 * each path of $PATH and checks for access
 * in case of access, function returns path
 * otherwise returns NULL		*/
char *get_cmdpath(char *curr_cmd)
{
	char **env_path;
	char *valid_path;
	int32_t i = 0;

	env_path = ft_split(getenv("PATH"), ':');
	while (env_path[i] != NULL)
	{
		env_path[i] = ft_strjoin(env_path[i], "/");
		valid_path = ft_strjoin(env_path[i], curr_cmd);
		if (access(valid_path, F_OK | X_OK) == 0)
			break ;
		free(valid_path);
		i++;
	}
	if (access(valid_path, F_OK | X_OK) != 0)
		return (NULL);
	else
		return (valid_path);
}

t_parsed_chunk	*last_node_pars(t_parsed_chunk *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void add_node_pars(t_hold **hold)
{
	t_parsed_chunk *tmp;

	tmp = (t_parsed_chunk *)malloc(sizeof(t_parsed_chunk));
	// if (!tmp)
	// 	return (exit_status(hold, "Error! Failed to malloc\n", 69), (t_parsed_chunk*)NULL);
	tmp->args = NULL;
	tmp->cmd_path = NULL;
	tmp->next = NULL;
	tmp->infile = STDIN_FILENO;
	tmp->outfile = STDOUT_FILENO;
	if ((*hold)->parsed_list == NULL)
		(*hold)->parsed_list = tmp;
	else
		(last_node_pars((*hold)->parsed_list))->next = tmp;
}

void create_parsed_list(t_hold **hold, t_lexing *lex)
{
	int32_t pipegroups;
	int32_t tmp;
	t_lexing *tmp_lex;
	t_parsed_chunk *tmp_pars;
	char *tmp_arg;

	tmp_arg = malloc(sizeof(char));
	tmp_arg = "\0";
	tmp_pars = NULL;
	tmp_lex = lex;
	pipegroups = count_pipegroups(lex);
	tmp = pipegroups;
	// printf("amount pipegroups: %d\n", pipegroups);

	// malloc amount of nodes as there are pipegroups:
	while (pipegroups > 0)
	{
		add_node_pars(hold);
		pipegroups--;
	}
	pipegroups = tmp;

// init list
	tmp_pars = (*hold)->parsed_list;
	while (pipegroups > 0)
	{
		while (tmp_lex->macro != PIPE)
		{
			if (tmp_lex->macro == SING_CLOSE_REDIR || tmp_lex->macro == DOUBL_CLOSE_REDIR)
			{
				tmp_pars->outfile = check_outfile(*hold, tmp_lex->next, tmp_lex->macro);
				tmp_lex = tmp_lex->next;
			}
			else if (tmp_lex->macro == SING_OPEN_REDIR)
			{
				tmp_pars->infile = check_infile(*hold, tmp_lex->next);
				tmp_lex = tmp_lex->next;
			}
			else if (tmp_lex->macro == DOUBL_OPEN_REDIR)	// herdoc function <<
				printf(MAG"DOUBL_CLOSE_REDIR -> add later\n"RESET);
			else
			{
				if (tmp_arg == NULL)
					tmp_arg = ft_strdup(tmp_lex->item);
				else
				{
					tmp_arg = ft_strjoin(tmp_arg, " ");
					tmp_arg = ft_strjoin(tmp_arg, tmp_lex->item); 
				}
				// printf(MAG"ARG -> add later\n"RESET);
				
			}
			if (tmp_lex->next == NULL)
				break ;
			tmp_lex = tmp_lex->next;
		}
		if (ft_strlen(tmp_arg) == 0)
		{
			printf(RED"pipegroup doesnt conatin any commands: %s -> dunno what to do | EXIT\n"RESET, tmp_lex->item);
			exit(0);
		}
		tmp_pars->args = ft_split(tmp_arg, ' ');
		tmp_pars->cmd_path = get_cmdpath(tmp_pars->args[0]);
		free(tmp_arg);
		tmp_arg = "\0";
		tmp_lex = tmp_lex->next;
		tmp_pars = tmp_pars->next;
		pipegroups--;
	}
}

void parser(t_hold *hold)
{
	recognize_type(hold);

    if (hold->exit_code != 0 || check_syntax_errors(hold))
        return ;

	create_parsed_list(&hold, hold->lex_struct);
	
}