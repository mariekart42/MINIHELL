#include "minishell.h"

t_env_exp	*new_node_env(void)
{
	t_env_exp	*tmp;

	tmp = (t_env_exp *)malloc(sizeof(t_env_exp));
	tmp->next = NULL;
	tmp->item = NULL;
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
	tmp->item = ft_strdup(content);
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
