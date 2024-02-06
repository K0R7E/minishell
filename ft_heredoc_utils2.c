/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils2.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 18:32:25 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/06 08:56:19 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	hd_error_msg(char *msg)
{
	g_info = 1;
	write(1, "\n", 1);
	ft_putstr_fd("minishell: warning: here-document delimited ", 2);
	ft_putstr_fd("by end-of-file (wanted `", 2);
	ft_putstr_fd(msg, 2);
	ft_putstr_fd("')\n\n", 2);
	g_info = 0;
}

int	ft_check_stop_hd(t_info *info, char *line, int fd)
{
	g_info = 0;
	if (info->stop_hd || !line)
	{
		info->stop_hd = 0;
		close (fd);
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
	if (g_info == 1)
	{
		info->stop_hd = 1;
		g_info = 0;
		if (input)
			free(input);
		return (1);
	}
	return (0);
}
