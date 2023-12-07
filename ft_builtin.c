/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:35:56 by fstark            #+#    #+#             */
/*   Updated: 2023/12/07 18:34:38 by fstark           ###   ########.fr       */
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

char **find_arguments(t_parsing *pars, int command_count, t_info *info)
{
	t_lexer tmp;
	int i;
	char **input;
	
	//tmp = info->lexer_save;
	
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
	printf("length to malloc:%d\n", find_arguments_length(tmp) + 1);
	input = malloc((find_arguments_length(tmp) + 1) * sizeof(char *));
	i = 0;
	while (tmp.type == 1 && tmp.next != NULL)
	{
		input[i] = ft_strdup(tmp.token);
		tmp = *tmp.next;
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

void	ft_builtin(t_parsing *pars, t_info *info)
{
	int command_count = 0;
	printf("cmd:%s\n", pars->cmd_builtin[command_count]);
	if (ft_strncmp2(pars->cmd_builtin[command_count],  "echo", 4) == 0)
	{
		if (ft_strncmp2(pars->cmd_builtin[command_count + 1], "-n", 2) == 0)
		{
			command_count++;
			ft_echo(0, find_arguments(pars, command_count, info));
		}
		else
			ft_echo(0, find_arguments(pars, command_count, info));
	}
	if (ft_strncmp2(pars->cmd_builtin[command_count],  "export", 6) == 0)
		ft_export(info, find_arguments(pars, command_count, info));
	command_count++;

	//link to the correct builtins, and execute them with the right input
	
}