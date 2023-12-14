/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/29 13:40:04 by fstark            #+#    #+#             */
/*   Updated: 2023/12/14 19:44:36 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int give_env_variable_pos(char *input, int i, t_info *info, int mode)
{
	int j;
	int pos;
	t_env *tmp;

	j = 0;
	pos = 0;
	while (input[i + ++j] != '\0')
	{
		if (input[i + j] == ' ' || input[i + j] == '\'' || input[i + j] == '\t' || input[i + j] == '\"' )
			break;
	}
	if (mode == 1)
		return (j);
	tmp = info->env_list;
	while (tmp != NULL)
	{
		//printf("comparing %s with %s\n", tmp->var, input + (i + 1));
		if (ft_strncmp(tmp->var, input + (i + 1), j - 1) == 0 && tmp->var[j] == '\0')
		{
			//printf("found env variable: %s\n", info->env[pos]);
			return(pos);
		}
		if (tmp->next == NULL)
			break;
		tmp = tmp->next;
		pos++;
	}
	//printf("env variable not found\n");
	return(-1);
}

char *copy_env_value(int j, t_info *info)
{
	int i;
	char *res;
	t_env *tmp;

	tmp = info->env_list;
	i = -1;
	while (++i < j)
		tmp = tmp->next;
	i = 0;
	res = malloc((ft_strlen(tmp->value + 1)) * sizeof(char));
	if (res == NULL)
		return(NULL);
	while (tmp->value[i] != '\0')
	{
		res[i] = tmp->value[i];
		i++;
	}
	res[i] = '\0';
	//printf("res: %s\n", res);
	return (res);
}

char *check_hedoc(char *in, t_info *info, int i)
{
	int state;
	char *res;

	state = 0;
	res = strdup(in);
	while ((info->input[i] == ' ' || info->input[i] == '\t') && info->input[i] != '\0')
		i++;
	while (info->input[i] != '\0' && (info->input[i] != ' ' && info->input[i] != '\t' && state == 0))
	{
		if (info->input[i] == '\'' || info->input[i] == '\"')
		{
			if (state == 0)
				state = 1;
			else if (state == 1)
				state = 0;
		}
		res = add_char_to_str(res, info->input[i]);
		i++;
	}
	free(in);
	return res;
}

int	hedoc_length(t_info *info, int i)
{
	int state;

	state = 0;
	while ((info->input[i] == ' ' || info->input[i] == '\t') && info->input[i] != '\0')
		i++;
	while (info->input[i] != '\0' && (info->input[i] != ' ' && info->input[i] != '\t' && state == 0))
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
		if (input[i] == '\"')
		{
			if (state == 0)
				state = 2;
			else if (state == 2)
				state = 0;
		}
		if (input[i] == '<' && input[i + 1] == '<' && state == 0)
		{
			res = add_char_to_str(res, input[i++]);
			res = add_char_to_str(res, input[i++]);
			res = check_hedoc(res, info, i);
			i = hedoc_length(info, i);
			if (input[i] == '\0')
				break;
		}
		if (input[i] == '$' && (state == 0 || state == 2))
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
	if (res == NULL)
		return (strdup("\0"));
	return(res);
}