
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

typedef struct s_fds
{
	int flag;
	int fd_in;
	int fd_out;
	char *value;
	struct s_fds *next;
}	t_fds;

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

//linked pars
typedef struct s_pars
{
	char			*cmd_path;
	char			*command;
	char			**args;
	t_lexer			*lexer;
	char			*in_file;
	char			*out_file;
	int				fd_in;
	int				fd_out;
	struct s_pars	*next;
}	t_pars;

typedef struct s_parsing
{
	char	**cmd_path;
	char	**cmd_cmd;
	char	**cmd_builtin;
	int		yon;
	char	*heredoc_delimiter;
	int 	pipes_count;
	int		command_count;
	t_lexer	lexer;
	t_fds	fds;
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
	char	**env;
	t_env	*env_list;
	char	*input;
	char	*path;
	char	*old_pwd;
	char	*pwd;
	char	*home;
	int		val;
	int		command_count;
	int		exit_status;
	int 	*pid;
	t_lexer	lexer_save;
	int		builtin_command_count;
}	t_info;

void ft_executor_pars(t_pars *pars, t_info *info);


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

// ft_simple_command.c
void ft_command_execute(t_pars *node, int numsimplecommands, t_info *info);

// ft_signals.c
void ft_signals(void);
void ft_sigquit(int signum);
void ft_sigint(int signum);

// gui.c
void print_centered(char *text);
void ft_print_minishell_gui(void);

//utils.c
void	ft_close(int fd);

// env conversion
void	env_conversion(t_info *info);
char **env_conversion_back(t_info *info);

//builtin
void	ft_builtin(t_pars *pars, t_info *info);
void	ft_export(t_info *info, char **args);
void	ft_env(t_info *info);
void	ft_echo(char **input);
void	ft_unset(t_info *info, char **args);
void	ft_cd(t_info *info, char **args);
void	ft_pwd(t_info *info);


//builtin utils
int strlcmp_export(char *str1, char *str2, int n);
void add_element(t_info *info, char *arg);
char *get_path(char *token, t_info *info);
void	update_info(t_info *info);



//parsing_right_way.c
void ft_parsing(t_pars **pars, t_lexer *tokens, t_info *info);
void free_pars_list(t_pars *head);
void ft_print_pars(t_pars *pars);


#endif
