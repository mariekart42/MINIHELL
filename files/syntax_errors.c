#include "../head/minishell.h"

/* function checks lexed_list for any kind of 
 * syntax errors (most of them are already handeled in lexer)
 * sets global variable 'exit_code' to error return value
 * returns 0 if not detected any errors
 * returns -1 in case of error */
int32_t check_syntax_errors(t_hold *hold)
{
	// if pipe or closed redir sign at very end
	printf("%s\n", (last_node_lex(hold->lex_struct))->item);
	if ((last_node_lex(hold->lex_struct))->macro == PIPE || \
		(last_node_lex(hold->lex_struct))->macro == SING_CLOSE_REDIR || \
		(last_node_lex(hold->lex_struct))->macro == SING_OPEN_REDIR || \
		(last_node_lex(hold->lex_struct))->macro == DOUBL_CLOSE_REDIR)
	{
		exit_status(hold, "syntax error near unexpected token 'newline'\n", 69);
		return (-1);
		// printf("test if\n\n");

	}
	return(0);
}