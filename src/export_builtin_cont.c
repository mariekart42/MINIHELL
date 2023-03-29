#include "minishell.h"

void	add_to_export_mod(t_hold *hold, char **vars,
							int var_class)
{
	t_env_exp	*new;
	t_env_exp	*tmp;
	char		*tmp_add;
	char		*tmp_add2;
	char		*tmp_add3;

	if (var_class == 1)
		tmp_add = ft_strjoin(vars[0], "=\"\"");
	if (var_class == 2)
	{
		tmp_add3 = ft_strjoin(vars[0], "=\"");
		tmp_add2 = ft_strjoin(tmp_add3, vars[1]);
		tmp_add = ft_strjoin(tmp_add2, "\"");
		free(tmp_add2);
		free(tmp_add3);
	}
	new = malloc(sizeof(t_env_exp));
	new->item = ft_strdup(tmp_add);
	free(tmp_add);
	new->next = NULL;
	tmp = hold->export_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	print_env_export(t_hold *hold)
{
	t_env_exp	*tmp;

	tmp = hold->export_list;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", hold->pars_list->outfile);
		ft_putstr_fd(tmp->item, hold->pars_list->outfile);
		write(hold->pars_list->outfile, "\n", 1);
		tmp = tmp->next;
	}
}

int	export_empty(t_hold *hold, t_pars *parsed_node)
{
	if (parsed_node->args[1] == NULL)
	{
		print_env_export(hold);
		return (0);
	}
	return (1);
}

int	get_var_type(t_pars *parsed_node, int i, int j)
{
	if (parsed_node->args[i][j + 1] == '\0')
		return (1);
	if (parsed_node->args[i][j + 1] != '\0')
		return (2);
	return (0);
}

char	*assign_var_value(t_pars *parsed_node, int i, int j)
{
	return (ft_strndup(&parsed_node->args[i][j + 1],
		ft_strlen(parsed_node->args[i]) + 1));
}
