#include "minishell.h"

bool builtin_parser(char *node)
{
	if (ft_strncmp(node, "echo\0", 5) == 0)
		return (true);
	else if (ft_strncmp(node, "pwd\0", 4) == 0)
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
int32_t init_outfile(t_lexing *file_node, int32_t type)
{
	int32_t file_id;

	file_id = 1;
	if (type != SING_CLOSE_REDIR && type != DOUBL_CLOSE_REDIR)
		return (1);
// not 100% sure about opening macros (in both open calls)
	if (type == SING_CLOSE_REDIR)
		file_id = open(file_node->item, O_CREAT | O_WRONLY | O_TRUNC , 0644);
	else if (type == DOUBL_CLOSE_REDIR)
		file_id = open(file_node->item, O_CREAT | O_WRONLY | O_APPEND); // check if its right
	if (file_id < 0)
		exit_status("Error!: unable to open outfile (in check_outfile func)\n", 69);
	return (file_id);
}

/* function checks and returns infile on success
 * input file must exist and be readable by the user running the command
 * file_node is the current node in parsed_list	*/
int32_t init_infile(t_parsed_chunk *file_node_pars, t_lexing *file_node_lex, int32_t type)
{
	int32_t file_id;

	file_id = 0;
	if (type == SING_OPEN_REDIR)
	{
	// not 100% sure about opening macros
		file_id = open(file_node_lex->item, O_RDONLY);
		if (file_id < 0)
		{
			write(2, RED"minihell: ", 16);
			ft_putstr_fd(file_node_lex->item, 2);
			exit_status(": no such file or directory\n"RESET, 69);
		}
		file_node_pars->here_doc_delim = NULL;
	}
	else if (type == DOUBL_OPEN_REDIR)
	{
		file_id = open("tmp.hd", O_WRONLY | O_CREAT, 0777);
		if (file_id < 0)
		{
			write(2, RED"minihell: ", 16);
			ft_putstr_fd(file_node_lex->item, 2);
			exit_status(": no such file or directory\n"RESET, 69);
		}
		file_node_pars->here_doc_delim = ft_strdup(file_node_lex->next->item);
	}
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
	char *tmp;
	int32_t i = 0;

	tmp = NULL;
	env_path = ft_split(getenv("PATH"), ':');
	while (env_path[i] != NULL)
	{
		tmp = ft_strjoin(env_path[i], "/");
		// env_path[i] = ft_strjoin(env_path[i], "/");
		// valid_path = ft_strjoin(env_path[i], curr_cmd);
		valid_path = ft_strjoin(tmp, curr_cmd);
		free(tmp);
		tmp = NULL;
		if (access(valid_path, F_OK | X_OK) == 0)
			break ;
		free(valid_path);
		valid_path = NULL;
		i++;
	}
	i=0;
	while(env_path[i] != NULL)
	{
		free(env_path[i]);
		env_path[i] = NULL;
		i++;
	}
	free(env_path);
	env_path = NULL;
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
	tmp->here_doc_delim = NULL;
	tmp->infile = STDIN_FILENO;
	tmp->outfile = STDOUT_FILENO;
	if ((*hold)->parsed_list == NULL)
		(*hold)->parsed_list = tmp;
	else
		(last_node_pars((*hold)->parsed_list))->next = tmp;
}

void add_arg(t_parsed_chunk *pars_node)
{
	int32_t i;
	int32_t x;
	char **new_args;
	t_parsed_chunk *tmp;

	i = 0;
	x = 0;
	tmp = pars_node;
	while (tmp->args[i] != NULL)
	{
		tmp = tmp->next;
		i++;
	}
	new_args = malloc(sizeof(char *) * i + 1);
	tmp = pars_node;
	while (tmp->args[x] != NULL)
	{
		new_args[x] = ft_strdup(tmp->args[x]);
		x++;
	}
}

int32_t arg_amount(t_lexing *lex_node)
{
	int32_t arg_amount;

	arg_amount = 0;
	while (lex_node && lex_node->macro != PIPE)
	{
		if (lex_node->macro != SING_CLOSE_REDIR && lex_node->macro != SING_OPEN_REDIR && lex_node->macro != DOUBL_CLOSE_REDIR && lex_node->macro != DOUBL_OPEN_REDIR)
			arg_amount++;
		lex_node = lex_node->next;
	}
	return (arg_amount);
}

void create_parsed_list(t_hold **hold, t_lexing *lex, int32_t pipegroups)
{
	int32_t i;
	t_lexing *tmp_lex;
	t_parsed_chunk *tmp_pars;

	tmp_pars = NULL;
	tmp_lex = lex;
	i = pipegroups;
	while (pipegroups > 0)
	{
		add_node_pars(hold);
		pipegroups--;
	}
	pipegroups = i;
	tmp_pars = (*hold)->parsed_list;
	while (pipegroups > 0)
	{
		tmp_pars->args = malloc(sizeof(char *) * arg_amount(tmp_lex) + 1);
		i = 0;
		while (tmp_lex->macro != PIPE)
		{
			tmp_pars->outfile = init_outfile(tmp_lex->next, tmp_lex->macro);
			tmp_pars->infile = init_infile(tmp_pars, tmp_lex->next, tmp_lex->macro);
			if (tmp_lex->macro == SING_CLOSE_REDIR || tmp_lex->macro == DOUBL_CLOSE_REDIR || tmp_lex->macro == SING_OPEN_REDIR || tmp_lex->macro == DOUBL_OPEN_REDIR)
				tmp_lex = tmp_lex->next;
			else
			{
				tmp_pars->args[i] = ft_strdup(tmp_lex->item);
				i++;
			}

			if (tmp_lex->next == NULL)
				break ;
			tmp_lex = tmp_lex->next;
		}
		tmp_pars->args[i] = NULL;
		tmp_pars->cmd_path = get_cmdpath(tmp_pars->args[0]);
		tmp_lex = tmp_lex->next;
		tmp_pars = tmp_pars->next;
		pipegroups--;
	}
}

void parser(t_hold *hold)
{
	int32_t pipegroups;

	recognize_type(hold);
	pipegroups = count_pipegroups(hold->lex_struct);
    if (error_code != 0 || check_syntax_errors(hold))
        return ;
	create_parsed_list(&hold, hold->lex_struct, pipegroups);
}