/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_builtin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 12:35:56 by fstark            #+#    #+#             */
/*   Updated: 2024/01/03 18:41:19 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp2(char *s1, char *s2, int n)
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
int	find_arguments_length(t_lexer tmp)
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
}*/

int	ft_builtin(t_pars *pars, t_info *info)
{
	int	exit_code;

	exit_code = 0;
	if (ft_strncmp2(pars->command, "echo", 4) == 0)
		exit_code = ft_echo(pars->cmd_args);
	if (ft_strncmp2(pars->command, "export", 6) == 0)
		exit_code = ft_export(info, pars->cmd_args);
	if (ft_strncmp2(pars->command, "unset", 5) == 0)
		exit_code = ft_unset(info, pars->cmd_args);
	if (ft_strncmp2(pars->command, "env", 3) == 0)
		exit_code = ft_env(info);
	if (ft_strncmp2(pars->command, "cd", 2) == 0)
		exit_code = ft_cd(info, pars->cmd_args);
	if (ft_strncmp2(pars->command, "pwd", 3) == 0)
		exit_code = ft_pwd(info);
	if (ft_strncmp2(pars->command, "exit", 3) == 0)
		exit_code = ft_exit(info, pars->cmd_args);
	return (exit_code);
}
