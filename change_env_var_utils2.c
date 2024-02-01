/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var_utils2.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:20:53 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/01 15:54:27 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*handle_char(char *res, char *input, t_info *info)
{
	char	*tmp;

	tmp = add_char_to_str(res, input[info->i]);
	if (tmp == NULL)
	{
		free(res);
		ft_error_message(*info->pars_ptr, info);
	}
	info->i++;
	return (tmp);
}

char	*handle_dollar_sign2(t_info *info, char *res, int j)
{
	char	*tmp;

	tmp = copy_env_value(j, info);
	if (tmp == NULL)
	{
		free(res);
		ft_error_message(*info->pars_ptr, info);
	}
	res = ft_strjoin2(res, tmp);
	if (res == NULL)
		ft_error_message(*info->pars_ptr, info);
	tmp = ft_strdup(res);
	if (tmp == NULL)
	{
		free(res);
		ft_error_message(*info->pars_ptr, info);
	}
	free(res);
	return (tmp);
}

char	*handle_dollar_sign(t_info *info, char *res, int i, char *input)
{
	int		j;
	char	*tmp;

	tmp = NULL;
	j = give_env_variable_pos(input, i, info, 0);
	if (j != -1)
	{
		tmp = handle_dollar_sign2(info, res, j);
	}
	else
	{
		if (res == NULL)
			tmp = ft_strdup("\0");
		else
			tmp = ft_strdup(res);
		if (tmp == NULL)
		{
			free(res);
			ft_error_message(*info->pars_ptr, info);
		}
		free(res);
	}
	info->i += (give_env_variable_pos(input, info->i, info, 1));
	return (tmp);
}

char	*handle_question_mark(t_info *info, char *res)
{
	char	*tmp;

	tmp = ft_itoa(info->exit_code);
	if (tmp == NULL)
	{
		free(res);
		ft_error_message(*info->pars_ptr, info);
	}
	res = ft_strjoin2(res, tmp);
	if (res == NULL)
	{
		ft_error_message(*info->pars_ptr, info);
	}
	tmp = ft_strdup(res);
	if (tmp == NULL)
	{
		free(res);
		ft_error_message(*info->pars_ptr, info);
	}
	free(res);
	info->i += 2;
	return (tmp);
}

char	*handle_hedoc(char *res, char *input, t_info *info)
{
	char	*tmp;

	res = handle_char(res, input, info);
	res = handle_char(res, input, info);
	res = check_hedoc(res, info, info->i);
	info->i = hedoc_length(info, info->i);
	tmp = ft_strdup(res);
	if (tmp == NULL)
	{
		free(res);
		ft_error_message(*info->pars_ptr, info);
	}
	free(res);
	return (tmp);
}
