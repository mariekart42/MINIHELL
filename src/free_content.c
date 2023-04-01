#include "minishell.h"

void	free_main(t_hold *hold)
{
	int32_t	i;

	i = 3;
	while (i < MAX_FD)
	{
		close(i);
		i++;
	}
	free_env_export(hold);
	clear_history();
}

void	free_content(t_hold *hold)
{
	free(hold->line);
	hold->line = NULL;
	free_list_lex(hold->lex_struct);
	free_list_pars(hold->pars_list);
	hold->lex_struct = NULL;
	hold->pars_list = NULL;
}

void	free_env_export(t_hold *hold)
{
	free_list_env_export(hold->env_list);
	free_list_env_export(hold->export_list);
	hold->env_list = NULL;
	hold->export_list = NULL;
}

void	free_env_path(char **env_path)
{
	int32_t	i;

	i = 0;
	while (env_path[i] != NULL)
	{
		free(env_path[i]);
		env_path[i] = NULL;
		i++;
	}
	free(env_path);
	env_path = NULL;
}