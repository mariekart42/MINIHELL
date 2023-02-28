#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <limits.h>	// for PATH_MAX macro
#include <sys/stat.h> // for stat function
#include <signal.h> // function for signal funcs
# include <stdbool.h>	// bool
#include <fcntl.h> // open function

#include "../libft/libft.h"

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

typedef struct s_env_export
{
	char	 *item;
	char	*var_name;
	char	*var_value;
	struct s_env_export	*next;
}			t_env_export;

// maybe include variable with macros later here
typedef struct s_parsed_chunk
{
	char	**args;
	char	*cmd_path;
	int32_t	infile;
	int32_t	outfile;

	struct s_parsed_chunk	*next;
}			t_parsed_chunk;

typedef struct s_hold
{
	char *valid_path;
	char *env_path;

	char	*line;
	int32_t	exit_code;

	struct s_lexing *lex_struct;

	struct s_env_export	*env_list;
	struct s_env_export	*export_list;

	struct s_parsed_chunk	*parsed_list;

}				t_hold;

//		main.c
void free_content(t_hold *hold);
int32_t init_structs(t_hold **hold);
void free_env_export(t_hold *hold);


//		syntax_errors.c
int32_t check_syntax_errors(t_hold *hold);


//		builtins/builtins.c
void echo_builtin(t_parsed_chunk *parsed_node);
void env_builtin(t_hold *hold);
void pwd_builtin(t_hold *hold);
void cd_builtin(t_hold *hold);
// void exit_builtin(t_hold *hold);
// void export_builtin(t_hold *hold);
// void unset_builtin(t_hold *hold);
bool builtin(t_hold *hold, t_parsed_chunk *parsed_node);


//		builtins/export.c
void export_builtin(t_hold *hold);
void swap_data(t_env_export *export_list);
void sort_export_list(t_hold *hold);



//		lexing.c
int32_t	lex_quote(t_hold *hold, int32_t i);
void	closed_quotes(t_hold *hold);
void	lex_pipe(t_hold *hold, int32_t i);
int32_t	skip_spaces(char *str, int32_t i);
void	check_spaces(t_hold *hold);
int32_t check_beginning_redir(t_hold *hold);
int32_t	lex_redir(t_hold *hold, int32_t i);
int32_t	lex_word(t_hold *hold, int32_t i);
void lexer(t_hold *hold);



//		parser.c
bool builtin_parser(char *node);
void recognize_type(t_hold *hold);
int32_t count_pipegroups(t_lexing *lex);
int32_t check_outfile(t_hold *hold, t_lexing *file_node, int32_t type);
int32_t check_infile(t_hold *hold, t_lexing *file_node);
char *get_cmdpath(char *curr_cmd);
void create_parsed_list(t_hold **hold, t_lexing *lex);
void parser(t_hold *hold);


//		executer.c
void executer(t_hold *hold);



//		utils.c
void			free_list_lex(t_lexing* head);
void			free_list_env(t_env_export* head);
void			add_node_lex(t_hold *hold, char *content);
t_lexing		*last_node_lex(t_lexing *lst);
t_env_export	*new_node_env(void);
t_env_export	*add_node_env(t_hold *hold, char *content, char *type);
t_parsed_chunk	*last_node_pars(t_parsed_chunk *lst);
void			add_node_pars(t_hold **hold);
void			exit_status(t_hold *hold, char *message, int8_t exit_code_);
void			create_env_export_list(t_hold *hold, char **ori_env);


// -----------------------------------------
//		delete_later.c
char *return_macro(int32_t m);
void print_list(t_lexing *list, char *name);
void print_macro_list(t_lexing *list);
void print_export(t_hold *hold);
void print_parsed_list(t_parsed_chunk *pars);
// -----------------------------------------

#endif