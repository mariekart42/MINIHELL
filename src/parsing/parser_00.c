#include "minishell.h"

void	sub_open_extension(t_lex	*lex, int i, t_hold *hold)
{
	char	*to_free;
	char	*extended;

	if (lex->item[i + 1] == '?' && lex->item[i + 2] == '\0')
		return ;
	to_free = lex->item;
	extended = extend(&lex->item[i], hold);
	lex->item = ft_strnnjoin(lex->item, i, extended, ft_strlen(extended));
	free(to_free);
	return ;
}

void	open_extensions(t_lex *lex, t_hold *hold)
{
	t_lex	*tmp;
	size_t	i;

	tmp = lex;
	while (tmp)
	{
		i = 0;
		while (i < ft_strlen(tmp->item) && (tmp->macro == DOUBL_QUOTE \
												|| tmp->macro == WORD))
		{
			if (tmp->item[i] == '$')
				sub_open_extension(tmp, i, hold);
			i++;
		}
		tmp = tmp->next;
	}
}

int32_t	init_pars_node(t_pars **pars_node, t_lex **lex_node, int32_t i)
{
	(*pars_node)->args = malloc(sizeof(char *) * (arg_amount((*lex_node)) + 1));
	i = 0;
	while ((*lex_node)->macro != PIPE)
	{
		(*pars_node)->outfile = init_outfile((*lex_node)->next, \
													(*lex_node)->macro);
		(*pars_node)->infile = init_infile((*pars_node), (*lex_node)->next, \
													(*lex_node)->macro);
		if ((*lex_node)->macro == SING_CLOSE_REDIR \
			|| (*lex_node)->macro == DOUBL_CLOSE_REDIR \
			|| (*lex_node)->macro == SING_OPEN_REDIR \
			|| (*lex_node)->macro == DOUBL_OPEN_REDIR)
			(*lex_node) = (*lex_node)->next;
		else
		{
			(*pars_node)->args[i] = ft_strdup((*lex_node)->item);
			i++;
		}
		if ((*lex_node)->next == NULL)
			break ;
		(*lex_node) = (*lex_node)->next;
	}
	return (i);
}

void	create_parsed_list(t_hold **hold, t_lex *lex, int32_t pipegroups)
{
	int32_t	i;
	t_lex	*tmp_lex;
	t_pars	*tmp_pars;

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
		i = init_pars_node(&tmp_pars, &tmp_lex, i);
		tmp_pars->args[i] = NULL;
		tmp_pars->cmd_path = get_cmdpath(tmp_pars->args[0]);
		tmp_lex = tmp_lex->next;
		tmp_pars = tmp_pars->next;
		pipegroups--;
	}
}

void	parser(t_hold *hold)
{
	recognize_type(hold);
	count_pipegroups(hold);
	if (g_error_code != 0 || check_syntax_errors(hold))
		return ;
	open_extensions(hold->lex_struct, hold);
	create_parsed_list(&hold, hold->lex_struct, hold->pipegroups);
}
