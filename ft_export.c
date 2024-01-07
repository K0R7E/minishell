/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:14:21 by fstark            #+#    #+#             */
/*   Updated: 2024/01/07 14:04:33 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

int	ft_strcmp(char *str1, char *str2)
{
	int	i;

	i = 0;
	while (str1[i] && str2[i])
	{
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	if (str1[i] > str2[i])
		return (2);
	if (str1[i] < str2[i])
		return (-2);
	return (0);
}

int	list_size(t_env *head)
{
	int		i;
	t_env	*tmp;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	print_export2(t_info *info)
{
	t_env	*tmp;
	t_env	*tmp2;

	tmp = info->env_list;
	tmp2 = info->env_list;
	while (tmp2->printed == 1)
		tmp2 = tmp2->next;
	while (tmp)
	{
		if (tmp->printed == 1)
		{
			tmp = tmp->next;
			continue ;
		}
		else if (ft_strcmp(tmp->var, tmp2->var) < 0)
			tmp2 = tmp;
		tmp = tmp->next;
	}
	if ((tmp2->value == NULL && ft_strncmp(tmp2->var, "_", 2) != 0)
		&& (ft_strncmp(tmp2->var, "ZDOTDIR", 8) != 0))
		printf("declare -x %s\n", tmp2->var);
	else if (ft_strncmp(tmp2->var, "_", 2) != 0
		&& (ft_strncmp(tmp2->var, "ZDOTDIR", 8) != 0))
		printf("declare -x %s=\"%s\"\n", tmp2->var, tmp2->value);
	tmp2->printed = 1;
}

void	print_export(t_info *info)
{
	t_env	*tmp2;
	int		i;
	int		j;

	i = list_size(info->env_list);
	j = 0;
	while (j < i)
	{
		print_export2(info);
		j++;
	}
	tmp2 = info->env_list;
	while (tmp2)
	{
		tmp2->printed = 0;
		tmp2 = tmp2->next;
	}
}

/*
int	is_valid_env(char *env)
{
	int		i;

	i = 0;
	if (ft_isdigit(env[i]) == 1)
		return (1);
	if (env[i] == '=')
		return (1);
	while (env[i] && env[i] != '=' && env[i] != '\0')
	{
		if (ft_isalnum(env[i]) == 0 && env[i] != '_')
			return (1);
		i++;
	}
	return (0);
}*/

int	ft_export(t_info *info, char **args)
{
	int	i;
	int	ret;

	ret = 0;
	i = 1;
	if (args[1] == NULL)
		print_export(info);
	else
	{
		while (args[i] != NULL)
		{
			if (is_valid_env(args[i]) == 0)
				add_element(info, args[i++]);
			else
			{
				ft_putstr_fd("minishell: export: `", 2);
				ft_putstr_fd(args[i], 2);
				ft_putstr_fd("': not a valid identifier\n", 2);
				ret = 1;
				i++;
			}
		}
	}
	i = 1;
	return (ret);
}

/*
		ft_export(info, NULL);
		ft_export(info, "a=abc");
		printf("_________________________\n");
		ft_export(info, NULL);
		ft_export(info, "a=123");
		printf("_________________________\n");
		ft_export(info, "b=123");
		ft_export(info, NULL);
*/