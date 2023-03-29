#include "minishell.h"

void	add_arg(t_pars *pars_node)
{
	int32_t	i;
	char	**new_args;
	t_pars	*tmp;

	i = 0;
	tmp = pars_node;
	while (tmp->args[i++] != NULL)
		tmp = tmp->next;
	new_args = malloc(sizeof(char *) * i + 1);
	tmp = pars_node;
	i = 0;
	while (tmp->args[i] != NULL)
	{
		new_args[i] = ft_strdup(tmp->args[i]);
		i++;
	}
}

int32_t	arg_amount(t_lex *lex_node)
{
	int32_t	arg_amount;

	arg_amount = 0;
	while (lex_node && lex_node->macro != PIPE)
	{
		if (lex_node->macro != SING_CLOSE_REDIR && \
			lex_node->macro != SING_OPEN_REDIR && \
			lex_node->macro != DOUBL_CLOSE_REDIR && \
			lex_node->macro != DOUBL_OPEN_REDIR)
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
	int			i;
	t_env_exp	*tmp;

	i = 0;
	tmp = hold->env_list;
	while (var[i])
	{
		if (var[i] == '$')
			break ;
		i++;
	}
	while (tmp != NULL)
	{
		if (ft_strncmp(var, tmp->item, i) == 0)
			return (ft_strdup(&tmp->item[i + 1]));
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
	while (var[i])
	{
		if (var[i] == '$')
		{
			if (ft_strlen(var) == 1)
				return (strdup("$"));
			if (var[i + 1] == '?')
				ext = ft_itoa(error_code);
			else
				ext = sub_extend(&var[i + 1], hold);
			ret = ft_strnnjoin(ret, ft_strlen(ret), ext, ft_strlen(ext));
			free(ext);
		}
		i++;
	}
	return (ret);
}
