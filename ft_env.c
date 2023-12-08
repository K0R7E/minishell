/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:16:44 by fstark            #+#    #+#             */
/*   Updated: 2023/12/08 17:23:50 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
void add_element(t_info *info, char *arg)
{
	t_env	*tmp;
	int i;

	i = 0;
	tmp = info->env_list;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	if (arg[i] == '\0')
		return ;
	while (strlcmp_export(arg, tmp->var, i) != 0 && tmp->next != NULL)
		tmp = tmp->next;
	//printf("compare: %s with %s for the first %d digits \n output: %d\n",arg, tmp->var, i -1, strlcmp_export(arg, tmp->var, i));
	if (strlcmp_export(arg, tmp->var, i) != 0)
	{
		printf("%d\n", strlcmp_export(arg, tmp->var, i -1));
		tmp->next = malloc(sizeof(t_env));
		tmp = tmp->next;
		tmp->next = NULL;
		tmp->printed = 0;
		tmp->var = ft_strldup(arg, i);
		tmp->value = ft_strdup(arg + i + 1);
	}
	else
	{
		free(tmp->value);
		tmp->value = ft_strdup(arg + i + 1);
	}
}
*/

void	ft_env(t_info *info)
{
	t_env	*tmp;
	int i;
	i = 1;
	
	tmp = info->env_list;
	while (tmp)
	{
		printf("%s=%s\n", tmp->var, tmp->value);
		tmp = tmp->next;
	}
	i = 1;
}

