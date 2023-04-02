NAME	= minishell
CC		= cc
CFLAGS	= -Wextra -Wall -Werror -g
# DEBUG	=  -fsanitize=address
RM		= rm -rf
SRC_PATH = src/
OBJ_PATH = obj/
INC_PATH = inc/

LIB_F = libft
LIB = libft.a

SRC		=	main.c \
			utils.c \
			utils_cont.c \
			executer_00.c \
			executer_01.c \
			executer_02.c \
			init_data.c \
			export_struct.c \
			export_struct_cont.c \
			free_content.c \
			free_content_cont.c \
			syntax_errors.c \
			delete_later.c \
			$(addprefix lexing/,\
			lexer_00.c \
			lexer_01.c \
			lexer_02.c \
			lexer_03.c) \
			$(addprefix parsing/,\
			parser_00.c \
			parser_01.c \
			parser_02.c \
			parser_03.c) \
			$(addprefix builtins/,\
			builtins.c \
			cd_builtin.c \
			cd_builtin_cont.c \
			echo_builtin.c \
			exit_builtin.c \
			unset_builtin.c \
			export_builtin.c \
			export_builtin_cont.c \
			export_builtin_utils.c \
			export_builtin_utils_cont.c) \
			$(addprefix signals/,\
			signals.c \
			signal_handlers.c)

SRCS	= $(addprefix $(SRC_PATH), $(SRC))
OBJ		= $(SRC:.c=.o)
OBJS	= $(addprefix $(OBJ_PATH), $(OBJ))
INC		= -I $(INC_PATH)

all: $(NAME)

$(OBJ_PATH)%.o: $(SRC_PATH)%.c
	@mkdir -p $(OBJ_PATH)
	@mkdir -p obj/signals obj/builtins obj/parsing obj/lexing
	$(CC) $(CFLAGS) -c $< -o $@ $(INC)

$(NAME): $(OBJS) $(LIB_F)/$(LIB)
	@$(CC) $(CFLAGS) $(OBJS) $(LIB_F)/$(LIB) $(DEBUG) -o $(NAME) -lreadline

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
