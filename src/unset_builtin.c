#include "minishell.h"

void	delete_var(t_hold **hold, char *var, char *structure)
{
	t_env_export	*tmp;
	t_env_export	*prev;

	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = (*hold)->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = (*hold)->export_list;
	if (tmp != NULL && (ft_strncmp(tmp->item, var, ft_strlen(var)) == 0))
	{
		(*hold)->env_list = tmp->next;
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
}

bool	find_var(t_hold *hold, char *var, char *structure)
{
	t_env_export	*tmp;
	bool			var_exist;

	var_exist = false;
	if (ft_strncmp(structure, "env", 3) == 0)
		tmp = hold->env_list;
	if (ft_strncmp(structure, "export", 6) == 0)
		tmp = hold->export_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->item, var, ft_strlen(var)) == 0)
		{
			var_exist = true;
			delete_var(&hold, var, structure);
		}
		tmp = tmp->next;
	}
	return (var_exist);
}

void	unset_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	char	**args;
	int		i;
	int		j;

	args = parsed_node->args;
	i = 1;
	j = 0;
	while (args[i] != NULL)
	{
		while (args[i][j] != '\0')
		{
			if (ft_isalnum_mod(parsed_node->args[i][j]) == 0)
			{
				ft_putstr_fd(RED"minshell: unset: ", 2);
				ft_putstr_fd(parsed_node->args[i], 2);
				exit_status(": not a valid identifier\n"RESET, 1);
				return ;
			}
			j++;
		}
		find_var(hold, args[i], "export");
		if (find_var(hold, args[i], "env") == false)
			return ;
		j = 0;
		i++;
	}
}
