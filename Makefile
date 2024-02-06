
NAME			=	minishell

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -g #-fsanitize=address,leak,undefined,
FLAGS			=	-lreadline 

VAL 			=	valgrind --leak-check=full --track-fds=yes --suppressions=valgrind.txt

VALGRIND		=	valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --track-fds=all --suppressions=valgrind.txt

SRCS            =	main.c \
					ft_getpwd.c ft_cpyarry.c lexer_utils.c lexer.c \
					change_env_var.c \
					change_env_var_utils.c input_check.c ft_handle_signals.c \
					env_conversion.c ft_export.c \
					ft_env.c ft_builtin.c ft_echo.c \
					ft_unset.c builtins_utils.c ft_cd.c \
					utils.c ft_pwd.c change_env_var_utils3.c\
					ft_main_arrycpy.c main_utils.c\
					ft_redir.c ft_redir_utils.c ft_handle_signals_utils.c\
					ft_parsing.c ft_parsing_1.c ft_parsing_2.c ft_parsing_3.c \
					ft_executor.c ft_executor_utils.c \
					utils2.c ft_heredoc_utils.c ft_heredoc_utils2.c \
					ft_exit.c ft_free_all.c ft_executor_utils2.c\
					ft_error_message.c remove_quotes.c input_check_utils.c \
					env_conversion_back.c builtins_utils2.c\
					change_env_var_hedoc.c ft_heredoc.c\
					ft_getpath_forcmd.c ft_parsing_utils.c\
					change_env_var_utils2.c input_check2.c\

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
				        $(CC) $(CFLAGS) $(OBJS) -o $(NAME) -L$(LIBFT_PATH) -lft -lreadline

$(OBJ_DIR):		
					mkdir -p $(OBJ_DIR)

clean:
						make -C $(LIBFT_PATH) clean
					    $(RM) $(OBJ_DIR)

fclean: 		    clean
						make -C $(LIBFT_PATH) fclean
				        $(RM) $(NAME)

re: 			fclean all

v:			${NAME}
				${VAL} ./${NAME}

va:			${NAME}
				${VALGRIND} ./${NAME}

r:			${NAME}
				./${NAME}

norm:		
				norminette $(SRCS) minishell.h libft libft.h | grep -v Norme -B 1 || true


.PHONY: 		all clean fclean re v va r norm libft
