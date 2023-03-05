#include "minishell.h"

// https://man7.org/linux/man-pages/man1/unset.1p.html

int	find_var(t_hold *hold, char *var)
{

}


void unset_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	char	**args;

	args = parsed_node->args;
	

}

// void export_builtin(t_hold *hold)
// {
// }