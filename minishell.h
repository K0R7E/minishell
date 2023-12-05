
#ifndef MINISHELL_H
# define MINISHELL_H

# include "libft/libft.h"
//# include "lexer.h"

# include <stdio.h>
# include <stddef.h>
# include <stdlib.h>
# include <string.h>
# include <signal.h>
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
	int command_number;
}	t_lexer_pos;

typedef struct s_parsing
{
	char	**cmd_path;
	char	**cmd_builtin;
	int		yon;
	char	*heredoc_delimiter;
	t_lexer	lexer;
	char	**args;
	char	*in_file;
	char	*out_file;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	char 	*check_cmd[7];
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


// main.c
void ft_get_input(t_info *info);

// ft_cpyarray.c
char	**ft_arrycpy(char **envp);

// ft_getpwd.c
void 	get_pwd(t_info *info);

// parsing.c
void ft_parser(t_lexer *tokens, t_parsing *pars, t_info *info);
void free_parsing(t_parsing *pars);
//void print_tokens(t_lexer *tokens);

//input check
int	ft_check_input(t_info *info);

// lexer.c
void	ft_lexer(t_info *info, t_parsing *list);
char *ft_strldup(char *s, size_t len);
int	ft_strchr2(char *s, int c);

// $ variable conversion
char *replace_dollar(char *input,  t_info *info);
char	*add_char_to_str(char *str, char c);
char *ft_strjoin2(char *str, char *add);

// ft_execution.c
void ft_heredoc(t_parsing *pars, t_info *info);
void ft_executor(t_parsing *pars, t_info *info);

// ft_signals.c
void ft_signals(void);
void ft_sigquit(int signum);
void ft_sigint(int signum);


#endif
