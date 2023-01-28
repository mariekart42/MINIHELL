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
	char	*line;
	char	*item;
	struct s_data	*next;
}		t_lexing;

typedef struct s_hold
{
	s_data *lexed_list;
}				t_hold;

#endif