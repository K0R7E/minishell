# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: akortvel <akortvel@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/09/11 09:58:37 by akortvel          #+#    #+#              #
#    Updated: 2023/10/30 13:41:15 by akortvel         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME			=	libft.a

CC				=	cc 
RM				=	rm -rf
CFLAGS			=	-Wall -Wextra -Werror -g
ARFLAGS			=	rcs
AR              =   ar

SRCS            =   ft_isalnum.c ft_isprint.c ft_memcmp.c  ft_putchar_fd.c ft_split.c \
                    ft_strlcat.c ft_strncmp.c ft_substr.c ft_atoi.c ft_isalpha.c \
                    ft_itoa.c ft_memcpy.c  ft_putendl_fd.c ft_strchr.c  ft_strlcpy.c \
                    ft_strnstr.c ft_tolower.c ft_bzero.c   ft_isascii.c \
                    ft_memmove.c ft_putnbr_fd.c  ft_strdup.c  ft_strlen.c  ft_strrchr.c \
                    ft_toupper.c ft_calloc.c  ft_isdigit.c ft_memchr.c  ft_memset.c  \
                    ft_putstr_fd.c  ft_strjoin.c ft_strmapi.c ft_strtrim.c ft_striteri.c \
                    ft_printf.c ft_putnbr_base_hex_low.c \
                    ft_putnbr_base_hex_up.c ft_putnbr_dec.c ft_putnbr_int.c \
                    ft_putpercent.c ft_putunsigned.c ft_putptr.c\
					get_next_line.c get_next_line_utils.c \


OBJ_DIR				=	obj
OBJS				=	$(SRCS:%.c=$(OBJ_DIR)/%.o)

$(OBJ_DIR)/%.o:		%.c	
								$(CC) $(CFLAGS) -c $< -o $@

all:			    $(NAME)

$(NAME): 		    $(OBJ_DIR) $(OBJS)
				        $(AR) $(ARFLAGS) $(NAME) $(OBJS)

$(OBJ_DIR):		
					mkdir -p $(OBJ_DIR)

clean:
					    $(RM) $(OBJ_DIR)

fclean: 		    clean
				        $(RM) $(NAME)

re: 			fclean all

.PHONY: 		all clean fclean re
