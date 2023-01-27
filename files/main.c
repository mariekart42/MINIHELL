#include "../head/minishell.h"

void exit_status(char *message, int32_t exit_code)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}


// throw error if the amount of quotes is unequal (no interpreting of unclosed quotes)
// returns the i that gives the position after the closing quote
int32_t lex_quote(t_data *data, int32_t i_)
{
	int32_t end = i_ + 1;
	char quote;

// either single or double quote
	quote = data->line[i_];
	while (data->line[end] != quote)
		end++;
	char *chunk;
	chunk = ft_substr(data->line, i_, end - i_ + 1);
	printf(GRN"[%s]\n"RESET, chunk);
	return (end);
}


// if amount of single or double quotes are not equal, function throws error 
// -> detects unclose quotes
void illegal_syntax(t_data *data)
{
	int32_t	i = 0;
	int32_t	single_quotes = 0;
	int32_t	double_quotes = 0;
	while (data->line[i] != '\0')
	{
		if (data->line[i] == 39)
			single_quotes++;
		else if (data->line[i] == 34)
			double_quotes++;
		i++;
	}
	if (single_quotes % 2 != 0 || double_quotes % 2 != 0)
		exit_status("syntax error: quotes are unclosed!\n", 69);
}

// devide chunks of commands etc in single linked list
void lexer(t_data *data)
{
	int32_t	i = 0;

	illegal_syntax(data);
	while (data->line[i] != '\0')
	{
		// if if detectes single or double quote
		// 39 -> single quote
		// 34 -> double quote
		if (data->line[i] == 39 || data->line[i] == 34)
		{
			i += lex_quote(data, i);
		}
		printf("i: [%c]\n", data->line[i]);
		// printf("[%c]\n", data->line[i]);
		i++;

		// if it detectes space (or any whitespace? --> guess there are only spaces)
	}
}


int main(int32_t argc, char **argv)
{
	t_data data;

	// using signal function here to catch signal if eg ctr-c is used

argc++;
argv++;
	while (1)
	{
		// read content from terminal
		data.line = readline("MINIHELL> ");
		if (!data.line)
			break ;

		lexer(&data);
		
		// printf("content before history: %s\n", line);
		// if (line && *line)	// if line exist and is not empty, stuff gets saved in history list
		// 	add_history(line);
		// // parse_and_execute(line);
		// printf("content after history: %s\n", line);
		free(data.line);
		
	}
	//free(line);
}

