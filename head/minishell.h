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

typedef struct s_data
{
	char	*line;
	char	*item;
	struct s_data	*lexed_line;
}		t_data;

typedef struct s_lexing
{

}
#endif