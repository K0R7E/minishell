/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:40:04 by fstark            #+#    #+#             */
/*   Updated: 2023/12/05 11:46:39 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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
	free (input);
	return(res);
}

char *change_env_var(char *input,  t_info *info)
{
	if (ft_strchr2(input, '$'))
	{
		printf("hi\n");
		input = replace_dollar(input, info);
	}
	return (input);
}