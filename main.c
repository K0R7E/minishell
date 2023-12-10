#include "minishell.h"

void ft_get_input(t_info *info)
{
	char *line;

	line = readline(LIME"minishell>"OFF);
	wait(NULL);
	if (line == NULL)
	{
		rl_on_new_line();
	}
	else if (line[0] == '\0')
	{
		free(line);
		ft_get_input(info);
	}
	else /* (line[0] != '\0') */
		add_history(line);
	info->input = ft_strdup(line);
	free(line);
	if (ft_check_input(info) == 1)
		ft_get_input(info);	
}

void test_lexer_print(t_parsing *pars)
{
	t_lexer *tmp;
	int i = 0;

	tmp = &pars->lexer;
	while (tmp)
	{
		printf("Token: %d: %s\n", i, tmp->token);
		tmp = tmp->next;
		i++;
	}
}


int main(int argc, char **argv, char **envp)
{
	t_info *info;
	t_parsing *parsing;
	t_pars *pars;

	info = malloc(sizeof(t_info));
	parsing = malloc(sizeof(t_parsing));


	if (argc != 1 || argv[1])
	{
		printf("Please do not add parameters\n");
		return (1);
	}
	info->env = ft_arrycpy(envp);
	env_conversion(info);
	get_pwd(info);
	info->exit_status = 0;
	printf("\033[2J\033[1;1H");
 	while (1)
	{
		pars = malloc(sizeof(t_pars));
		pars = NULL;
		info->command_count = 1;
		info->builtin_command_count = 0;
		ft_get_input(info);
		ft_lexer(info, parsing);
		ft_parsing(&pars, &parsing->lexer, info);
		//ft_print_pars(pars);
		ft_test_executor(&pars, info);
		free_pars_list(pars);
	}
	return (0);
}

/* int main(int argc, char **argv, char **envp)
{
	t_info *info;
	t_parsing *parsing;
	t_pars *pars;

	info = malloc(sizeof(t_info));
	parsing = malloc(sizeof(t_parsing));
	if (argc != 1 || argv[1])
	{
		printf("Please do not add parameters\n");
		return (1);
	}
	info->env = ft_arrycpy(envp);
	env_conversion(info);
	get_pwd(info);
	//ft_print_minishell_gui();
	printf("\033[2J\033[1;1H");
 	while (1)
	{
		pars = malloc(sizeof(t_pars));
		pars = NULL;
		ft_signals();
		info->builtin_command_count = 0;
		ft_get_input(info);
		ft_lexer(info, parsing);
		ft_parsing((t_pars **)pars, &parsing->lexer, info);
		//ft_parser(&pars->lexer, pars, info);
		//printf("-----------------------------------------------------------------------------\n");
		//test_lexer_print(pars);
		ft_print_pars((t_pars *)pars);
		//ft_executor(pars, info);
	}
	return (0);
} */
//echo "hello" > file1 | cat < file1 | cat -e > file2 | cat file2 | ls -l | wc -l

