/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_export.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 18:14:21 by fstark            #+#    #+#             */
/*   Updated: 2023/12/07 15:52:59 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int		ft_strcmp(char *str1, char *str2)
{
	int i;

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

//compare the first n digits of two strings
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
	if (str2[i] == '\0' && str1[i] == '=')
		return (0);
	return (1);
}

/*
int	ft_arrylen(char **arr)
{
	int i;void	ft_export(t_info *info, char *arg);

	i = 0;
	while (arr[i])
		i++;
	return (i);
}
*/
/*
void	print_export(t_info *info)
{
	//Sort array alphabetically
	int i;
	int j;
	int length;
	char **tmp;
	char *temp;

	i = 0;
	j = 0;
	length = ft_arrylen(info->env);
	tmp = ft_arrycpy(info->env);
	while (i < length - 1)
	{
		j = 0;
		while ( i + j < length)
		{
			if (ft_strcmp(tmp[i], tmp[i + j]) > 0)
			{
				temp = tmp[i];
				tmp[i] = tmp[i + j];
				tmp[i + j] = temp;
			}
			j++;
		}
		i++;
	}
	
	i = 0;
	while (tmp[i])
	{
		if (ft_strcmp(tmp[i], "_=") != 2)
			printf("declare -x %s\n", tmp[i]);
		i++;
	}
	free_array(tmp);
}
*/

int list_size(t_env *head)
{
	int i;
	t_env *tmp;

	i = 0;
	tmp = head;
	while (tmp)
	{
		i++;
		tmp = tmp->next;
	}
	return (i);
}

void	print_export(t_info *info)
{
	t_env *tmp;
	t_env *tmp2;
	int i;
	int j;

	i = list_size(info->env_list);
	//printf("i = %d\n", i);
	j = 0;
	while (j < i)
	{
		tmp = info->env_list;
		tmp2 = info->env_list;
		while (tmp2->printed == 1)
			tmp2 = tmp2->next;
		while (tmp)
		{
			if (tmp->printed == 1)
			{
				tmp = tmp->next;
				continue;
			}
			else if (ft_strcmp(tmp->var, tmp2->var) < 0)
				tmp2 = tmp;
			tmp = tmp->next;
		}
		printf("declare -x %s=\"%s\"\n", tmp2->var, tmp2->value);
		j++;
		tmp2->printed = 1;
	}
	tmp2 = info->env_list;
	while (tmp2)
	{
		tmp2->printed = 0;
		tmp2 = tmp2->next;
	}
}

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
	printf("compare: %s with %s for the first %d digits \n output: %d\n",arg, tmp->var, i -1, strlcmp_export(arg, tmp->var, i));
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

void	ft_export(t_info *info, char **args)
{
	int i;
	
	i = 0;
	if (args[0] == NULL)
		print_export(info);
	else
	while (args[i] != NULL)
		add_element(info, args[i++]);
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