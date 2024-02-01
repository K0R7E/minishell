/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_signals.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:06:20 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/01 17:10:13 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

/* int g_global = 0;

void ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}	

void	sig_int(int sig)
{
	(void)sig;
	if (g_global != 1)
	{
		ft_putstr_fd("\b\b  ", 2);
		ft_putstr_fd("\n", 2);
		ft_putstr_fd("\033[0;36m\033[1m🤬 minishell ▸ \033[0m", 2);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", 2);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char	*nbr;

	nbr = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", 2);
		ft_putendl_fd(nbr, 2);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b  \b\b", 2);
	ft_memdel(nbr);
} */



t_global	g_global;

void	sigint_handler(int sig)
{
	(void)sig;
	if (!g_global.in_hd)
	{
		ft_putstr_fd("\n", STDERR_FILENO);
	}
	if (g_global.in_cmd)
	{
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	else if (g_global.in_hd)
	{
		g_global.stop_hd = 1;
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
		return ;
	}
	else
	{
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
}

void	init_signals(void)
{
	signal(SIGINT, sigint_handler);
	signal(SIGQUIT, sigquit_handler);
}
