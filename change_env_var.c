/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:20:43 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/07 15:15:54 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	give_env_variable_pos(char *input, int i, t_info *info, int mode)
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

char	*copy_env_value(int j, t_info *info)
{
	int		i;
	char	*res;
	t_env	*tmp;

	tmp = info->env_list;
	i = -1;
	while (++i < j)
		tmp = tmp->next;
	i = 0;
	res = malloc((ft_strlen(tmp->value) + 1) * sizeof(char));
	if (res == NULL)
		return (NULL);
	while (tmp->value[i] != '\0')
	{
		res[i] = tmp->value[i];
		i++;
	}
	res[i] = '\0';
	return (res);
}

char	*check_hedoc(char *in, t_info *info, int i)
{
	int		state;
	char	*res;

	state = 0;
	res = strdup(in);
	while ((info->input[i] == ' ' || info->input[i] == '\t')
		&& info->input[i] != '\0')
		i++;
	while (info->input[i] != '\0')
	{
		if (info->input[i] == '\'' || info->input[i] == '\"')
		{
			if (state == 0)
				state = 1;
			else if (state == 1)
				state = 0;
		}
		if (state == 0 && ft_strchr_lexer(" \t<>|", info->input[i]))
			break ;
		res = add_char_to_str(res, info->input[i]);
		i++;
	}
	free(in);
	return (res);
}

char	*replace_dollar2(char *in, t_info *info, t_quote_state qs, char *res)
{
	while (in[info->i] != '\0' && info->flag == 0)
	{
		if (info->input[info->i] == '\'' && qs.state_d == 0)
			qs.state_s = update_quote_state2(qs, '\'');
		if (info->input[info->i] == '\"' && qs.state_s == 0)
			qs.state_d = update_quote_state2(qs, '\"');
		if (in[info->i] == '<' && in[info->i + 1] == '<'
			&& qs.state_s == 0 && qs.state_d == 0)
			res = handle_hedoc(res, in, info);
		else if (in[info->i] == '$' && (qs.state_s == 0))
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
		return (strdup("\0"));
	return (res);
}

char	*replace_dollar(char *input, t_info *info)
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
	res = replace_dollar2(input, info, qs, tmp);
	return (res);
}
