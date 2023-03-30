#include "minishell.h"

void	delete_var(t_hold **hold, char *var, char *structure)
{
	t_env_exp	*tmp;
	t_env_exp	*prev;

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
	t_env_exp	*tmp;
	bool		var_exist;

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

int	print_unset_exit(t_pars *parsed_node, int i)
{
	if (ft_isdigit(parsed_node->args[i][0]) != 0)
	{
		exit_status("export:", parsed_node->args[i],
			": not a valid identifier", 1);
	}
	return (0);
}

void	unset_builtin(t_hold *hold, t_pars *parsed_node)
{
	int		i;
	int		j;

	i = 1;
	j = 0;
	while (parsed_node->args[i] != NULL)
	{
		if (print_unset_exit(parsed_node, i) == 0)
			return ;
		while (parsed_node->args[i][j] != '\0')
		{
			if (ft_isalnum_mod(parsed_node->args[i][j]) == 0)
			{
				exit_status("unset:", parsed_node->args[i],
					": not a valid identifier", 1);
				return ;
			}
			j++;
		}
		find_var(hold, parsed_node->args[i], "export");
		if (find_var(hold, parsed_node->args[i], "env") == false)
			return ;
		j = 0;
		i++;
	}
}
