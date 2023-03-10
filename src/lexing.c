#include "minishell.h"

// throw error if the amount of quotes is unequal (no interpreting of unclosed quotes)
// returns the i that gives the position after the closing quote
// int32_t lex_quote(t_hold *hold, int32_t i)
// {
// 	int32_t	end;
// 	char	quote;
// 	char	*tmp;

// 	end = i + 1;
// 	// either single or double quote
// 	quote = hold->line[i];
// 	while (hold->line[end] != quote)
// 		end++;

// 	// put token into linked list
// 	tmp = ft_substr(hold->line, i, end - i + 1);
// 	add_node_lex(hold, tmp);
// 	return (end - i);
// }

// char *calloc_string(t_hold *hold, int32_t i)
// {
// 	int32_t len;
// 	char *return_string;

// 	len = 0;
// 	while (hold->line[i] != '\0')
// 	{
// 		len++;
// 		i++;
// 	}
// 	return_string = (char*)ft_calloc(len + 1, 1);
// 	if (!return_string)
// 	{
// 		exit_status(hold, RED"Error! Failed to malloc for sring in calloc_string()\n"RESET, 69);
// 		exit(69);
// 	}
// 	return (return_string);
// }

// int32_t new_lex_quote(t_hold *hold, int32_t i)
// {
// 	char first_quote;
// 	char *string;
// 	int32_t x;

// 	x = 0;
// 	string = calloc_string(hold, i);
// 	while (hold->line[i] != '\0')
// 	{
// 		first_quote = hold->line[i];
// 		i++;
// 		while (hold->line[i] != first_quote)
// 		{
// 			if (hold->line[i] == '\0')
// 			{
// 				exit_status(hold, "minihell: syntax error: quotes are unclosed!\n", 69);
// 				return(-1);
// 			}
// 			string[x] = hold->line[i];
// 			x++;
// 			i++;
// 		}
// 		if (hold->line[i + 1] != ' ' && hold->line[i + 1] != '\t')
// 			break;
// 		while (hold->line[i+1] == ' ' || hold->line[i+1] == '\t')
// 			i++;
// 		i++;
// 	}
// 	add_node_lex(hold, string);
// 	return (x + 1);

// }

/* function checks if amount of quotes is equal -> all quotes are closed
 * THROWS ERROR IF:
 *		- either amount of single or double quotes are not equal	*/
// void closed_quotes(t_hold *hold)
// {
// 	int32_t	i;
// 	int32_t	single_quotes;
// 	int32_t	double_quotes;

// 	i = 0;
// 	single_quotes = 0;
// 	double_quotes = 0;
// 	while (hold->line[i] != '\0')
// 	{
// 		if (hold->line[i] == 39)
// 			single_quotes++;
// 		else if (hold->line[i] == 34)
// 			double_quotes++;
// 		i++;
// 	}
// 	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
// 		exit_status(hold, RED"minihell: syntax error: quotes are unclosed!\n"RESET, 69);
// }

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
// void check_spaces(t_hold *hold)
// {
// 	int32_t	i;
// 	char *tmp;

// 	i = skip_spaces(hold->line, 0);
// 	if (i == 0)
// 		return ;
// 	tmp = ft_substr(hold->line, i, ft_strlen(hold->line) - i);
// 	ft_memmove(hold->line, tmp, ft_strlen(hold->line) - i + 1);
// }

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
	while (hold->line[end] != '\0' && hold->line[end] != '\n' && hold->line[end] != '>' && hold->line[end] != '<' && hold->line[end] != '|')
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

char *quote_chunk(char *line, int32_t i, int32_t len)
{
	char open_quote;
	// int32_t other_quote;
	int32_t x;
	char *quote_chunk_;

	open_quote = line[i];
	// other_quote = 0;
	x = 0;
	quote_chunk_ = (char*)ft_calloc(len, 1);
	i++;
	while (line[i] != '\0')
	{
		if (line[i] == open_quote)
		{
			// if ((other_quote % 2) != 0)
			// 	break ;
			return (quote_chunk_);
		}
		// if ((line[i] == 34 || line[i] == 39) && line[i] != open_quote)
		// {
		// 	other_quote++;
		// }
		quote_chunk_[x] = line[i];
		i++;
		x++;
	}
	ft_putstr_fd(RED"minihell: syntax error: quotes are unclosed!\n"RESET, 69);
	return (NULL);
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
	return (return_pointer);
}

// skip useless spaces
// deal with quotes
void prep_line(t_hold *hold)
{
	char *pointer;
	char *tmp;
	char *check_tmp;
	int32_t i =0;

	while (hold->line[i] == ' ' || hold->line[i] == '\t')
		i++;
	pointer = (char *)malloc(1);
	pointer[0] = '\0';
	while (hold->line[i] != '\0')
	{
		if (hold->line[i] == ' ' || hold->line[i] == '\t')
		{
			while (hold->line[i] == ' ' || hold->line[i] == '\t')
				i++;
			pointer = add_letter(pointer, ' ');
		}
		if (hold->line[i] == 39 || hold->line[i] == 34)
		{
			check_tmp = quote_chunk(hold->line, i, ft_strlen(hold->line) - i + 1);
			if (!check_tmp)
				return (exit_status(hold, RED"minihell: syntax error: quotes are unclosed!\n"RESET, 69));
			if (ft_strlen(check_tmp) == 0)
				i+=1;
			else
			{
				tmp = ft_strjoin(pointer, check_tmp);
				free(pointer);
				i += ft_strlen(check_tmp) + 1;
				char check;
				check = hold->line[i];
				char check2;
				check2 = hold->line[i+1];

				free(check_tmp);
				check_tmp = NULL;
				pointer = ft_strdup(tmp);
				free(tmp);
				tmp = NULL;
			}
		}
		else
			pointer = add_letter(pointer, hold->line[i]);
		i++;
	}
	free(hold->line);
	hold->line = ft_strdup(pointer);
	free(pointer);
}

int32_t QUOTES(char *line)
{
	
}

// devide chunks of commands etc in single linked list
void lexer(t_hold *hold)
{
	int32_t	i;
	i = 0;
	// check_spaces(hold);
	// closed_quotes(hold);
	prep_line(hold);
	// return;
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
			i += QUOTES(hold, i);
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