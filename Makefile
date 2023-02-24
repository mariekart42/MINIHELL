NAME	= minishell
CC		= gcc
CFLAGS	= -Wall -Werror -Wextra -g
# CFLAGS	= -Werror -Wall -Wextra -pthread -g -fsanitize=thread
RM		= rm -rf

SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/

LIB_F = libft
LIB = libft.a

SRC		=	main.c \
			utils.c \
			lexing.c \
			parser.c \
			executer.c \
			syntax_errors.c \
			delete_later.c \
			export.c \
			builtins.c

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS) $(LIB_F)/$(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_F)/$(LIB) -o $(NAME) -lreadline

$(LIB_F)/$(LIB):
	@make -C $(LIB_F)

clean:
	$(RM) $(OBJ_PATH)
	@make clean -C $(LIB_F)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIB_F)

re: fclean all

.PHONY: all re clean fclean
