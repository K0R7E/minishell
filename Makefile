
NAME			=	minishell

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -g
FLAGS			=	-lreadline 

SRCS            =	main.c \
					ft_getpwd.c ft_cpyarry.c lexer_utils.c lexer.c \
					parsing.c ft_executor.c change_env_var.c \
					change_env_var_utils.c input_check.c ft_signals.c \
					gui.c ft_heredoc.c env_conversion.c ft_export.c \
					ft_env.c ft_builtin.c ft_echo.c\
					ft_unset.c builtins_utils.c ft_cd.c #ft_pipe.c 

OBJ_DIR				=	obj
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

LIBFT_PATH			= 	./libft
LIBFT				= 	$(LIBFT_PATH)/libft.a

$(OBJ_DIR)/%.o:		%.c	
								$(CC) $(CFLAGS) -c $< -o $@

all:			    $(NAME)

$(LIBFT):		
						make -C $(LIBFT_PATH) all

$(NAME): 		    $(LIBFT) $(OBJ_DIR) $(OBJS)
						cp	$(LIBFT) $(NAME)
				        $(CC) $(CFLAGS) $(FLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_PATH) -lft

$(OBJ_DIR):		
					mkdir -p $(OBJ_DIR)

clean:
						make -C $(LIBFT_PATH) clean
					    $(RM) $(OBJ_DIR)

fclean: 		    clean
						make -C $(LIBFT_PATH) fclean
				        $(RM) $(NAME)

re: 			fclean all

run:			${NAME}
				${VALGRIND} ./${NAME} map.ber

.PHONY: 		all clean fclean re run libft
