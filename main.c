#include "minishell.h"
#include <readline/readline.h>

void ft_get_input(t_info *info)
{
	char *line;
	
	line = readline(LIME"minishell>"OFF);
	info->input = ft_strdup(line);
	free(line);
	if (!info->input)
	{
		ft_putendl_fd("exit", STDOUT_FILENO);
		exit(EXIT_SUCCESS);
	}
	if (info->input[0] == '\0')
	{
		free(info->input);
		info->input = NULL;
		return ;
	}
	add_history(info->input);
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

int ft_listsize(t_pars *pars)
{
	int i;
	t_pars *tmp;

	i = 0;
	tmp = pars;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
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
	//ft_print_minishell_gui();
	printf("\033[2J\033[1;1H");
	pars = malloc(sizeof(t_pars));
 	while (1)
	{
		pars = NULL;
		info->command_count = 1;
		info->builtin_command_count = 0;
		ft_get_input(info);
		if (ft_check_input(info) == 1)
			continue ;
		if (!info->input)
			continue ;
		ft_lexer(info, parsing);
		ft_parsing(&pars, &parsing->lexer, info);
		info->command_count = ft_listsize(pars);
		//ft_print_pars(pars);
		ft_executor(pars, info);
		//ft_command_execute(pars, ft_listsize(pars), info);
		//free_pars_list(pars);
		free(info->input);
		info->input = NULL;
	}
	return (0);
}

/*

echo "hello" > file1 | echo -n "hello" | cat < file1 | cat -e > file2 | cat file2 | ls -l | wc -l

/bin/ls /bin/ -l

*/

