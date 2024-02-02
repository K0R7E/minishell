/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_conversion.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/06 14:34:23 by fstark            #+#    #+#             */
/*   Updated: 2024/02/02 17:35:58 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//convert the env to a linked list

int	find_equals_sign(char *str)
{
	int	i;

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
}

void	env_conversion2(t_info *info, t_pars *pars, char **envp, int i)
{
	t_env	*tmp;

	tmp = malloc(sizeof(t_env));
	if (tmp == NULL)
		ft_error_message(pars, info);
	tmp->next = NULL;
	tmp->printed = 0;
	tmp->var = ft_strldup(envp[i], find_equals_sign(envp[i]));
	if (tmp->var == NULL)
	{
		free(tmp);
		ft_error_message(pars, info);
	}
	tmp->value = ft_strdup(envp[i] + find_equals_sign(envp[i]) + 1);
	if (tmp->value == NULL)
	{
		free(tmp->var);
		free(tmp);
		ft_error_message(pars, info);
	}
	if (info->env_list == NULL)
		info->env_list = tmp;
	else
		ft_lstadd_back(info->env_list, tmp);
}

void	env_conversion(t_info *info, t_pars *pars, char **envp)
{
	int		i;

	info->env_list = NULL;
	i = 0;
	while (envp[i])
	{
		env_conversion2(info, pars, envp, i);
		i++;
	}
	get_pwd(info);
}

/*
void	env_conversion(t_info *info, t_pars *pars, char **envp)
{
	t_env	*tmp;
	int		i;

	info->env_list = NULL;
	i = 0;
	while (envp[i])
	{
		tmp = malloc(sizeof(t_env));
		if (tmp == NULL)
			ft_error_message(pars, info);
		tmp->next = NULL;
		tmp->printed = 0;
		tmp->var = ft_strldup(envp[i], find_equals_sign(envp[i]));
		if (tmp->var == NULL)
		{
			free(tmp);
			ft_error_message(pars, info);
		}
		tmp->value = ft_strdup(envp[i] + find_equals_sign(envp[i]) + 1);
		if (tmp->var == NULL)
		{
			free(tmp->var);
			free(tmp);
			ft_error_message(pars, info);
		}
		if (info->env_list == NULL)
			info->env_list = tmp;
		else
			ft_lstadd_back(info->env_list, tmp);
		i++;
	}
}*/

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

/*
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
}*/