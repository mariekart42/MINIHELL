#include "minishell.h"

int32_t	lex_word(t_hold *hold, char *s, int32_t i)
{
	char	*quote_chunk_;
	char	*string;
	int32_t	x;

	quote_chunk_ = NULL;
	string = ft_calloc(ft_strlen(s) + 1, 1);
	x = 0;
	while (1)
	{
		if (s[i] == '\0' || s[i] == ' ' || s[i] == '|' || s[i] == '>' \
							|| s[i] == '<' || (s[i] == '$' && s[i + 1] == '?'))
			break ;
		else if (s[i] == 34 || s[i] == 39)
		{
			quote_chunk_ = quote_chunk2(s, i);
			i += update_i(quote_chunk_);
			if (quote_chunk_ != NULL)
				string = handle_quote_chunk(&string, &quote_chunk_);
			x = ft_strlen(string) - 1;
		}
		else
			string[x] = s[i];
		i++;
		x++;
	}
	if (x > 0)
	{
		string[x] = '\0';
		add_node_lex(hold, string);
		free(string);
	}
	return (i - 1);
}

/* function adds pipe symbol as a new node to the 'lex_struct'
 * THROWS ERROR IF:
 *		- pipe at the very beginning of the line
 *		- more then one pipe symbol in a row (only seperated by spaces) */
void	lex_pipe(t_hold *hold, int32_t i)
{
	if (i == 0)
		return (exit_status("syntax error near unexpected token '|'", ""\
																	, "", 2));
	i++;
	while (hold->line[i] == ' ')
		i++;
	if (hold->line[i] == '|')
		return (exit_status("syntax error near unexpected token '|'", ""\
																	, "", 2));
	add_node_lex(hold, "|");
}

void	check_closed_quotes(t_hold *hold)
{
	char	quote;
	int32_t	i;

	i = 0;
	while (hold->line[i] != '\0')
	{
		if (hold->line[i] == 34 || hold->line[i] == 39)
		{
			quote = hold->line[i];
			i++;
			while (hold->line[i] != quote)
			{
				if (hold->line[i] == '\0')
					return (exit_status("syntax error: quotes are unclosed!"\
																, "", "", 69));
				i++;
			}
		}
		i++;
	}
}

// devide chunks of commands etc in single linked list
void	lexer(t_hold *hold)
{
	int32_t	i;

	i = 0;
	check_closed_quotes(hold);
	while (hold->line[i] != '\0' && hold->line[i] != '\n')
	{
		if (g_error_code != 0)
			return ;
		if (hold->line[i] == '$' && hold->line[i + 1] == '?')
		{
			add_node_lex(hold, "$?");
			i++;
		}
		else if (hold->line[i] == '|')
			lex_pipe(hold, i);
		else if (hold->line[i] == '<' || hold->line[i] == '>')
			i = lex_redir(hold, i);
		else if (hold->line[i] != ' ' && hold->line[i] != '\t')
			i = lex_word(hold, hold->line, i);
		i++;
	}
	if (hold->lex_struct == NULL)
		exit_status(": :command not found!", "", "", 127);
}
