#include "minishell.h"

int32_t	check_syntax_errors(t_hold *hold)
{
	if ((last_node_lex(hold->lex_struct))->macro == PIPE || \
		(last_node_lex(hold->lex_struct))->macro == SING_CLOSE_REDIR || \
		(last_node_lex(hold->lex_struct))->macro == SING_OPEN_REDIR || \
		(last_node_lex(hold->lex_struct))->macro == DOUBL_CLOSE_REDIR)
	{
		exit_status("syntax error near unexpected token 'newline'", "", "", 69);
		return (-1);
	}
	return (0);
}
