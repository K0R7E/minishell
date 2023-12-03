#include "minishell.h"

void ft_parser(t_info *info, t_parsing *pars, t_lexer *lexer)
{
	int i = 0;
	int j = 0;

	while (lexer->next)
	{
		if (lexer->type == 1)
		{
			pars->args[j] = ft_strdup(lexer->token);
			printf("args: %s\n", pars->args[j]);
		}
		else if (lexer->type == 2)
		{
			pars->in_file = ft_strdup(lexer->token);
			pars->fd_in = open(pars->in_file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
			printf("redir_in: %s\n", pars->in_file);
		}
		else if (lexer->type == 3)
		{
			pars->out_file = ft_strdup(lexer->token);
			pars->fd_out = open(pars->out_file, O_RDONLY);
			printf("redir_out: %s\n", pars->out_file);
		}
		else if (lexer->type == 4)
		{
			pars->in_file = ft_strdup(lexer->token);
			printf("recir_append: %s\n", pars->in_file); // should redirect output in append mode.
		}
		else if (lexer->type == 5)
		{
			pars->out_file = ft_strdup(lexer->token);
			printf("heredoc: %s\n", pars->out_file); // heredoc + delimiter
		}
		lexer = lexer->next;
	}
}


int main(int argc, char **argv, char **envp)
{
	t_info *info;
	t_parsing *pars;

	info = malloc(sizeof(t_info));
	pars = malloc(sizeof(t_parsing));
	(void)argc;
	(void)argv;
	info->env = ft_arrycpy(envp);
	get_pwd(info);
 	while (1)
	{
		//ft_check_input(info);
		//ft_lexer(info, pars);
		ft_parser(info, pars, info->lexer);
		//ft_exec(info, pars);
	} 
}