/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_unset.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:44:15 by fstark            #+#    #+#             */
/*   Updated: 2024/01/06 17:06:29 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	strlcmp_unset(char *str1, char *str2, int n)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	if (str2[i] == '\0' && str1[i] == '\0')
		return (0);
	return (1);
}

void	remove_element2(t_info *info, int j, t_env *tmp)
{
	t_env	*tmp2;

	tmp2 = info->env_list;
	while (j > 1)
	{
		tmp2 = tmp2->next;
		j--;
	}
	tmp2->next = tmp->next;
	free(tmp->var);
	free(tmp->value);
	free(tmp);
}

void	remove_element(t_info *info, char *arg)
{
	t_env	*tmp;
	int		i;
	int		j;

	i = 0;
	j = 0;
	tmp = info->env_list;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	if (arg[i] != '\0')
		return ;
	while (strlcmp_unset(arg, tmp->var, i) != 0 && tmp->next != NULL)
	{
		tmp = tmp->next;
		j++;
	}
	if (strlcmp_unset(arg, tmp->var, i) != 0)
		return ;
	remove_element2(info, j, tmp);
}

int	ft_unset(t_info *info, char **args)
{
	int	i;

	i = 1;
	if (args[1] == NULL)
		return (0);
	else
	{
		while (args[i] != NULL)
			remove_element(info, args[i++]);
	}
	return (0);
}
