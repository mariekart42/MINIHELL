#include "minishell.h"

void	delete_var(t_hold **hold, char *var)
{
	t_env_export	*tmp;
	t_env_export	*prev;

	tmp = (*hold)->env_list;
	if (tmp != NULL && (ft_strncmp(tmp->item, var, ft_strlen(var)) == 0))
	{
		(*hold)->env_list = tmp->next;
		free(tmp);
		return ;
	}
	while (tmp != NULL && (ft_strncmp(tmp->item, var, ft_strlen(var)) != 0))
	{
		prev = tmp;
		tmp = tmp->next;
	}
	if (tmp == NULL)
		return ;
	prev->next = tmp->next;
	free(tmp);
}

bool	find_var(t_hold *hold, char *var)
{
	t_env_export	*tmp;
	bool			var_exist;

	var_exist = false;
	tmp = hold->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->item, var, ft_strlen(var)) == 0)
		{
			var_exist = true;
			delete_var(&hold, var);
		}
		tmp = tmp->next;
	}
	free(tmp);
	return (var_exist);
}

void	unset_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	char	**args;
	int		i;

	args = parsed_node->args;
	i = 1;
	while (args[i] != NULL)
	{
		if (find_var(hold, args[i]) == false)
		{
			// ft_putstr_fd(RED"minshell: unset: ", 2);
			// ft_putstr_fd(args[i], 2);
			// exit_status(hold, ": not a valid identifier\n"RESET, 69);
			return ;
		}
		i++;
	}
}

// void export_builtin(t_hold *hold)
// {
// }