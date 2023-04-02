#include "../inc/minishell.h"

bool	is_heredoc_break(char	*input_string, t_pars *pars_node, char	*tmp2)
{
	bool	test;

	test = ft_strlen(pars_node->here_doc_delim) == ft_strlen(input_string);
	if (ft_strncmp(input_string, pars_node->here_doc_delim,
			ft_strlen(pars_node->here_doc_delim)) == 0 && test)
	{
		ft_putstr_fd(tmp2, pars_node->infile);
		free(tmp2);
		free(input_string);
		return (true);
	}
	return (false);
}

void	handle_here_doc_cont(t_pars *pars_node, char *input_string,
			char *tmp1, char *tmp2)
{
	heredoc_sig();
	while (1)
	{
		input_string = readline(CYN"heredoc> "RESET);
		if (is_heredoc_break(input_string, pars_node, tmp2))
			break ;
		if (tmp1 == NULL)
		{
			tmp1 = ft_strdup(input_string);
			tmp2 = ft_strjoin(tmp1, "\n");
			free(tmp1);
		}
		else
		{
			tmp1 = ft_strnnjoin(tmp2, ft_strlen(tmp2), input_string,
					ft_strlen(input_string));
			free(tmp2);
			tmp2 = ft_strjoin(tmp1, "\n");
			free(tmp1);
		}
		free(input_string);
	}
	close(pars_node->infile);
	pars_node->infile = open("tmp.hd", O_CREAT | O_RDONLY, 0777);
}

void	handle_here_doc(t_pars *pars_node)
{
	char	*input_string;
	char	*tmp1;
	char	*tmp2;

	input_string = NULL;
	tmp1 = NULL;
	tmp2 = NULL;
	if (pars_node->here_doc_delim == NULL)
		write(2, "problem with delim in handle_here_doc\n", 38);
	handle_here_doc_cont(pars_node, input_string, tmp1, tmp2);
}

void	handle_single_builtin(t_hold *hold)
{
	int32_t	tmp_in;
	int32_t	tmp_out;

	if (hold->pars_list->here_doc_delim != NULL)
		handle_here_doc(hold->pars_list);
	tmp_in = dup(STDIN_FILENO);
	tmp_out = dup(STDOUT_FILENO);
	dup2(hold->pars_list->infile, STDIN_FILENO);
	dup2(hold->pars_list->outfile, STDOUT_FILENO);
	builtin(hold, hold->pars_list);
	dup2(tmp_in, STDIN_FILENO);
	dup2(tmp_out, STDOUT_FILENO);
	if (hold->pars_list->infile != 0)
		close(hold->pars_list->infile);
	if (hold->pars_list->outfile != 1)
		close(hold->pars_list->outfile);
}

void	close_fds_parent(t_pars **parsed_node)
{
	if ((*parsed_node)->infile != 0)
		close((*parsed_node)->infile);
	if ((*parsed_node)->outfile != 1)
		close((*parsed_node)->outfile);
}
