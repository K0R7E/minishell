
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

# define R "\033[0;31m"
# define G "\033[0;32m"
# define Y "\033[0;33m"
# define LIME "\033[1;32m"
# define OFF "\033[0m"

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
	int				hd_quote;
	char			*token;
	struct s_lexer	*next;
}	t_lexer;

//for lexer
typedef struct s_lexer_pos
{	
	int i;
	int command_number;
	int hedoc;
}	t_lexer_pos;

typedef struct s_parsing
{
	char	**cmd_cmd;
	char	**cmd_builtin;
	int		yon;
	char	*heredoc_delimiter;
	int 	pipes_count;
	int		command_count;
	t_lexer	lexer;
	char	**args;
	char	*in_file;
	char	*out_file;
	int		fd_in;
	int		fd_out;
	int		fd_pipe[2];
	char 	*check_cmd[7];
}	t_parsing;

typedef struct s_env
{	
	int 			printed;
	char 			*var;
	char			*value;
	struct s_env	*next;
}	t_env;
typedef struct s_info
{
	char **env;
	t_env *env_list;
	char *input;
	char *path;
	char *old_pwd;
	char *pwd;
	char *home;
	t_lexer	lexer_save;
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

// ft_heredoc.c
void ft_heredoc(t_parsing *pars, t_info *info);

// ft_executor.c
void ft_executor(t_parsing *pars, t_info *info);
int ft_arrylen(char **pars);
void ft_execute(char *args[], int input_fd, int output_fd);
int ft_count_pipes(t_parsing *pars);

// ft_signals.c
void ft_signals(void);
void ft_sigquit(int signum);
void ft_sigint(int signum);

// gui.c
void print_centered(char *text);
void ft_print_minishell_gui(void);

//ft_pipe.c
void ft_pipe(t_parsing *pars, t_info *info);

// env conversion
void	env_conversion(t_info *info);

//builtin
void	ft_builtin(t_parsing *pars, t_info *info);
void	ft_export(t_info *info, char **args);
void	ft_env(t_info *info);
void	ft_echo(int mode, char **input);

#endif
