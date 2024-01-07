/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:21:49 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/07 17:46:40 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* void	ft_print_pars(t_pars *pars)
{
	int i = 0;
	int j = 0;
	int k = 0;

	while (pars != NULL)
	{
		printf("Node: %d\n", i);
		printf("----------------------\n");
		printf("Fd_in: %d\n", pars->fd_in);
		printf("Fd_out: %d\n", pars->fd_out);
		printf("In_file: %s\n", pars->in_file);
		printf("Out_file: %s\n", pars->out_file);
		printf("Cmd_path: %s\n", pars->cmd_path);
		printf("Command: %s\n", pars->command);
		printf("cmd_args: ");
		if (pars->cmd_args != NULL)
		{
			k = 0;
			while (pars->cmd_args[k])
			{
				printf("%s ", pars->cmd_args[k]);
				k++;
			}
		}
		printf("\n");
		printf("Args: ");
		if (pars->args != NULL)
		{
			j = 0;
			while (pars->args[j])
			{
				printf("%s ", pars->args[j]);
				j++;
			}
		}
		printf("\n");
		printf("----------------------\n");
		pars = pars->next;
		i++;
	}
} */

/*
void	print_lexer_list(t_info *info)
{
	t_lexer	*tmp;

	tmp = info->lexer;
	printf("\n");
	while (tmp->next != NULL)
	{
		printf("hd_quote %d\n", tmp->hd_quote);
		printf("command: %d\n", tmp->command);
		printf("type: %d\n", tmp->type);
		printf("token: %s\n\n", tmp->token);
		tmp = tmp->next;
	}
	printf("hd_quote %d\n", tmp->hd_quote);
	printf("command: %d\n", tmp->command);
	printf("type: %d\n", tmp->type);
	printf("token: %s\n", tmp->token);
}*/

void	ft_get_input(t_info *info)
{
	char	*line;

	line = readline(LIME"minishell>"OFF);
	info->input = ft_strdup(line);
	free(line);
	if (!info->input)
	{
		free(info->input);
		ft_free_all(*info->pars_ptr, info, 2);
		exit(1);
	}
	if (info->input[0] == '\0')
	{
		free(info->input);
		info->input = NULL;
		return ;
	}
	add_history(info->input);
	return ;
}

int	ft_listsize(t_pars *pars)
{
	int		i;
	t_pars	*tmp;

	i = 0;
	tmp = pars;
	while (tmp)
	{
		tmp = tmp->next;
		i++;
	}
	return (i);
}

void	ft_init_values(t_info *info)
{
	info->old_pwd = NULL;
	info->pwd = NULL;
	info->path = NULL;
	info->home = NULL;
	info->input = NULL;
	info->lexer = NULL;
	info->exit_status = 0;
	g_global.stop_hd = 0;
	g_global.in_cmd = 0;
	g_global.in_hd = 0;
	info->exit_code = 0;
	init_signals();
}

t_info	*calloc_info(void)
{
	t_info	*info;

	info = malloc(sizeof(t_info));
	if (!info)
	{
		ft_putstr_fd("minishell: malloc error\n", 1);
		exit (1);
	}
	ft_init_values(info);
	return (info);
}

int	main(int argc, char **argv, char **envp)
{
	t_info	*info;
	t_pars	*pars;

	ft_args(argv, argc);
	pars = NULL;
	info = calloc_info();
	info->pars_ptr = &pars;
	info->env = ft_arrycpy_main(envp, info);
	env_conversion(info, pars, envp);
	while (1)
	{
		init_loop(pars, info);
		pars = NULL;
		ft_get_input(info);
		if (!info->input)
			continue ;
		if (ft_check_input(info) == 1)
			continue ;
		ft_lexer(info);
		if (ft_parsing(&pars, info->lexer, info) == 1)
			continue ;
		ft_1(info, pars);
	}
	ft_free_all(pars, info, 2);
	return (0);
}
/*

echo "hello" > file1 | echo -n "hello" | cat < file1 
| cat -e > file2 | cat file2 | ls -l | wc -l

/bin/ls /bin/ -l

valgrind --suppressions=valgrind_ignore_leaks.txt 
--trace-children=yes --leak-check=full ./minishell

funcheck -i="readline" -a ./minishell

*/
