#include "minishell.h"

void	swap_data(t_env_exp *export_list)
{
	char	*tmp_item;

	tmp_item = export_list->item;
	export_list->item = export_list->next->item;
	export_list->next->item = tmp_item;
}
