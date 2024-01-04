/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion_back.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 17:32:19 by fstark            #+#    #+#             */
/*   Updated: 2024/01/03 17:32:41 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_lstsize2(t_env *lst)
{
	int	i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char	**env_conversion_back(t_info *info)
{
	t_env	*tmp;
	int		i;
	char	**res;

	i = 0;
	tmp = info->env_list;
	res = malloc((ft_lstsize2(tmp) + 1) * sizeof(char *));
	if (res == NULL)
	{
		ft_error_message(NULL, info);
	}
	while (tmp)
	{
		res[i] = ft_strjoin(tmp->var, "=");
		res[i] = ft_strjoin(res[i], tmp->value);
		tmp = tmp->next;
		i++;
	}
	res[i] = NULL;
	return (res);
}
