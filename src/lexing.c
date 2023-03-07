#include "minishell.h"

// throw error if the amount of quotes is unequal (no interpreting of unclosed quotes)
// returns the i that gives the position after the closing quote
int32_t lex_quote(t_hold *hold, int32_t i)
{
	int32_t	end;
	char	quote;
	char	*tmp;

	end = i + 1;
	// either single or double quote
	quote = hold->line[i];
	while (hold->line[end] != quote)
		end++;

	// put token into linked list
	tmp = ft_substr(hold->line, i, end - i + 1);
	add_node_lex(hold, tmp);
	return (end - i);
}

/* function checks if amount of quotes is equal -> all quotes are closed
 * THROWS ERROR IF:
 *		- either amount of single or double quotes are not equal	*/
void closed_quotes(t_hold *hold)
{
	int32_t	i;
	int32_t	single_quotes;
	int32_t	double_quotes;

	i = 0;
	single_quotes = 0;
	double_quotes = 0;
	while (hold->line[i] != '\0')
	{
		if (hold->line[i] == 39)
			single_quotes++;
		else if (hold->line[i] == 34)
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		exit_status(hold, RED"minihell: syntax error: quotes are unclosed!\n"RESET, 69);
}

/* function adds pipe symbol as a new node to the 'lex_struct'
 * THROWS ERROR IF:
 *		- pipe at the very beginning of the line
 *		- more then one pipe symbol in a row (only seperated by spaces) */
void lex_pipe(t_hold *hold, int32_t i)
{
	if (i == 0)
		return (exit_status(hold, RED"minihell: syntax error near unexpected token '|'\n"RESET, 2));
	i++;
	while (hold->line[i] == ' ')
		i++;
	if (hold->line[i] == '|')
		return (exit_status(hold, RED"minihell: syntax error near unexpected token '|'\n"RESET, 2));
	add_node_lex(hold, "|");
}

/* function skips all spaces and returns new index i			*/
int32_t skip_spaces(char *str, int32_t i)
{
	while (str[i] == 32)
		i++;
	return (i);
}

/* function skips all spaces in the very beginning of 'line'
 * like this its easier to throw errors in eg. the pipe function 
 *	-> no pipe at the very beginning possible
 * If there are spaces, line gets cutted till there are no more spaces in the beginning
 * 	eg.		before: '   santi isn't real'
 * 			after:	'santi isn't real'								*/
void check_spaces(t_hold *hold)
{
	int32_t	i;
	char *tmp;

	i = skip_spaces(hold->line, 0);
	if (i == 0)
		return ;
	tmp = ft_substr(hold->line, i, ft_strlen(hold->line) - i);
	ft_memmove(hold->line, tmp, ft_strlen(hold->line) - i + 1);
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
	exit_status(hold, RED"minihell: syntax error near unexpected token 'newline'\n"RESET, 2);
    return (-1);
}

/* function adds redirection symbol(s) as a new node to the 'lex_struct'
 * THROWS ERROR IF:
 *		- redir sign at the very beginning and nothing else (except spaces)
 *		- same symbol more then 2 times in a row (eg. >>>, > > >, >> >)
 *		- in any case this syntax: '><'	(eg. ><, <><, >><)						*/
int32_t lex_redir(t_hold *hold, int32_t i)
{
	if (i == 0)
    {
		if (check_beginning_redir(hold) != 0)
            return (-1);
    }
	if (hold->line[i] == '<')
	{
		i++;
		i = skip_spaces(hold->line, i);
		if(hold->line[i] == '<')
		{
			add_node_lex(hold, "<<");
			i++;
			i = skip_spaces(hold->line, i);
			if (hold->line[i] == '<')
            {
				exit_status(hold, RED"minihell: syntax error near unexpected token '<'\n"RESET, 69);
                return (-1);
            }
			return (i-1);
		}
		add_node_lex(hold, "<");
		return (i-1);
	}
	else if (hold->line[i] == '>')
	{
		i++;
		i = skip_spaces(hold->line, i);
		if (hold->line[i] == '<')
        {
			exit_status(hold, RED"minihell: syntax error near unexpected token '<'\n"RESET, 69);
            return (-1);
        }
		if (hold->line[i] == '>')
		{
			add_node_lex(hold, ">>");
			i++;
			i = skip_spaces(hold->line, i);
			if (hold->line[i] == '>' || hold->line[i] == '<')
            {
				exit_status(hold, RED"minihell: syntax error near unexpected token '>'\n"RESET, 69);
                return (-1);
            }
			return (i-1);
		}
		add_node_lex(hold, ">");
		return (i-1);
	}
	return (69);
}

/* function adds words as a new node to 'lex_struct' 
 * 	as long as there are no:
 *		- special characters (quotes, pipe, redirection signs, $?)
 *		- spaces
 *		- newline character or null-terminator		*/
int32_t lex_word(t_hold *hold, int32_t i)
{
	int32_t	end;
	char	*tmp;

	end = i;
	while (hold->line[end] != 32 && hold->line[end] != '\0' && hold->line[end] != '\n' && hold->line[end] != 34 && hold->line[end] != 39 && hold->line[end] != '>' && hold->line[end] != '<' && hold->line[end] != '|')
	{
		if (hold->line[end] == '$' && hold->line[end + 1] == '?')
			break ;
		end++;
	}

	// put token into linked list
	tmp = ft_substr(hold->line, i, end - i);
	add_node_lex(hold, tmp);
	free(tmp);
	return (end - i - 1);
}

// devide chunks of commands etc in single linked list
void lexer(t_hold *hold)
{
	int32_t	i;
	i = 0;
	check_spaces(hold);
	closed_quotes(hold);
	while (hold->line[i] != '\0' && hold->line[i] != '\n')
	{
        if (hold->exit_code != 0)
            return ;
		if (hold->line[i] == '$' && hold->line[i + 1] == '?')
		{
			add_node_lex(hold, "$?");
			i++;
		}
		else if (hold->line[i] == 39 || hold->line[i] == 34)	//  ' or "  -> single and double quote
        {
			i += lex_quote(hold, i);
        }
		else if (hold->line[i] == '|')
        {
			lex_pipe(hold, i);
        }
		else if (hold->line[i] == '<' || hold->line[i] == '>')
        {
			i = lex_redir(hold, i);
        }
		else if (hold->line[i] != ' ')
        {
			i += lex_word(hold, i);
        }
		i++;
	}
}