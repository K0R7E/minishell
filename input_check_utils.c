/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 14:25:10 by fstark            #+#    #+#             */
/*   Updated: 2024/01/03 17:42:31 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_handle_redirect_length(t_info *info, int i)
{
	if (info->input[i] == '>' && info->input[i + 1] == '>')
		i++;
	else if (info->input[i] == '<' && info->input[i + 1] == '<')
		i++;
	return (i);
}

int	ft_find_last_redirect(t_info *info, int i)
{
	i--;
	if (info->input[i +1] == '>' && info->input[i] == '>')
		i--;
	else if (info->input[i +1] == '<' && info->input[i] == '<')
		i--;
	while (i >= 0)
	{
		if (info->input[i] == '>' && info->input[i - 1] == '>')
			return (4);
		else if (info->input[i] == '<' && info->input[i - 1] == '<')
			return (3);
		else if (info->input[i] == '>')
			return (2);
		else if (info->input[i] == '<')
			return (1);
		i--;
	}
	return (0);
}

int	check_if_allowed(int newer, int last, t_info *info, int i)
{
	if (last == 3)
	{
		if (newer != 1 && newer != 2)
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
		if (newer != 1 && newer != 2)
			return (1);
	}
	if (last == 2)
	{
		if (newer != 1)
		{
			ft_putstr_fd("syntax error near unexpected token `", 2);
			if (ft_find_last_redirect(info, i) == 1)
				ft_putstr_fd("<", 2);
			if (ft_find_last_redirect(info, i) == 2)
				ft_putstr_fd(">", 2);
			if (ft_find_last_redirect(info, i) == 3)
				ft_putstr_fd("<<", 2);
			if (ft_find_last_redirect(info, i) == 4)
				ft_putstr_fd(">>", 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
	}
	return (0);
}
