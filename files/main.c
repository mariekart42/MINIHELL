#include "../head/minishell.h"

void exit_status(char *message, int32_t exit_code)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

t_lexing	*ft_lstnew_lex(void *content)
{
	t_lexing	*ptr;

	ptr = (t_lexing *)malloc(sizeof(*ptr));
	if (ptr == NULL)
		return (NULL);
	ptr->item = content;
	ptr->next = NULL;
	return (ptr);
}

t_lexing	*ft_lstlast_lex(t_lexing *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
}

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
	if (hold->lexed_list == NULL)
		hold->lexed_list = ft_lstnew_lex(tmp);
	else
		(ft_lstlast_lex(hold->lexed_list))->next = ft_lstnew_lex(tmp);
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
		exit_status("syntax error: quotes are unclosed!\n", 69);
}

/* function adds pipe symbol as a new node to the 'lexed_list'
 * THROWS ERROR IF:
 *		- pipe at the very beginning of the line
 *		- more then one pipe symbol in a row (only deperated by spaces) */
void lex_pipe(t_hold *hold, int32_t i)
{
	if (i == 0)
		exit_status("syntax error near unexpected token '|'\n", 2);
	// skip all spaces
	i++;
	while (hold->line[i] == 32)
		i++;
	if (hold->line[i] == 124)
		exit_status("syntax error near unexpected token '|'\n", 2);
	// pipe token cant be at the very beginning of 'lexed_list'
	(ft_lstlast_lex(hold->lexed_list))->next = ft_lstnew_lex("|");
}

/* function skips all spaces in the very beginning of 'line'
 * like this its easier to throw errors in eg. the pipe function 
 *	-> no pipe at the very beginning possible
 * If there are spaces, line gets cutted till there are no more spaces in the beginning
 * 	eg.		before: '   santi isn't real'
 * 			after:	'santi isn't real'		*/
void skip_spaces(t_hold *hold)
{
	int32_t	i;
	char *tmp;

	i = 0;
	while (hold->line[i] == 32)
		i++;
	if (i == 0)
		return ;
	tmp = ft_substr(hold->line, i, ft_strlen(hold->line) - i);
	ft_memmove(hold->line, tmp, ft_strlen(hold->line) - i + 1);
}

// int32_t lex_redir(t_hold *hold, int32_t i)
// {
// 	while ()
// }

// devide chunks of commands etc in single linked list
void lexer(t_hold *hold)
{
	int32_t	i;

	i = 0;
	skip_spaces(hold);
	closed_quotes(hold);
	while (hold->line[i] != '\0')
	{
		if (hold->line[i] == 39 || hold->line[i] == 34)	//  ' "  -> single and double quote
			i += lex_quote(hold, i);
		else if (hold->line[i] == 124) //  |  -> pipe
			lex_pipe(hold, i);
		// else if (hold->line[i] == 60 || hold->line[i] == 62) //  < >  -> redirection signs
		// 	i += lex_redir(hold, i);
		i++;
	}
}

void print_list(t_lexing *list, char *name)
{
	printf("----------\n[%s]:\n", name);
	if(list == NULL)
	{
		printf("list_pos_1: (NULL)\n");
		return ;
	}
	int32_t i = 1;
	t_lexing *node = NULL;
	node = list;
	while (node->next != NULL)
	{
		printf("list_pos_%d: %s\n", i, node->item);
		i++;
		node = node->next;
	}
	printf("list_pos_%d: %s\n", i, node->item);
	i++;
	if(node->next == NULL)
		printf("list_pos_%d: (NULL)\n", i);
	else	
		printf("something wrong! (print_list function)\n");
	printf("-- done --\n\n");
}

void freeList(t_lexing* head)
{
   t_lexing* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }
}

int main(int32_t argc, char **argv)
{
	t_hold	*hold;

	hold = (t_hold*)malloc(sizeof(t_hold));
	if (!hold)
		return (1);

	// using signal function here to catch signal if eg ctr-c is used
argc++;
argv++;
	while (1)
	{
		// read content from terminal
		hold->line = readline("MINIHELL> ");
		if (!hold->line)
			break ;

		lexer(hold);

		print_list(hold->lexed_list, "yee");
		
		// printf("content before history: %s\n", line);
		// if (line && *line)	// if line exist and is not empty, stuff gets saved in history list
		// 	add_history(line);
		// // parse_and_execute(line);
		// printf("content after history: %s\n", line);
		freeList(hold->lexed_list);
		free(hold->line);
		break;
		
	}
	//free(line);
}

// change linked list to new struct
// reconstruct code to new struct