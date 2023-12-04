/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/25 18:52:32 by akortvel          #+#    #+#             */
/*   Updated: 2023/12/04 14:31:04 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
//# include "lexer.h"

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

// Token types
enum {
    TokenTypeWord = 1,
    TokenTypeOutputRedirect = 2,
    TokenTypeInputRedirect = 3,
    TokenTypeOutputAppend = 4,
    TokenTypeHeredoc = 5,
    TokenTypePipe = 6,
	TokenTypeEnd = 7,
	TokenTypeDelimiter = 8,
};

typedef struct s_lexer
{	
	int				command;
	int				type;
	char			*token;
	struct s_lexer	*next;
}	t_lexer;

typedef struct s_lexer_pos
{	
	int i;
}	t_lexer_pos;

typedef struct s_parsing
{
	char	*cmd_path;
	int		command; //whatever this means?
	t_lexer	*lexer;
	char	**args;
	char	*in_file;
	char	*out_file;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	char 	**check_cmd;
}	t_parsing;

typedef struct s_info
{
	char **env;
	t_lexer *lexer;
	char *input;
	char *path;
	char *old_pwd;
	char *pwd;
	char *home;
}	t_info;


/* void	parser(char* input, t_info *info);
char 	*replace_dollar(char *input,  t_info *info); */
char	**ft_arrycpy(char **envp);
/* void	ft_clearscreen(char *input); */
//void	ft_printenv(char *input, t_info *info);
void 	get_pwd(t_info *info);
//void	ft_lexer(t_input *input,  t_info *info);
/* char	*ft_strldup(char *s, size_t len); */


#endif
