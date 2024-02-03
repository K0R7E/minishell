/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:32:25 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/03 18:37:29 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_error_msg(char *msg)
{
	write(1, "\n", 1);
	ft_putstr_fd("minishell: warning: here-documentdelimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("')\n\n", 2);
}

int	ft_check_stop_hd(t_info *info, char *line)
{
	if (info->stop_hd || !line)
	{
		info->stop_hd = 0;
		return (1);
	}
	return (0);
}

char	*ft_hd_str_01(t_pars *pars, t_info *info, char *str, char *line)
{
	str = ft_str_123(pars, info, str, line);
	if (info->hd_quote == 0)
		str = replace_dollar_hedoc(str, info);
	return (str);
}

int	ft_check_empty_line(char *str, char *input)
{
	if (input == NULL)
	{
		hd_error_msg(str);
		return (1);
	}
	return (0);
}

int	ft_check_hd(t_info *info, char *input)
{
	if (info->stop_hd)
	{
		if (input)
			free(input);
		return (1);
	}
	return (0);
}
