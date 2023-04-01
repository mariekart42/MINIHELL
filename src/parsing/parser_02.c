#include "minishell.h"

/* function counts and returns amount of pipegroups in 'lexed_list' */
void	count_pipegroups(t_hold *hold)
{
	t_lex	*tmp;
	int32_t	pipegroup;

	pipegroup = 1;
	tmp = hold->lex_struct;
	while (tmp != NULL)
	{
		if (tmp->macro == PIPE)
			pipegroup++;
		tmp = tmp->next;
	}
	if (pipegroup > 1000)
		exit_status("fugguUUUUUUU!", "", "", 69);
	else
		hold->pipegroups = pipegroup;
}

/* function appends command from 'pars_list' at the end of
 * each path of $PATH and checks for access
 * in case of access, function returns path
 * otherwise returns NULL		*/
char	*get_cmdpath(char *curr_cmd)
{
	char	**env_path;
	char	*valid_path;
	char	*tmp;
	int32_t	i;

	env_path = ft_split(getenv("PATH"), ':');
	tmp = NULL;
	i = 0;
	while (env_path[i] != NULL)
	{
		tmp = ft_strjoin(env_path[i], "/");
		valid_path = ft_strjoin(tmp, curr_cmd);
		free(tmp);
		tmp = NULL;
		if (access(valid_path, F_OK | X_OK) == 0)
			break ;
		free(valid_path);
		valid_path = NULL;
		i++;
	}
	free_env_path(env_path);
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

void	add_node_pars(t_hold **hold)
{
	t_pars	*tmp;

	tmp = (t_pars *)malloc(sizeof(t_pars));
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
