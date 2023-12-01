# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: fstark <fstark@student.42.fr>              +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/11/25 18:54:43 by akortvel          #+#    #+#              #
#    Updated: 2023/12/01 11:58:41 by fstark           ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	minishell

CC				=	cc
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -g
FLAGS			=	-lreadline 
SRCS            =	main.c lexer.c change_env_var.c parser.c ft_utils.c

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
