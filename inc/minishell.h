#ifndef MINISHELL_H
#define MINISHELL_H

#include <stdlib.h>
#include <stdio.h>
#include <unistd.h> // unlink
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
# define SING_OPEN_REDIR 5		// <
# define SING_CLOSE_REDIR 6		// >
# define DOUBL_OPEN_REDIR 7		// << heredoc
# define DOUBL_CLOSE_REDIR 8	// >>

# define MAX_FD 1024

int32_t error_code;

// get_next_line
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4096
# endif



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

// typedef struct s_here_doc
// {
// 	char	*delim;
// 	bool	is_here_doc;
// }				t_here_doc;

// maybe include variable with macros later here
typedef struct s_parsed_chunk
{
	char	**args;
	char	*cmd_path;
	int32_t	infile;
	int32_t	outfile;
	char *here_doc_delim;
	// struct s_here_doc		access;
	struct s_parsed_chunk	*next;
}			t_parsed_chunk;

typedef struct s_hold
{
	char *valid_path;
	char *env_path;

	char	**my_env;

	char	*line;
	// int32_t	exit_code;

	struct s_lexing *lex_struct;

	struct s_env_export	*env_list;
	struct s_env_export	*export_list;

	struct s_parsed_chunk	*parsed_list;

}				t_hold;

//		main.c
void free_content(t_hold **hold);
int32_t init_structs(t_hold **hold);
void free_env_export(t_hold *hold);


//		get_next_line.c
void	buff_after_line(char *buff);
char	*create_last(char *buff, char *line);
char	*get_next_line(int fd);


//		syntax_errors.c
int32_t check_syntax_errors(t_hold *hold);


//		builtins
void	echo_builtin(t_parsed_chunk *parsed_node);
void	env_builtin(t_hold *hold);
void	pwd_builtin(t_hold *hold);
void	cd_builtin(t_hold *hold, t_parsed_chunk *parsed_node);
void	exit_builtin(t_parsed_chunk *parsed_node);
void 	unset_builtin(t_hold *hold, t_parsed_chunk *parsed_node);
bool 	builtin(t_hold *hold, t_parsed_chunk *parsed_node);

//		cd_builtin_cont.c
void	add_to_env(t_hold *hold, char *add, char *structure);
void	update_env(t_hold *hold, char *old, char *new, char *structure);
void	add_to_var(t_hold *hold, char *add, char *structure);
void	update_var_value(t_hold *hold, char *old, char *new, char *structure);

//		unset.c
bool	find_var(t_hold *hold, char *var, char *structure);
void	delete_var(t_hold **hold, char *var, char *structure);

//		export_struct.c
void			create_env_export_list(t_hold *hold, char **ori_env);
t_env_export	*new_node_env(void);
void			add_node_env(t_hold *hold, char *content, char *type);
void 			swap_data(t_env_export *export_list);
void 			sort_export_list(t_hold *hold);

//		export_builtin.c
void 			export_builtin(t_hold *hold, t_parsed_chunk *parsed_node);

//		export_builtin_cont.c
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strncpy(char *dest, const char *src, size_t len);

//		signals.c
void			signals(void);
void			child_sig(void);
void			heredoc_sig(void);

//		signal_handlers.c
void			sig_handle(int sig);
void			sig_handle_child(int sig);
void			heredoc_sig_handle(int sig);

//		lexing.c
// int32_t	lex_quote(t_hold *hold, int32_t i);
// char *calloc_string(t_hold *hold, int32_t i);
// int32_t new_lex_quote(t_hold *hold, int32_t i);
// void	closed_quotes(t_hold *hold);
void	lex_pipe(t_hold *hold, int32_t i);
int32_t	skip_spaces(char *str, int32_t i);
// void	check_spaces(t_hold *hold);
int32_t check_beginning_redir(t_hold *hold);
int32_t	lex_redir(t_hold *hold, int32_t i);
// int32_t	lex_word(t_hold *hold, int32_t i);
char *quote_chunk(t_hold *hold, int32_t i, int32_t len);
char *add_letter(char *pointer, char letter);
// void prep_line(t_hold *hold);
void lexer(t_hold *hold);

// char *cut_string(char *line, int32_t start, int32_t end);
// int32_t lex_WORD(t_hold *hold, char *line, int32_t i);

// new lex
char *quote_chunk2(char *line, int32_t i);
int32_t lex_word(t_hold *hold, char *line, int32_t i);
void check_closed_quotes(t_hold *hold);


//		parser.c
bool builtin_parser(char *node);
void recognize_type(t_hold *hold);
int32_t count_pipegroups(t_lexing *lex);
int32_t init_outfile(t_lexing *file_node, int32_t type);
int32_t init_infile(t_parsed_chunk *file_node_pars, t_lexing *file_node_lex, int32_t type);
char *get_cmdpath(char *curr_cmd);
void create_parsed_list(t_hold **hold, t_lexing *lex, int32_t pipegroups);
void			add_node_pars(t_hold **hold);
t_parsed_chunk	*last_node_pars(t_parsed_chunk *lst);
int32_t arg_amount(t_lexing *lex_node);
void parser(t_hold *hold);


//		executer.c
void redirection(t_parsed_chunk *parsed_node, int32_t i, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2]);
void open_pipefds(int32_t pipegroups, int32_t pipe_fds[MAX_FD][2]);
// void close_fds(t_parsed_chunk *parsed_list, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2]);
void execute_cmd(t_parsed_chunk *parsed_node, char **ori_env);
void handle_here_doc(t_parsed_chunk *pars_node);
void executer(t_hold *hold, char **ori_env);

void close_fds(t_hold *hold, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2]);
void close_all_fds(t_parsed_chunk *parsed_node, int32_t pipe_fds[MAX_FD][2], int32_t i, int32_t pipegroups);

//		utils.c
void free_list_pars(t_parsed_chunk* head);
void free_list_lex(t_lexing* head);
void free_list_env_export(t_env_export* head);
void			add_node_lex(t_hold *hold, char *content);
t_lexing		*last_node_lex(t_lexing *lst);
void exit_status(char *message, int8_t exit_code_);


// -----------------------------------------
//		delete_later.c
char *return_macro(int32_t m);
void print_list(t_lexing *list, char *name);
void print_macro_list(t_lexing *list);
void print_export(t_hold *hold);
void print_parsed_list(t_parsed_chunk *pars);
// -----------------------------------------

#endif