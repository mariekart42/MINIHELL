#include "minishell.h"

int32_t	init_structs(t_hold *hold, char **argv, int32_t argc)
{
	(void)argv;
	(void)argc;
	g_error_code = 0;
	hold->prev_error = 0;
	hold->line = NULL;
	hold->env_list = NULL;
	hold->pars_list = NULL;
	hold->export_list = NULL;
	hold->lex_struct = NULL;
	return (0);
}

void	create_env_export_list(t_hold *hold, char **ori_env)
{
	int32_t	env_len;

	env_len = 0;
	while (ori_env[env_len] != NULL)
	{
		add_node_env(hold, ori_env[env_len], "env");
		add_node_env(hold, ori_env[env_len], "export");
		env_len++;
	}
	sort_export_end(hold->export_list);
}
