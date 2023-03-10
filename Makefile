NAME	= minishell
CC		= cc
CFLAGS	= -Wall -Werror -Wextra -g
# CFLAGS	=  -fsanitize=address
RM		= rm -rf

SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/

LIB_F = libft
LIB = libft.a

SRC		=	main.c \
			utils.c \
			export_struct.c \
			lexing.c \
			parser.c \
			executer.c \
			syntax_errors.c \
			delete_later.c \
			builtins.c \
			cd_builtin.c \
			cd_builtin_cont.c \
			echo_builtin.c \
			exit_builtin.c \
			unset_builtin.c \
			export_builtin.c

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
	@make bonus -C $(LIB_F)

clean:
	$(RM) $(OBJ_PATH)
	@make clean -C $(LIB_F)

fclean: clean
	$(RM) $(NAME)
	@make fclean -C $(LIB_F)

re: fclean all

.PHONY: all re clean fclean
