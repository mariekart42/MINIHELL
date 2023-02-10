NAME= minishell.a

CC = gcc
CFLAGS= -Wall -Werror -Wextra -g
# -fsanitize=thread
HEADER= minishell.h
RM= rm -rf
NAME = minishell
#DEBUG = -fsanitize=address

LIBFT= include/libft/libft.a

FILES=	files/main.c \
		files/utils.c \
		files/lexing.c \
		files/parser.c \
		files/executer.c \
		files/delete_later.c

O_FILES= $(FILES:%.c=%.o)

all: $(NAME)

$(NAME): $(O_FILES)
	$(MAKE) -C include/libft
	$(CC) $(CFLAGS) $(DEBUG) $(O_FILES) $(LIBFT) -lreadline -o $(NAME)

clean:
	$(MAKE) clean -C include/libft
	$(RM) $(O_FILES)
	
fclean: clean
	$(MAKE) fclean -C include/libft
	$(RM) $(NAME)
	
re: fclean all

.PHONY: all clean fclean re