/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:34:23 by fstark            #+#    #+#             */
/*   Updated: 2023/12/13 14:52:13 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//convert the env to a linked list

int	find_equals_sign(char *str)
{
	int i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '=')
			return (i);
		i++;
	}
	return (-1);
}

t_env	*ft_lstlast(t_env *head)
{
	t_env	*tmp;

	tmp = head;
	while (tmp->next)
	{
		tmp = tmp->next;
		if (tmp->next == NULL)
			return (tmp);
	}
	return (tmp);
}

void	ft_lstadd_back(t_env *stack, t_env *newx)
{
	t_env	*n;

	if (stack)
	{
		n = ft_lstlast(stack);
		n->next = newx;
		newx->next = NULL;
	}
	/*
	else
	{
		*stack = newx;
		(*stack)->next = NULL;
	}
	*/
}

void	env_conversion(t_info *info)
{
	t_env	*tmp;
	int		i;

	info->env_list = NULL;
	i = 0;
	while (info->env[i])
	{
		tmp = malloc(sizeof(t_env));
		tmp->next = NULL;
		tmp->printed = 0;
		tmp->var = ft_strldup(info->env[i], find_equals_sign(info->env[i]));
		tmp->value = ft_strdup(info->env[i] + find_equals_sign(info->env[i]) + 1);
		if (info->env_list == NULL)
			info->env_list = tmp;
		else
			ft_lstadd_back(info->env_list, tmp);
		i++;
	}
	//print the info->env_list list
	/*
	tmp = info->env_list;
	while (tmp)
	{
		printf("var: %s\n", tmp->var);
		//printf("value: %s\n", tmp->value);
		tmp = tmp->next;
	}
	*/
}

int	ft_lstsize2(t_env *lst)
{
	int i;

	i = 0;
	while (lst)
	{
		lst = lst->next;
		i++;
	}
	return (i);
}

char **env_conversion_back(t_info *info)
{
	t_env	*tmp;
	int		i;
	char	**res;

	i = 0;
	tmp = info->env_list;
	res = malloc((ft_lstsize2(tmp) + 1) * sizeof(char *));
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