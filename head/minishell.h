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

# define BUILTIN 0
# define WORD 1
# define SING_QUOTE 2
# define DOUBL_QUOTE 3
# define PIPE 4
# define SING_OPEN_REDIR 5
# define SING_CLOSE_REDIR 6
# define DOUBL_OPEN_REDIR 7
# define DOUBL_CLOSE_REDIR 8



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
	char		*item;
	int32_t		macro;
	struct s_lexing	*next;
}		t_lexing;

typedef struct s_args
{
	char	**arg_array;
	struct s_args	*next;
}				t_args;

// typedef struct s_env
// {
// 	char	*env_list;
// 	struct s_data *next;
// }				t_env;

typedef struct s_hold
{
	// char *infile;
	// char *outfile;


	char *valid_path;

	char	*line;
	int8_t	exit_code;

	struct s_env	*env_struct;
	struct s_args	*args_struct;
	struct s_lexing *lex_struct;
}				t_hold;


//		delete_later.c
char *return_macro(int32_t m);
void print_list(t_lexing *list, char *name);
void print_macro_list(t_lexing *list);
void print_args(t_hold *hold);


//		utils.c
void free_list_lex(t_lexing* head);
void free_list_arg(t_args* head);
void exit_status(t_hold *hold, char *message, int8_t exit_code_);
void		add_node_lex(t_hold *hold, char *content);
t_lexing	*last_node_lex(t_lexing *lst);
t_lexing	*ft_lstnew_lex(void *content);
t_lexing	*ft_lstlast_lex(t_lexing *lst);

void add_node_args(t_hold *hold, char **content);
t_args	*last_node_args(t_args *lst);


//		lexing.c
int32_t	lex_quote(t_hold *hold, int32_t i);
void	closed_quotes(t_hold *hold);
void	lex_pipe(t_hold *hold, int32_t i);
int32_t	skip_spaces(char *str, int32_t i);
void	check_spaces(t_hold *hold);
int32_t check_beginning_redir(t_hold *hold);
int32_t	lex_redir(t_hold *hold, int32_t i);
int32_t	lex_word(t_hold *hold, int32_t i);
void create_env_list(t_hold *hold, char **env);
void lexer(t_hold *hold, char **env);


//		parser.c
bool builtin_parser(char *node);
void recognize_type(t_hold *hold);
void parser(t_hold *hold);

//		executer.c
void init_args(t_hold *hold);
void get_path(t_hold *hold, char **env, int32_t cmd_index);
void executer(t_hold *hold, char **env);


#endif