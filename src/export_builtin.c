#include "minishell.h"

// void	sort_export_list(t_hold *hold, char *var) 
// {
// }

void print_env_export(t_hold *hold)
{
	t_env_export *tmp;
	
	tmp = hold->export_list;
	while (tmp != NULL)
	{
		ft_putstr_fd("declare -x ", hold->parsed_list->outfile);
		ft_putstr_fd(tmp->item, hold->parsed_list->outfile);
		write(hold->parsed_list->outfile, "\n", 1);
		tmp = tmp->next;
	}
}

void	add_to_env_mod(t_hold *hold, char *add, int var_class)
{
	t_env_export	*new;
	t_env_export	*tmp;

	var_class = 0;
	new = malloc(sizeof(t_env_export));
	new->item = ft_strdup(add);
	new->next = NULL;
	tmp = hold->env_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	add_to_export_mod(t_hold *hold, char *add, int var_class)
{
	t_env_export	*new;
	t_env_export	*tmp;
	char			*tmp_add;
	char			*tmp_add2;

	if (var_class == 1)
		tmp_add = ft_strjoin(add, "\"\"");
	if (var_class == 2)
	{
		tmp_add2 = ft_strjoin("\"", add);
		free(tmp_add2);
		tmp_add = ft_strjoin(tmp_add2, "\"");
	}
	new = malloc(sizeof(t_env_export));
	new->item = ft_strdup(tmp_add);
	free(tmp_add);
	new->next = NULL;
	tmp = hold->export_list;
	while (tmp->next != NULL)
		tmp = tmp->next;
	tmp->next = new;
}

void	export_builtin(t_hold *hold, t_parsed_chunk *parsed_node)
{
	int		i;
	int		j;
	int		var_class;

	i = 1;
	j = 0;
	if (parsed_node->args[1] == NULL)
	{
		print_env_export(hold);
		return ;
	}
	while (parsed_node->args[i] != NULL)
	{
		var_class = 0;
		while (parsed_node->args[i][j] != '\0')
		{
			if (parsed_node->args[i][j] == '=')
			{
				if (parsed_node->args[i][j + 1] == '\0')
					var_class = 1;
				else
					var_class = 2;
			}
			j++;
		}
		if (var_class == 0)
		{
			find_var(hold, parsed_node->args[i], "export");
			add_to_env(hold, parsed_node->args[i], "export");
		}
		else
		{
			find_var(hold, parsed_node->args[i], "env");
			find_var(hold, parsed_node->args[i], "export");
			add_to_env_mod(hold, parsed_node->args[i], var_class);
			add_to_export_mod(hold, parsed_node->args[i], var_class);
		}
		// sort_export_list(hold, parsed_node->args[i]); // Problem for Future Santiago
		j = 0;
		i++;
	}
}

//To do

// Sort with bubble sort
// [ ] Remove node if var alredy exists and replace 
// open_quotes.c from Fedia for case 2

// Check with "string cases"
// export - var var="" var="abc def"
// env - var var= var=abc def
// cmd - [x]0 [x]1 [x]2

// [x] Ask Marie about case 3:
// [x] 3 is a full arg by itself arg[i] == "abc def"

////////////////
// char	*ft_strndup(const char *s1, size_t n)
// {
// 	char	*cpy;

// 	if (ft_strlen((char *)s1) < n)
// 		cpy = ft_strnew(ft_strlen((char *)s1));
// 	else
// 		cpy = ft_strnew(n);
// 	if (cpy == NULL)
// 		return (NULL);
// 	return (ft_strncpy(cpy, (char *)s1, n));
// }
/////////