#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdlib.h>
# include <stdio.h>
# include <unistd.h> // unlink
# include <limits.h>	// for PATH_MAX macro
# include <sys/stat.h> // for stat function
# include <signal.h> // function for signal funcs
# include <stdbool.h>	// bool
# include <fcntl.h> // open function
# include <sys/types.h>

# include "../libft/libft.h"

// libs for readline
# include <readline/readline.h>
# include <readline/history.h>

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

typedef struct s_lex
{
	char			*item;
	int32_t			macro;
	struct s_lex	*next;
}					t_lex;

typedef struct s_env_exp
{
	char				*item;
	char				*var_name;
	char				*var_value;
	struct s_env_exp	*next;
}						t_env_exp;

typedef struct s_pars
{
	char			**args;
	char			*cmd_path;
	char			*here_doc_delim;
	int32_t			infile;
	int32_t			outfile;
	struct s_pars	*next;
}					t_pars;

typedef struct s_hold
{
	char				*valid_path;
	char				*env_path;
	char				**my_env;
	char				*line;
	int32_t				pipegroups;
	struct s_lex		*lex_struct;
	struct s_env_exp	*env_list;
	struct s_env_exp	*export_list;
	struct s_pars		*pars_list;
}						t_hold;

//
//! --- LEXER: ---------------------------------------------------------
//		lexer_00.c
int32_t	lex_word(t_hold *hold, char *s, int32_t i); //shit too long
void	lex_pipe(t_hold *hold, int32_t i);
void	check_closed_quotes(t_hold *hold);
void	lexer(t_hold *hold);

//		lexer_01.c
int32_t	skip_spaces(char *str, int32_t i);
int32_t	check_out_redir_syntax(t_hold **hold, int32_t i);
int32_t	check_in_redir_syntax(t_hold **hold, int32_t i);
int32_t	check_beginning_redir(t_hold *hold);
int32_t	lex_redir(t_hold *hold, int32_t i);

//		lexer_02.c
char	*init_string(char *line, char quote, int32_t i, int32_t quote_len_);
char	*handle_quote_chunk(char **string, char **quote_chunk);
int32_t	update_i(char *quote_chunk);
char	*quote_chunk2(char *line, int32_t i);

//		lexer_03.c
char	*add_letter(char *pointer, char letter);
int32_t	quote_len(char *line, int32_t i, char quote);

//
//! --- PARSER: --------------------------------------------------------
//		parser_00.c
void	sub_open_extension(t_lex	*lex, int i, t_hold *hold);
void	open_extensions(t_lex *lex, t_hold *hold);
int32_t	init_pars_node(t_pars **pars_node, t_lex **lex_node, int32_t i);
void	create_parsed_list(t_hold **hold, t_lex *lex, int32_t pipegroups);
void	parser(t_hold *hold);

//		parser_01.c
void	add_arg(t_pars *pars_node);
int32_t	arg_amount(t_lex *lex_node);
char	*ft_strnnjoin(char const *s1, int n1, char const *s2, int n2);
char	*sub_extend(char *var, t_hold *hold);
char	*extend(char *var, t_hold *hold);

//		parser_02.c
void	count_pipegroups(t_hold *hold);
void	free_env_path(char **env_path);
char	*get_cmdpath(char *curr_cmd);
t_pars	*last_node_pars(t_pars *lst);
void	add_node_pars(t_hold **hold);

//		parser_03.c
bool	builtin_parser(char *node);
void	recognize_type(t_hold *hold);
int32_t	init_outfile(t_lex *file_node, int32_t type);
int32_t	init_infile(t_pars *file_node_pars, t_lex *file_node_lex, int32_t type);

//
//! --- EXECUTER: ------------------------------------------------------







void	redir_first(t_pars *pars_node, int32_t pipe_fds[MAX_FD][2], int32_t i, int32_t pipegroups);




//		init_data.c
int32_t init_structs(t_hold **hold, char **argv, int32_t argc);
void create_env_export_list(t_hold *hold, char **ori_env);


//		free_content.c
void free_content(t_hold **hold);
void free_env_export(t_hold *hold);


