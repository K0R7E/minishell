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

/*
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
}*/

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

void ft_init(t_pars *pars, t_info *info, char **envp)
{
	info->env = ft_arrycpy(envp);
	env_conversion(info, pars, envp);
	get_pwd(info);
	info->exit_status = 0;
	g_global.stop_hd = 0;
	g_global.in_cmd = 0;
	g_global.in_hd = 0;
	init_signals();
	info->command_count = 1;
	info->builtin_command_count = 0;
}


int main(int argc, char **argv, char **envp)
{
	t_info *info;
	t_pars *pars;

	if (argc != 1 || argv[1])
	{
		printf("Please do not add parameters\n");
		return (1);
	}
	info = malloc(sizeof(t_info));
	if (!info)
		return (1);
	pars = malloc(sizeof(t_pars));
	if (!pars)
	{
		free(info);
		return (1);
	}
	ft_init(pars, info, envp);
	printf("\033[2J\033[1;1H");
 	while (1)
	{
		pars = NULL;
		ft_get_input(info);
		if (ft_check_input(info) == 1)
			continue ;
		if (!info->input)
			continue ;
		ft_lexer(info, pars);
		ft_parsing(&pars, &info->lexer, info);
		info->command_count = ft_listsize(pars);
		ft_executor(pars, info);
		ft_give_new_value(pars, info);
	}
	ft_free_all(pars, info, 2);
	free(info);
	free(pars);
	return (0);
}

