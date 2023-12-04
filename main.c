#include "minishell.h"

void ft_get_input(t_info *info)
{
	char *line;

	line = readline("\033[0;32mminishell> \033[0m");
	if (line == NULL)
	{
		printf("exit\n");
		exit(0);
	}
	else if (line[0] != '\0')
	{
		add_history(line);
	}
	info->input = ft_strdup(line);
	free(line);
}

int main(int argc, char **argv, char **envp)
{
	t_info *info;
	t_parsing *pars;

	info = malloc(sizeof(t_info));
	pars = malloc(sizeof(t_parsing));
	if (argc != 1 || argv[1])
	{
		printf("Please do not add parameters\n");
		return (1);
	}
	info->env = ft_arrycpy(envp);
	get_pwd(info);
 	while (1)
	{
		ft_get_input(info);
		//ft_check_input(info);
		//ft_lexer(info, pars);
		ft_parser(pars->lexer, pars);
/* 		ft_executor(info, pars);
		ft_execute(pars->args, pars->fd_in, pars->fd_out); */

/*     	t_lexer *tokens = tokenize_input(info->input);

    	printf("Tokens:\n");
    	print_tokens(tokens);

    	printf("\nParsed:\n");
    	ft_parser(tokens, pars);

    	free_tokens(tokens);
    	free_parsing(pars); */
	}
	return (0);
}