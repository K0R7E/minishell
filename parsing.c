#include "minishell.h"

void ft_parser(t_info *info, t_parsing *pars, t_lexer *lexer)
{
	int i = 0;

	while (lexer->token[i])
	{
		
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