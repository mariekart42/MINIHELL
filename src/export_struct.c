#include "minishell.h"

void	sort_export_list_sub(t_hold *hold, t_env_exp	*tmp)
{
	if (ft_strncmp(hold->export_list->var_name,
			hold->export_list->next->var_name,
			ft_strlen(hold->export_list->next->var_name)) > 0)
	{
		swap_data(hold->export_list);
		hold->export_list = tmp;
	}
	else
		hold->export_list = hold->export_list->next;
}

void	sort_export_list(t_hold *hold)
{
	t_env_exp	*tmp;
	char		**tmp_tmp;
	int			i;

	i = 2;
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		tmp_tmp = ft_split(tmp->item, '=');
		tmp->var_name = tmp_tmp[0];
		tmp->var_value = tmp_tmp[1];
		while (tmp_tmp[i] != NULL)
		{
			tmp->var_value = ft_strjoin(tmp->var_value, tmp_tmp[i]);
			i++;
		}
		free(tmp_tmp);
		i = 2;
		tmp = tmp->next;
	}
	tmp = hold->export_list;
	while (hold->export_list != NULL && hold->export_list->next != NULL)
		sort_export_list_sub(hold, tmp);
	hold->export_list = tmp;
}

t_env_exp	*new_node_env(void)
{
	t_env_exp	*tmp;

	tmp = (t_env_exp *)malloc(sizeof(t_env_exp));
	tmp->next = NULL;
	tmp->item = NULL;
	tmp->var_name = NULL;
	tmp->var_value = NULL;
	return (tmp);
}

void	add_node_export_sub(t_hold *hold, t_env_exp *tmp, t_env_exp *p)
{
	if (hold->export_list == NULL)
			hold->export_list = tmp;
	else
	{
		p = hold->export_list;
		while (p->next != NULL)
			p = p->next;
		p->next = tmp;
	}
}

void	add_node_env(t_hold *hold, char *content, char *type)
{
	t_env_exp	*tmp;
	t_env_exp	*p;

	tmp = new_node_env();
	tmp->item = content;
	p = NULL;
	if (ft_strncmp(type, "env", 3) == 0)
	{
		if (hold->env_list == NULL)
			hold->env_list = tmp;
		else
		{
			p = hold->env_list;
			while (p->next != NULL)
				p = p->next;
			p->next = tmp;
		}
		return ;
	}
	else
	{
		add_node_export_sub(hold, tmp, p);
		return ;
	}
}
<<<<<<< HEAD
=======
