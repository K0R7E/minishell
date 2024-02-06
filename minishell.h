/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:39:43 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/06 11:22:56 by akortvel         ###   ########.fr       */
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
# include <signal.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <fcntl.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <errno.h>

# define SIGINT  2
# define SIGQUIT 3 

# define R "\033[0;31m"
# define G "\033[0;32m"
# define Y "\033[0;33m"
# define LIME "\033[1;32m"
# define OFF "\033[0m"

// Token types
enum
{
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
	int				flag;
	int				fd_in;
	int				fd_out;
	char			*value;
	struct s_fds	*next;
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
	int	i;
	int	command_number;
	int	hedoc;
}	t_lexer_pos;

typedef struct quote_state
{
	int	state_s;
	int	state_d;
}	t_quote_state;

//linked pars
typedef struct s_pars
{
	char			*cmd_path;
	char			*command;
	char			**args;
	char			**cmd_args;
	//t_lexer			*lexer;
	char			*in_file;
	char			*out_file;
	int				fd_in;
	int				fd_out;
	char			*heredoc;
	struct s_pars	*next;
	//struct s_pars	*prev;
}	t_pars;

typedef struct s_env
{
	int				printed;
	char			*var;
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
	int		hd_quote;
	int		val;
	int		command_count;
	int		exit_status;
	int		exit_code;
	//int 	*pid;	
	t_lexer	*lexer;
	int		builtin_command_count;
	t_pars	**pars_ptr;
	int		i;
	int		flag;
	int		in_cmd;
	int		in_hd;
	int		stop_hd;
}	t_info;

extern int	g_info;

/*##########################################################*/
/*#####################  FUNCTIONS  ########################*/
/*##########################################################*/

void	ft_print_pars(t_pars *pars);

void	ft_executor_pars(t_pars *pars, t_info *info);
int		ft_listsize(t_pars *pars);

char	**ft_arrycpy_main(char **envp, t_info *info);

// main.c
void	ft_get_input(t_info *info);

// ft_cpyarray.c
char	**ft_arrycpy(char **envp);
void	ft_free_array(char **arr);

// ft_getpwd.c
void	get_pwd(t_info *info);

//main_utils.c
void	ft_1(t_info *info, t_pars *pars);
void	ft_args(char **argv, int argc);
void	init_loop(t_pars *pars, t_info *info);

//input check.c
int		ft_check_input(t_info *info);
int		check_empty(t_info *info);

//input check_utils.c
int		check_if_allowed(int newer, int last, t_info *info, int i);
int		ft_find_last_redirect(t_info *info, int i);
int		ft_handle_redirect_length(t_info *info, int i);

// lexer.c
void	ft_lexer(t_info *info);
void	remove_quotes_from_parsing_list(t_pars *pars, t_info *info);
char	*ft_strldup(char *s, size_t len);
int		ft_strchr_lexer(char *s, int c);

// $ variable conversion
char	*replace_dollar(char *input, t_info *info);
char	*add_char_to_str(char *str, char c);
char	*ft_strjoin2(char *str, char *add);
char	*replace_dollar_hedoc(char *input, t_info *info);
char	*handle_char(char *res, char *input, t_info *info);
char	*handle_dollar_sign(t_info *info, char *res, int i, char *input);
char	*handle_question_mark(t_info *info, char *res);
char	*handle_hedoc(char *res, char *input, t_info *info);
int		hedoc_length(t_info *info, int i);
char	*check_hedoc(char *in, t_info *info, int i);
char	*copy_env_value(int j, t_info *info);
int		give_env_variable_pos(char *input, int i, t_info *info, int mode);
int		update_quote_state2(t_quote_state qs, char c);
char	*slash_rem(char *in, t_info *info, char *res);
int		slash(char *str, t_info *info);
void	ft_check_qoutes_in_repdollar(t_info *info, t_quote_state *qs);
char	*ft_dollar_check(char *res, t_info *info, t_quote_state *qs, char *in);

// remove quotes
char	*remove_quotes(char *str);

// ft_signals.c
/* void	sigint_handler(int sig);
void	sigquit_handler(int sig);
void	init_signals(void); */
int		ft_strcmp_123(const char *s1, const char *s2);

// signal_new.c
void	ignore_sigquit(void);
void	set_signals_interactive(void);
void	set_signals_noninteractive(void);

//utils.c
void	ft_close(int fd);
void	ft_error_message(t_pars *pars, t_info *info);
int		update_quote_state(int i);
void	ft_3(char *first, char *second, char *third);
int		ft_strncmp_12(const char *s1, const char *s2, size_t n);
int		ft_strncmp_12hd(const char *s1, const char *s2, size_t n);
int		change_one_zero(int i);

// env conversion
void	env_conversion(t_info *info, t_pars *pars, char **envp);
char	**env_conversion_back(t_info *info);

//builtin
int		ft_builtin(t_pars *pars, t_info *info);
int		ft_export(t_info *info, char **args);
int		ft_env(t_info *info);
int		ft_echo(char **input);
int		ft_unset(t_info *info, char **args);
int		ft_cd(t_info *info, char **args);
int		ft_pwd(t_info *info);
int		ft_exit(t_info *info, char **input);
int		ft_strncmp2(char *s1, char *s2, int n);

