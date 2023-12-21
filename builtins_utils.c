/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/08 12:31:30 by fstark            #+#    #+#             */
/*   Updated: 2023/12/21 12:13:17 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int strlcmp_export(char *str1, char *str2, int n)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	if (str2[i] == '\0' && (str1[i] == '=' || str1[i] == '\0'))
		return (0);
	return (1);
}

void add_element(t_info *info, char *arg)
{
	t_env	*tmp;
	int i;

	i = 0;
	tmp = info->env_list;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	//if (arg[i] == '\0')
		//return ;
	while (strlcmp_export(arg, tmp->var, i) != 0 && tmp->next != NULL)
		tmp = tmp->next;
	//printf("compare: %s with %s for the first %d digits \n output: %d\n",arg, tmp->var, i -1, strlcmp_export(arg, tmp->var, i));
	if (strlcmp_export(arg, tmp->var, i) != 0)
	{
		//printf("%d\n", strlcmp_export(arg, tmp->var, i -1));
		
		tmp->next = malloc(sizeof(t_env));
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->printed = 0;
		tmp->var = ft_strldup(arg, i);
		if (arg[i] == '=')
			tmp->value = ft_strdup(arg + i + 1);
		else
			tmp->value = NULL;
	}
	else
	{
		if (arg[i] != '=')
			return;
		free(tmp->value);
		tmp->value = ft_strdup(arg + i + 1);
	}
}

void	update_info(t_info *info)
{
	t_env *tmp;
	char *unset;
	
	free(info->home);
	//free(info->pwd);
	//free(info->old_pwd);
	tmp = info->env_list;
	unset = strdup("000");
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "HOME", 4) == 0)
		{
			unset[0] = '1';
			info->home = ft_strdup(tmp->value);
		}
		/*
		if (ft_strncmp(tmp->var, "OLDPWD", 6) == 0)
		{
			unset[1] = '1';
			info->old_pwd = ft_strdup(tmp->value);
		}
		if (ft_strncmp(tmp->var, "PWD", 3) == 0)
		{
			unset[2] = '1';
			info->pwd = ft_strdup(tmp->value);
		}*/
		tmp = tmp->next;
	}
	if (unset[0] == '0')
	{
		free(info->home);
		//info->home = ft_strdup("");
		info->home = NULL;
	}
	/*
	if (unset[1] == '0')
	{
		free(info->old_pwd);
		//info->old_pwd = ft_strdup("");
		info->old_pwd = NULL;
	}
	if (unset[2] == '0')
		info->pwd = ft_strdup("");*/
}