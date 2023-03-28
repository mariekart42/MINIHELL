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
	t_lex *tmp;

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
int32_t init_outfile(t_lex *file_node, int32_t type)
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
		exit_status("Error!: unable to open outfile (in check_outfile func)", "", "", 69);
	return (file_id);
}

/* function checks and returns infile on success
 * input file must exist and be readable by the user running the command
 * file_node is the current node in pars_list	*/
int32_t init_infile(t_pars *file_node_pars, t_lex *file_node_lex, int32_t type)
{
	int32_t file_id;

	file_id = 0;
	if (type == SING_OPEN_REDIR)
	{
	// not 100% sure about opening macros
		file_id = open(file_node_lex->item, O_RDONLY);
		if (file_id < 0)
		{
			// write(2, RED"minihell: ", 16);
			// ft_putstr_fd(file_node_lex->item, 2);
			exit_status(file_node_lex->item, ": no such file or directory", "", 69);
		}
		file_node_pars->here_doc_delim = NULL;
	}
	else if (type == DOUBL_OPEN_REDIR)
	{
		file_id = open("tmp.hd", O_WRONLY | O_CREAT, 0777);
		if (file_id < 0)
		{
			// write(2, RED"minihell: ", 16);
			// ft_putstr_fd(file_node_lex->item, 2);
			exit_status(file_node_lex->item, ": no such file or directory", "", 69);
		}
		file_node_pars->here_doc_delim = ft_strdup(file_node_lex->next->item);
	}
	return (file_id);
}

/* function counts and returns amount of pipegroups in 'lexed_list' */
void count_pipegroups(t_hold *hold)
{
	t_lex *tmp;
	int32_t	pipegroup;

	pipegroup = 1;
	tmp = hold->lex_struct;
	while (tmp != NULL)
	{
		if (tmp->macro == PIPE)
			pipegroup++;
		tmp = tmp->next;
	}
	hold->pipegroups = pipegroup;
	// return (pipegroup);
}

/* function appends command from 'pars_list' at the end of
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

t_pars	*last_node_pars(t_pars *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

void add_node_pars(t_hold **hold)
{
	t_pars *tmp;

	tmp = (t_pars *)malloc(sizeof(t_pars));
	// if (!tmp)
	// 	return (exit_status(hold, "Error! Failed to malloc\n", 69), (t_pars*)NULL);
	tmp->args = NULL;
	tmp->cmd_path = NULL;
	tmp->next = NULL;
	tmp->here_doc_delim = NULL;
	tmp->infile = STDIN_FILENO;
	tmp->outfile = STDOUT_FILENO;
	if ((*hold)->pars_list == NULL)
		(*hold)->pars_list = tmp;
	else
		(last_node_pars((*hold)->pars_list))->next = tmp;
}

void add_arg(t_pars *pars_node)
{
	int32_t i;
	int32_t x;
	char **new_args;
	t_pars *tmp;

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

int32_t arg_amount(t_lex *lex_node)
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

char	*ft_strnnjoin(char const *s1, int n1, char const *s2, int n2)
{
	char	*tmp;

	if (s1 && s2)
	{
		tmp = ft_strnew(n1 + n2);
		if (!tmp)
			return (NULL);
		tmp = ft_strncpy(tmp, (char *)s1, n1);
		ft_strlcat(tmp, (char *)s2, n1 + n2 + 1);
		return (tmp);
	}
	else if (s1 == NULL && s2 != NULL)
		return (ft_strndup((char *)s2, n2));
	else if (s2 == NULL && s1 != NULL)
		return (ft_strndup((char *)s1, n1));
	else
		return (NULL);
}

char	*sub_extend(char *var, t_hold *hold)
{
	int				i;
	t_env_exp	*tmp;

	i = 0;
	tmp = hold->env_list;
	while(var[i])
	{
		if(var[i] == '$')
			break ;
		i++;
	}
	while (tmp != NULL)
	{
		if (ft_strncmp(var, tmp->item, i) == 0)
		{
			return(ft_strdup(&tmp->item[i + 1]));
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	*extend(char *var, t_hold *hold)
{
	int		i;
	char	*ret;
	char	*ext;
	
	i = 0;
	ret = NULL;
	while(var[i])
	{
		if(var[i] == '$')
		{
			if(ft_strlen(var) == 1)
				return (strdup("$"));
			if(var[i + 1] == '?')
				ext = ft_itoa(error_code);
			else
				ext = sub_extend(&var[i + 1], hold);
			ret = ft_strnnjoin(ret,ft_strlen(ret), ext, ft_strlen(ext));
			free(ext);
		}
		i++;
	}
	return (ret);
}

void	sub_open_extension(t_lex	*lex, int i, t_hold *hold)
{
	char	*to_free;
	char	*extended;

	to_free = lex->item;
	extended = extend(&lex->item[i], hold);
	lex->item = ft_strnnjoin(lex->item, i, extended, ft_strlen(extended));
	free(to_free);
	return ;
}

void	open_extensions(t_lex *lex, t_hold *hold)
{
	t_lex	*tmp;
	size_t			i;

	tmp = lex;
	while (tmp)
	{
		i = 0;
		while(i < ft_strlen(tmp->item) && (tmp->macro == DOUBL_QUOTE 
			|| tmp->macro == WORD))
		{
			if(tmp->item[i] == '$')
				sub_open_extension(tmp, i, hold);
			i++;
		}
		tmp = tmp->next;
	}
}

void create_parsed_list(t_hold **hold, t_lex *lex, int32_t pipegroups)
{
	int32_t i;
	t_lex *tmp_lex;
	t_pars *tmp_pars;

	tmp_pars = NULL;
	tmp_lex = lex;
	i = pipegroups;
	while (pipegroups > 0)
	{
		add_node_pars(hold);
		pipegroups--;
	}
	pipegroups = i;
	tmp_pars = (*hold)->pars_list;
	while (pipegroups > 0)
	{
		tmp_pars->args = malloc(sizeof(char *) * (arg_amount(tmp_lex) + 1));
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
	// int32_t pipegroups;

	recognize_type(hold);
	// hold->pipegroups = 
	count_pipegroups(hold);
    if (error_code != 0 || check_syntax_errors(hold))
        return ;
	open_extensions(hold->lex_struct, hold);
	create_parsed_list(&hold, hold->lex_struct, hold->pipegroups);
}