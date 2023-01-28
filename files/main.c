#include "../head/minishell.h"

void exit_status(char *message, int32_t exit_code)
{
	write(2, message, ft_strlen(message));
	exit(exit_code);
}

t_data	*ft_lstnew_(void *content)
{
	t_data	*ptr;

	ptr = (t_data *)malloc(sizeof(*ptr));
	if (ptr == NULL)
		return (NULL);
	ptr->item = content;
	ptr->next = NULL;
	return (ptr);
}
t_data	*ft_lstlast_(t_data *lst)
{
	if (!lst)
		return (NULL);
	while (lst->next)
		lst = lst->next;
	return (lst);
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

char *chunk = ft_substr(data->line, i_, end - i_ + 1);
printf("chunk: %s\n", chunk);
	if (data->next == NULL)
		data->next = ft_lstnew_(chunk);
	else
		(ft_lstlast_(data))->next = ft_lstnew_(chunk);
	// put it into linked list
	// ft_lstlast((t_list*)data) = ft_lstnew(ft_substr(data->line, i_, end - i_ + 1));

	// printf(GRN"[%s]\n"RESET, chunk);
	return (end - i_);
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
	t_data *head = data;
	head->item = "bla";

	illegal_syntax(data);
	while (data->line[i] != '\0')
	{
		// if if detectes single or double quote
		// 39 -> single quote
		// 34 -> double quote
		if (data->line[i] == 39 || data->line[i] == 34)
			i += lex_quote(data, i);
		i++;

		// if it detectes space (or any whitespace? --> guess there are only spaces)
	}
}

void print_list(t_data *list, char *name)
{
	printf("----------\n[%s]:\n", name);
	if(list == NULL)
	{
		printf("list_pos_1: (NULL)\n");
		return ;
	}
	int32_t i = 1;
	t_data *node = NULL;
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

void freeList(t_data* head)
{
   t_data* tmp;

   while (head != NULL)
    {
       tmp = head;
       head = head->next;
       free(tmp);
    }

}

int main(int32_t argc, char **argv)
{
	t_hold	hold;

	hold = malloc(sizeof(t_hold));
	if (!hold)
		return (1);

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

		print_list(&data, "yee");
		
		// printf("content before history: %s\n", line);
		// if (line && *line)	// if line exist and is not empty, stuff gets saved in history list
		// 	add_history(line);
		// // parse_and_execute(line);
		// printf("content after history: %s\n", line);
		freeList(t_hold);
		free(data.line);
		
	}
	//free(line);
}



// change linked list to new struct
// reconstruct code to new struct