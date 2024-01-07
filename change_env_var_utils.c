/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 11:18:52 by fstark            #+#    #+#             */
/*   Updated: 2024/01/07 14:10:41 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	hedoc_length(t_info *info, int i)
{
	int	state;

	state = 0;
	while ((info->input[i] == ' ' || info->input[i] == '\t')
		&& info->input[i] != '\0')
		i++;
	while (info->input[i] != '\0' && (info->input[i] != ' '
			&& info->input[i] != '\t' && state == 0))
	{
		if (info->input[i] == '\'' || info->input[i] == '\"')
		{
			if (state == 0)
				state = 1;
			else if (state == 1)
				state = 0;
		}
		i++;
	}
	return (i);
}

char	*add_char_to_str(char *str, char c)
{
	char	*new;
	int		length;

	length = 0;
	if (str == NULL)
	{
		str = malloc(1 * sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
	}
	while (str[length] != '\0')
		length++;
	new = malloc ((length + 2) * (sizeof(char)));
	if (new != NULL)
	{
		length = -1;
		while (str[++length] != '\0')
			new[length] = str[length];
		new[length] = c;
		new[++length] = '\0';
	}
	free(str);
	return (new);
}

char	*ft_fill_str(char *str, char *add, int i, int j)
{
	char	*total;

	total = malloc((ft_strlen(str) + ft_strlen(add) + 2) * sizeof(char));
	if (total != NULL)
	{
		while (str[i] != '\0')
		{
			total[i] = str[i];
			i++;
		}
		while (add[j] != '\0')
		{
			total[i + j] = add[j];
			j++;
		}
		total[i + j] = '\0';
	}
	free(str);
	free(add);
	return (total);
}

char	*ft_strjoin2(char *str, char *add)
{
	char	*total;
	int		i;
	int		j;

	i = 0;
	j = 0;
	if (add == NULL)
		return (NULL);
	if (str == NULL)
	{
		str = malloc(1 * sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
	}
	total = ft_fill_str(str, add, i, j);
	return (total);
}

/*
char	*ft_strjoin2(char *str, char *add)
{
	char	*total;
	int		i;
	int		j;

	if (add == NULL)
		return (NULL);
	if (str == NULL)
	{
		str = malloc(1 * sizeof(char));
		if (str == NULL)
			return (NULL);
		str[0] = '\0';
	}
	total = malloc((ft_strlen(str) + ft_strlen(add) + 1) * sizeof(char));
	if (total == NULL)
	{
		free(str);
		return (NULL);
	}
	i = 0;
	while (str[i] != '\0')
	{
		total[i] = str[i];
		i++;
	}
	j = 0;
	while (add[j] != '\0')
    {
		total[i + j] = add[j];
		j++;
    }
	total[i + j] = '\0';
	free(str);
	free(add);
	return (total);
}*/
