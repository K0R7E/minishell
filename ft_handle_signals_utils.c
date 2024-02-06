/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signals_utils.c                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/06 08:58:54 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/06 09:35:09 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_cmd_sig(t_info *info)
{
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_redisplay();
	info->exit_code = 130;
}

void	handle_hd_sig(t_info *info)
{
	g_info = 1;
	ioctl(STDIN_FILENO, TIOCSTI, "\n");
	rl_replace_line("", 0);
	rl_on_new_line();
	info->stop_hd = 0;
	info->exit_code = 130;
}

//Due to the unpredictability of the behavior caused by the ioctl call,
//such strange side effects can occur.

void	handle_default_sig(t_info *info)
{
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
	info->exit_code = 130;
}
