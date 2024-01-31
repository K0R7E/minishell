/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var_hedoc.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/04 11:32:51 by fstark            #+#    #+#             */
/*   Updated: 2024/01/31 20:47:59 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/*
int	give_env_variable_pos_hedoc(char *input, int i, t_info *info, int mode)
{
	int		j;
	int		pos;
	t_env	*tmp;

	j = 0;
	pos = 0;
	while (input[i + ++j] != '\0')
	{
		if (ft_isalnum(input[i + j]) == 0 && input[i + j] != '_')
			break ;
	}
	if (mode == 1)
		return (j);
	tmp = info->env_list;
	while (tmp != NULL)
	{
		if (ft_strncmp(tmp->var, input + (i + 1), j - 1) == 0
			&& tmp->var[j - 1] == '\0')
			return (pos);
		if (tmp->next == NULL)
			break ;
		tmp = tmp->next;
		pos++;
	}
	return (-1);
}

char	*copy_env_value_hedoc(int j, t_info *info)
{
	int		i;
	char	*res;
	t_env	*tmp;

	tmp = info->env_list;
	i = -1;
	while (++i < j)
		tmp = tmp->next;
	i = 0;
	res = malloc((ft_strlen(tmp->value + 1)) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (tmp->value[i] != '\0')
	{
		res[i] = tmp->value[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}*/

/*
char	*replace_dollar_hedoc(char *input, t_info *info)
{
	int				i;
	char			*res;
	int				j;
	t_quote_state	qs;

	qs.state_d = 0;
	qs.state_s = 0;
	i = 0;
	res = NULL;
	while (input[i] != '\0')
	{
		if (input[i] == '$' && (qs.state_s == 0))
		{
			if (input[i +1] == '?')
			{
				res = ft_strjoin2(res, ft_itoa(info->exit_code));
				i += 2;
			}
			else if (ft_isalpha(input[i +1]) == 0 && input[i +1] != '_')
			{
				res = add_char_to_str(res, input[i]);
				i++;
			}
			else
			{
				j = give_env_variable_pos_hedoc(input, i, info, 0);
				if (j != -1)
					res = ft_strjoin2(res, copy_env_value_hedoc(j, info));
				i += (give_env_variable_pos_hedoc(input, i, info, 1));
			}
		}
		else
		{
			res = add_char_to_str(res, input[i]);
			i++;
		}
	}
	free (input);
	if (res == NULL)
		return (strdup("\0"));
	return (res);
}*/

char	*replace_dollar_he2(char *in, t_info *info, t_quote_state qs, char *res)
{
	while (in[info->i] != '\0' && info->flag == 0)
	{
		if (in[info->i] == '$' && (qs.state_s == 0))
		{
			if (in[info->i +1] == '?')
				res = handle_question_mark(info, res);
			else if (ft_isalpha(in[info->i +1]) == 0 && in[info->i +1] != '_')
				res = handle_char(res, in, info);
			else
				res = handle_dollar_sign(info, res, info->i, in);
		}
		else
			res = handle_char(res, in, info);
	}
	free (in);
	if (res == NULL)
	{
		res = ft_strdup("\0");
		if (res == NULL)
			ft_error_message(*info->pars_ptr, info);
	}
	return (res);
}

char	*replace_dollar_hedoc(char *input, t_info *info)
{
	t_quote_state	qs;
	int				i;
	char			*res;
	char			*tmp;

	tmp = NULL;
	info->flag = 0;
	qs.state_d = 0;
	qs.state_s = 0;
	i = 0;
	info->i = 0;
	res = replace_dollar_he2(input, info, qs, tmp);
	return (res);
}