//		builtins.c
void	env_builtin(t_hold *hold, t_pars *parsed_node);
void	pwd_builtin(t_hold *hold, t_pars *parsed_node);
bool	builtin(t_hold *hold, t_pars *parsed_node);



char *handle_quote_chunk(char **string, char **quote_chunk);

//		main.c
void free_content(t_hold **hold);
int32_t init_structs(t_hold **hold, char **argv, int32_t argc);
void free_env_export(t_hold *hold);


//		get_next_line.c
void	buff_after_line(char *buff);
char	*create_last(char *buff, char *line);
char	*get_next_line(int fd);


//		syntax_errors.c
int32_t check_syntax_errors(t_hold *hold);

char	*ft_strnew(const int size);
//		builtins
void	echo_builtin(t_hold *hold, t_pars *parsed_node);
void	env_builtin(t_hold *hold, t_pars *parsed_node);
void	pwd_builtin(t_hold *hold, t_pars *parsed_node);
void	cd_builtin(t_hold *hold, t_pars *parsed_node);
void	exit_builtin(t_hold *hold, t_pars *parsed_node);
void 	unset_builtin(t_hold *hold, t_pars *parsed_node);

//		cd_builtin_cont.c
void	add_to_env(t_hold *hold, char *add, char *structure);


//		unset.c
bool	find_var(t_hold *hold, char *var, char *structure);
void	delete_var(t_hold **hold, char *var, char *structure);

//		export_struct.c
void			create_env_export_list(t_hold *hold, char **ori_env);
t_env_exp	*new_node_env(void);
void			add_node_env(t_hold *hold, char *content, char *type);
void 			swap_data(t_env_exp *export_list);
void 			sort_export_list(t_hold *hold);

//		export_builtin.c
void 			export_builtin(t_hold *hold, t_pars *parsed_node);
void			add_to_export_mod(t_hold *hold, char *var_name, char *var_value, int var_class);
void			sort_export_end(t_env_exp *export_list);
void			swap_export(t_env_exp *export_list);
int				ft_isalnum_mod(int val);

//		export_builtin_cont.c
char			*ft_strndup(const char *s1, size_t n);
char			*ft_strncpy(char *dest, const char *src, size_t len);
int				ft_strcmp(char *s1, char *s2);
void			swap_export(t_env_exp *export_list);

//		signals.c
void			signals(void);
void			child_sig(void);
void			heredoc_sig(void);

//		signal_handlers.c
void			sig_handle(int sig);
void			sig_handle_child(int sig);
void			heredoc_sig_handle(int sig);



//		executer.c
void redirection(t_pars *parsed_node, int32_t i, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2]);
void open_pipefds(int32_t pipegroups, int32_t pipe_fds[MAX_FD][2]);
// void close_fds(t_pars *parsed_list, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2]);
void execute_cmd(t_pars *parsed_node, char **ori_env);
void handle_here_doc(t_pars *pars_node);
void executer(t_hold *hold, char **ori_env);
void exec_child(t_hold *hold, t_pars *pars_node, char **ori_env, int32_t pipe_fds[MAX_FD][2]);
void close_fds_child(t_hold *hold, int32_t pipegroups, int32_t pipe_fds[MAX_FD][2]);
void close_all_fds(t_pars *parsed_node, int32_t pipe_fds[MAX_FD][2], int32_t i, int32_t pipegroups);
void close_fds_parent(t_pars **parsed_node);


//		utils.c
void free_list_pars(t_pars* head);
void free_list_lex(t_lex* head);
void free_list_env_export(t_env_exp* head);
void			add_node_lex(t_hold *hold, char *content);
t_lex		*last_node_lex(t_lex *lst);
void exit_status(char *msg1, char *msg2, char *msg3, int32_t exit_code_);
void	print_error_code(void);
int	ft_isalnum_mod(int val);


// -----------------------------------------
//		delete_later.c
char *return_macro(int32_t m);
void print_list(t_lex *list, char *name);
void print_macro_list(t_lex *list);
void print_export(t_hold *hold);
void print_parsed_list(t_pars *pars);
// -----------------------------------------

#endif