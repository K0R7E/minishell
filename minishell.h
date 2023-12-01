/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:52:32 by akortvel          #+#    #+#             */
/*   Updated: 2023/12/01 11:57:43 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
# include "lexer.h"

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <readline/readline.h>
# include <readline/history.h>

# define MAX_INPUT_SIZE 1024

typedef struct s_lexer
{	
	int	command;
	int	type;
	char	*token;
	void	*next;
}	t_lexer;

typedef struct s_parsing
{
	char *cmd_path;
	int	command; //whatever this means?
	t_lexer redir;
	char **args;
	char *in_file;
	char	*out_file;
	int	fd_in;
	int	fd_out;
	int	fd_pipe[2];
}	t_parsing;


void	parser(char* input, t_info *info);
char 	*replace_dollar(char *input,  t_info *info);
char	**ft_arrycpy(char **envp);
void 	ft_echo(char *input);
void	ft_clearscreen(char *input);
//void	ft_printenv(char *input, t_info *info);
void	get_pwd(t_info *info);
void	ft_lexer(t_input *input,  t_info *info);
char	*ft_strldup(char *s, size_t len);

#endif