//ft_check_input.c
int		ft_check_input(t_info *info);

//builtin utils
int		strlcmp_export(char *str1, char *str2, int n);
void	add_element(t_info *info, char *arg);
char	*get_path(char *token, t_info *info);
void	update_info(t_info *info);
int		is_valid_env(char *env);
void	update_pwd(t_info *info, char *path);

//ft_free_all.c
void	ft_free_all(t_pars *pars, t_info *info, int flag);

/*##########################################################*/
/*###################  AKORTVEL-DONE  ######################*/
/*##########################################################*/

//ft_getpath_forcmd.c
char	*get_path_new(t_pars *pars, char *token, t_info *info);

//ft_heredoc.c
int		ft_redir_heredoc(t_pars *pars, t_info *info, int i, int count);
int		hd_loop(t_pars *pars, t_info *info, int i, int fd);
char	*remove_newline(char *line, char *input);
char	*add_line(char *input);
int		ft_delimiter(char *delim, char *line);

//ft_heredoc_utils.c
int		ft_check_qoutes(char *str);
int		ft_check_newline(t_pars *pars, char *str, int j);
void	free_hd(char *line, char *str);
char	*ft_str_123(t_pars *pars, t_info *info, char *str, char *line);
int		hd_err_ex(int fd);

//ft_heredoc_utils_2.c
void	hd_error_msg(char *msg);
int		ft_check_stop_hd(t_info *info, char *line, int fd);
char	*ft_hd_str_01(t_pars *pars, t_info *info, char *str, char *line);
int		ft_check_empty_line(char *str, char *input);
int		ft_check_hd(t_info *info, char *input);

// ft_redir.c
int		ft_redir(t_pars *pars, t_info *info);
int		ft_handle_redirection(t_pars *tmp, t_info *info);
void	ft_redir_output_app(t_pars *pars, t_info *info, int i, int count);
void	ft_redir_output(t_pars *pars, t_info *info, int i, int count);
void	ft_redir_input(t_pars *pars, t_info *info, int i, int count);

//ft_redir_utils.c
int		ft_check_num(char **str, char *c);

//ft_parsing.c
int		ft_parsing(t_pars **pars, t_lexer *tokens, t_info *info);
void	add_pars_node(t_pars *pars, t_pars **head, t_lexer *tmp, t_info *info);
t_pars	*node_for_word(t_pars *pars, t_lexer *tmp, t_info *info);
void	proc_spec(t_pars *node, t_pars *pars, t_lexer *tmp, t_info *info);
void	fill_args(t_pars *node, t_lexer *tmp1, t_info *info, t_pars *pars);

//ft_parsing_1.c
void	free_argsnode(t_pars *node);
void	free_cmdnode(t_pars *node);
void	ft_free_node(t_pars *node);
char	**calloc_cmd(char **args, t_pars *pars, t_info *info);
int		should_skip_arg(char *arg);

//ft_parsing_2.c
void	initialize_node_files(t_pars *node);
void	check_null(t_pars *node, t_pars *pars, t_info *info);
int		iterate_lexer_tokens(t_lexer *tmp, t_pars *node);
void	set_c_p(t_pars *node, t_lexer *tmp, t_pars *pars, t_info *info);
void	init_node(t_pars *node);

//ft_parsing_3.c
t_pars	*allocate_node(t_pars *pars, t_info *info, int arg_size);
void	hand_all_fail(char **tmp, char **args, t_pars *pars, t_info *info);
char	**ft_add_cmd_args(char **args, t_pars *pars, t_info *info);

//ft_parsing_utils.c
int		ft_check_word_type(t_pars *pars, t_lexer *tokens, t_info *info);
int		is_next_args(t_lexer *tokens);
int		ft_lstsize(t_lexer *tokens);
char	*convert_to_cmd(char *str, t_info *info);

//ft_executor.c
void	handle_execve_error(char *command, char **env, char *path);
void	handle_child_process(t_pars *tmp, t_info *info, int fd_in, int fd_out);
void	handle_parent_proc(pid_t pid, t_info *info, int fd_in, int fd_out);
void	ft_fork(t_pars *tmp, t_info *info, int fd_in, int fd_out);
void	ft_executor(t_pars *pars, t_info *info, int fd_in, int fd_out);

//ft_executor_utils.c
int		is_builtin_1(char *command);
int		is_builtin_2(char *command);
void	setup_fd(int fd, int std_no);
void	setup_file_fd(int file_fd, char *file, int fd, int std_no);
int		is_builtin(char *command, char **cmd_args);

//ft_executor_utils2.c
void	close_fds_from_list(int in, int out, int ft_pip, int fd_in);
void	setup_fd_2(int fd_out, int fd_pipe[2]);
int		should_move_to_next(t_pars *tmp);

//handle_signals.c
void	config_signals(void);
//void	handle_sig(int sig, t_info *info);
t_info	*handle_sig(int sig, t_info *info);
void	sigquit_handler(int sig);

// handle_signals_utils.c
void	handle_cmd_sig(t_info *info);
void	handle_hd_sig(t_info *info);
void	handle_default_sig(t_info *info);

int		ft_listsize(t_pars *pars);
void	ft_init_values(t_info *info);
void	ft_shit(int tmp_fd_in);

#endif
