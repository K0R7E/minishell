/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:40:04 by fstark            #+#    #+#             */
/*   Updated: 2023/12/01 12:46:39 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*add_char_to_str(char *str, char c)
{
	char	*new;
	int		length;

	length = 0;
	if (str == NULL)
		str = "\0";
	while (str[length] != '\0')
		length++;
	new = malloc ((length + 2) * (sizeof(char)));
	if (new != NULL)
	{
		length = 0;
		while (str[length] != '\0')
		{
			new[length] = str[length];
			length++;
		}
		new[length] = c;
		new[++length] = '\0';
	}
	if (str[0] != '\0')
		free(str);
	return (new);
}

char *ft_strjoin2(char *str, char *add)
{	
	if (add == NULL)
		return (NULL);
	if (str == NULL)
	{
		str = malloc(1 * sizeof(char));
		if (str	== NULL)
			return(NULL);
		str[0] = '\0';
	}
	char *total; 
	total = malloc((ft_strlen(str) + ft_strlen(add) + 1) * sizeof(char));
	if (total == NULL)
	{
		free(str);
		return(NULL);
	}
	int i = 0;
	while (str[i] != '\0')
	{
		total[i] = str[i];
		i++;
	}
	int j = 0;
	while (add[j] != '\0')
    {
		total[i + j] = add[j];
		j++;
    }
	total[i + j] = '\0';
	free(str);
	free(add);
	return (total);
}



int give_env_variable_pos(char *input, int i, t_info *info, int mode)
{
	int j;
	int pos;

	j = 0;
	pos = 0;
	while (input[i + ++j] != '\0')
	{
		if (input[i + j] == ' ' || input[i + j] == '\'' || input[i + j] == '\t' || input[i + j] == '\"' )
			break;
	}
	if (mode == 1)
		return (j);
	while(info->env[pos] != NULL)
	{
		if (ft_strncmp(info->env[pos], input + (i + 1), j - 1) == 0 && info->env[pos][j - 1] == '=')
		{
			//printf("found env variable: %s\n", info->env[pos]);
			return(pos);
		}
		pos++;
	}
	//printf("env variable not found\n");
	return(-1);
}

char *copy_env_value(int j, t_info *info)
{
	int i;
	char *res;

	i = 0;
	while (info->env[j][i] != '=')
		i++;
	res = malloc(((ft_strlen(info->env[j]) + 1) - i) * sizeof(char));
	if (res == NULL)
		return(NULL);
	i++;
	int k = 0;
	while (info->env[j][i] != '\0')
	{
		res[k] = info->env[j][i];
		i++;
		k++;
	}
	res[k] = '\0';
	//printf("res: %s\n", res);
	return (res);
}

char *replace_dollar(char *input,  t_info *info)
{
	int i;
	int state;
	char *res = NULL;
	int j;

	i = 0;
	state = 0;
	while (input[i] != '\0')
	{
		if (input[i] == '\'')
		{
			if (state == 0)
				state = 1;
			else if (state == 1)
				state = 0;
		}
		if (input[i] == '$' && state == 0)
		{
			j = give_env_variable_pos(input, i, info, 0);
			if (j != -1)
			{
				//printf("res before iteration %d: %s\n", i, res);
				res = ft_strjoin2(res, copy_env_value(j, info));
				//printf("res after iteration %d: %s\n", i, res);
			}
			i += (give_env_variable_pos(input, i, info, 1));
		}
		else
		{
			res = add_char_to_str(res, input[i]);
			i++;
			//printf("i: %d", i);
		}
		//printf("res after iteration %d: %s\n", i, res);
	}
	//free (input);
	return(res);
}
