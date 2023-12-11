/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:35:56 by fstark            #+#    #+#             */
/*   Updated: 2023/12/11 16:04:34 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int ft_strncmp2(char *s1, char *s2, int n)
{
	int	i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		if (i < (n -1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

/*
int find_arguments_length(t_lexer tmp)
{
	t_lexer tmp2;
	int i;

	i = 0;
	if (tmp.next == NULL)
		return (0);
	tmp2 = tmp;
	while (tmp2.type == 1 && tmp2.next != NULL)
	{
		i++;
		tmp2 = *tmp2.next;
	}
	return (i);
}
*/

/*
char **find_arguments(t_parsing *pars, int command_count, t_info *info)
{
	t_lexer tmp;
	int i;
	char **input;
	
	
	tmp = info->lexer_save;
	
	t_lexer tmp3 = info->lexer_save;
	printf("\n");
	while (tmp3.next != NULL)
	{
		printf("type: %d\n", tmp3.type);
		printf("token: %s\n\n", tmp3.token);
		tmp3 = *tmp3.next;
	}
	printf("type: %d\n", tmp3.type);
	printf("token: %s\n", tmp3.token);
	i = 0;
	while (i < command_count)
	{
		if (ft_strncmp(tmp.token, pars->cmd_builtin[i], strlen(tmp.token)) == 0)
			i++;
		tmp = *tmp.next;
	}
	//printf("length to malloc:%d\n", find_arguments_length(tmp) + 1);
	input = malloc((find_arguments_length(tmp) + 1) * sizeof(char *));
	i = 0;
	while (tmp.type == 1 && tmp.next != NULL)
	{
		input[i] = ft_strdup(tmp.token);
		tmp = *tmp.next;
		i++;
	}
	if (tmp.type == 1)
	{
		input[i] = ft_strdup(tmp.token);
		i++;
	}
	input[i] = NULL;
	//print input
	i = 0;
	while (input[i] != NULL)
	{
		printf("input[%d]:%s\n", i, input[i]);
		i++;
	}
	return (input);
}
*/

void	ft_builtin(t_pars *pars, t_info *info)
{
	if (ft_strncmp2(pars->command,  "echo", 4) == 0)
		ft_echo(pars->args);
	if (ft_strncmp2(pars->command,  "export", 6) == 0)
		ft_export(info, pars->args);
	if (ft_strncmp2(pars->command,  "unset", 5) == 0)
		ft_unset(info, pars->args);
	if (ft_strncmp2(pars->command,  "env", 3) == 0)
		ft_env(info);
	if (ft_strncmp2(pars->command,  "cd", 2) == 0)
		ft_cd(info, pars->args);
	if (ft_strncmp2(pars->command,  "pwd", 2) == 0)
		ft_pwd(info);
	//info->builtin_command_count++;
}