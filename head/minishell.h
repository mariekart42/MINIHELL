#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

#include <sys/stat.h> // for stat function

#include <signal.h> // function fo rsignal funcs

# include <stdbool.h>	// bool

#include "../include/libft/libft.h"

// libs for readline
#include <readline/readline.h>
#include <readline/history.h>


//colour shit
# define RED   "\x1B[31m"
# define GRN   "\x1B[32m"
# define YEL   "\x1B[33m"
# define BLU   "\x1B[34m"
# define MAG   "\x1B[35m"
# define CYN   "\x1B[36m"
# define WHT   "\x1B[37m"
# define RESET "\x1B[0m"

typedef struct s_lexing
{
	char	*item;
	struct s_lexing	*next;
}		t_lexing;

typedef struct s_hold
{
	char	*line;
	struct s_lexing *lexed_list;
}				t_hold;


//		delete_later.c
void print_list(t_lexing *list, char *name);


//		utils.c
void		freeList(t_lexing* head);
void		exit_status(char *message, int32_t exit_code);
void		add_node_lex(t_hold *hold, char *content);
t_lexing	*last_node_lex(t_lexing *lst);
t_lexing	*ft_lstnew_lex(void *content);
t_lexing	*ft_lstlast_lex(t_lexing *lst);


//		lexing.c
int32_t	lex_quote(t_hold *hold, int32_t i);
void	closed_quotes(t_hold *hold);
void	lex_pipe(t_hold *hold, int32_t i);
int32_t	skip_spaces(char *str, int32_t i);
void	check_spaces(t_hold *hold);
void	check_beginning_redir(char *line);
int32_t	lex_redir(t_hold *hold, int32_t i);
int32_t	lex_word(t_hold *hold, int32_t i);
void	lexer(t_hold *hold);


#endif