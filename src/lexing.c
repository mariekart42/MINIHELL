#include "minishell.h"

/* function adds pipe symbol as a new node to the 'lex_struct'
 * THROWS ERROR IF:
 *		- pipe at the very beginning of the line
 *		- more then one pipe symbol in a row (only seperated by spaces) */
void lex_pipe(t_hold *hold, int32_t i)
{
	if (i == 0)
		return (exit_status("syntax error near unexpected token '|'", "", "", 2));
	i++;
	while (hold->line[i] == ' ')
		i++;
	if (hold->line[i] == '|')
		return (exit_status("syntax error near unexpected token '|'", "", "", 2));
	add_node_lex(hold, "|");
}

/* function skips all spaces and returns new index i			*/
int32_t skip_spaces(char *str, int32_t i)
{
	while (str[i] == 32)
		i++;
	return (i);
}

/* function checks if there are no more signs beside space and redirection sign	
 * it's an syntax error if there is nothing but redirection signs 
 * returns -1 if there is an illegal redirection sign
 * returns  0 if everything is noice        */
int32_t check_beginning_redir(t_hold *hold)
{
	int32_t i;

	i = 0;
	while(hold->line[i] != '\0' && hold->line[i] != '\n')
	{
		if (hold->line[i] != 32 && hold->line[i] != '<' && hold->line[i] != '>')
			return (0);
		i++;		
	}
	exit_status("syntax error near unexpected token 'newline'", "", "", 2);
    return (-1);
}

/* function adds redirection symbol(s) as a new node to the 'lex_struct'
 * THROWS ERROR IF:
 *		- redir sign at the very beginning and nothing else (except spaces)
 *		- same symbol more then 2 times in a row (eg. >>>, > > >, >> >)
 *		- in any case this syntax: '><'	(eg. ><, <><, >><)						*/
int32_t lex_redir(t_hold *hold, int32_t i)
{

	if ((i == 0) && (check_beginning_redir(hold) != 0))
		return (-1);
	if (hold->line[i] == '<')
	{


		// i++;
		i = skip_spaces(hold->line, i+1) + 1;
		if(hold->line[i] == '<')
		{
			add_node_lex(hold, "<<");
			i++;
			i = skip_spaces(hold->line, i);
			if (hold->line[i] == '<')
                return (exit_status("syntax error near unexpected token '<'", "", "", 69), -1);
			return (i-1);
		}
		add_node_lex(hold, "<");
		return (i-1);
	}
	else if (hold->line[i] == '>')
	{
		// i++;
		i = skip_spaces(hold->line, i+1) + 1;
		if (hold->line[i] == '<')
            return (exit_status("syntax error near unexpected token '<'", "", "", 69), -1);
		if (hold->line[i] == '>')
		{
			add_node_lex(hold, ">>");
			i++;
			i = skip_spaces(hold->line, i);
			if (hold->line[i] == '>' || hold->line[i] == '<')
                return (exit_status("syntax error near unexpected token '>'", "", "", 69), -1);
			return (i-1);
		}
		add_node_lex(hold, ">");
		return (i-1);
	}
	return (69);
}

char *add_letter(char *pointer, char letter)
{
	int32_t i;
	char *return_pointer;

	i = 0;
	return_pointer = (char *)malloc(ft_strlen(pointer) + 2);
	while (pointer[i] != '\0')
	{
		return_pointer[i] = pointer[i];
		i++;
	}
	return_pointer[i] = letter;
	i++;
	return_pointer[i] = '\0';
	free(pointer);
	pointer = NULL;
	return (return_pointer);
}

int32_t quote_len(char *line, int32_t i, char quote)
{
	int32_t len;

	len = 0;
	while (line[i] != '\0')
	{
		if (line[i] == quote)
			return (len);
		len++;
		i++;
	}
	return (-1);
}

char *quote_chunk2(char *line, int32_t i)
{
	char quote;
	char *string;
	int32_t quote_len_;
	int32_t x;

	quote = line[i];
	quote_len_ = quote_len(line, i+1, quote);
	if (line[i + 1] == quote || quote_len_ == -1)
		return (NULL);
	string = (char *)malloc(quote_len_ + 1);
	x = 0;
	i++;
	while (line[i] != '\0')
	{
		if (line[i] == quote)
			break ;
		string[x] = line[i];
		x++;
		i++;
	}
	if (x <= 0)
		return (NULL);
	string[x] = '\0';
	return (string);
}

char *handle_quote_chunk(char **string, char **quote_chunk)
{
	char *tmp;

	tmp = ft_strjoin(*string, *quote_chunk);
	free(*string);
	*string = ft_strdup(tmp);
	free(tmp);
	free(*quote_chunk);
	tmp = NULL;
	quote_chunk = NULL;
	return (*string);
}

int32_t update_i(char *quote_chunk)
{
	if (quote_chunk == NULL)
		return (1);
	else
		return (ft_strlen(quote_chunk) + 1);
}

int32_t lex_word(t_hold *hold, char *line, int32_t i)
{
	char *quote_chunk_;
	char *string;
	int32_t x;

	quote_chunk_ = NULL;
	string = ft_calloc(ft_strlen(line) + 1, 1);
	x = 0;
	while (1)
	{
		if (line[i] == '\0' || line[i] == ' ' || line[i] == '|' || line[i] == '>' || line[i] == '<' || (line[i] == '$' && line[i+1] == '?'))
			break ;
		else if (line[i] == 34 || line[i] == 39)
		{
			quote_chunk_ = quote_chunk2(line, i);
			i += update_i(quote_chunk_);
			if (quote_chunk_ != NULL)
				string = handle_quote_chunk(&string, &quote_chunk_);
			x = ft_strlen(string) - 1;
		}
		else
			string[x] = line[i];
		i++;
		x++;
	}
	if (x > 0)
	{
		string[x] = '\0';
		add_node_lex(hold, string);
		free(string);
	}
	return (i-1);
}

void check_closed_quotes(t_hold *hold)
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
					return(exit_status("syntax error: quotes are unclosed!", "", "", 69));
				i++;
			}
		}
		i++;
	}
}

// devide chunks of commands etc in single linked list
void lexer(t_hold *hold)
{
	int32_t	i;

	i = 0;
	check_closed_quotes(hold);
	while (hold->line[i] != '\0' && hold->line[i] != '\n')
	{
        if (error_code != 0)
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
