/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_handle_signals.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 17:40:17 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/04 14:02:15 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_memdel(void *ptr)
{
	if (ptr)
	{
		free(ptr);
		ptr = NULL;
	}
}

t_info	*handle_sig(int sig, t_info *info_in)
{
	static t_info	*info;

	if (info_in != NULL)
	{
		info = info_in;
		return (info);
	}
	if (info == NULL)
		return (NULL);
	if (sig == SIGINT)
	{
		if (!info->in_hd)
			write(1, "\n", 1);

		if (info->in_cmd)
		{
			rl_replace_line("", 0);
			rl_redisplay();
			info->exit_code = 130; // not work here
			return (info);
		}
		else if (info->in_hd)
		{
			info->stop_hd = 1;
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			info->exit_code = 130;
			return (info);
		}
		else
		{
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			info->exit_code = 130;
			return (info);
		}
	}
/* 	else if (sig == SIGQUIT)
	{
		while (waitpid(-1, NULL, WNOHANG) > 0)
		{
			if (!info->in_cmd && !info->in_hd)
			{
				printf("First\n");
				return (NULL);
			}
			if (info->in_cmd == 1 || info->in_hd == 1)
			{
				printf("Second\n");
				ft_putstr_fd("Quit (core dumped)\n", STDERR_FILENO);
				info->exit_code = 131;
			}
			else
			{
				printf("Third\n");
				return (info);
			}
			return (info);
		}
	} */
	return (info);
}

void	sigquit_handler(int sig)
{
	ft_putstr_fd("Quit: ", STDERR_FILENO);
	ft_putnbr_fd(sig, STDERR_FILENO);
	ft_putchar_fd('\n', STDERR_FILENO);
	exit(131);
}

void	signal_handler(int signal, siginfo_t *info, void *ucontent)
{
	t_info	*info_ptr;

	info_ptr = handle_sig(signal, NULL);
	(void)ucontent;
	(void)info;
	if (info_ptr == NULL)
		return ;
	if (signal == SIGINT)
		handle_sig(signal, info_ptr);
/* 	else if (signal == SIGQUIT)
		handle_sig(signal, info_ptr); */
}

void	config_signals(void)
{
	struct sigaction	sa_newsig;

	ft_memset(&sa_newsig, 0, sizeof(sa_newsig));
	sa_newsig.sa_sigaction = &signal_handler;
	sa_newsig.sa_flags = SA_SIGINFO;
	sigaction(SIGINT, &sa_newsig, NULL);
	signal(SIGQUIT, SIG_IGN);
	//sigaction(SIGINT, &sa_newsig, NULL);
}

/* void	handle_sig(int sig, t_info *info_in)
{
	static t_info	*info;
	if (info_in != NULL)
	{
		info = info_in;
		return ;
	}
	if (sig == SIGINT)
	{
		if (info->in_cmd)
		{
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_redisplay();
			return ;
		}
		else if (info->in_hd)
		{
			info->stop_hd = 1;
			write(1, "\n", 1);
			rl_replace_line("", 0);
			rl_on_new_line();
			return ;
		}
		else
		{
			printf("\n");
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
		}
	}
	else if (sig == SIGQUIT)
	{
		ft_putstr_fd("Quit: ", STDERR_FILENO);
		ft_putnbr_fd(sig, STDERR_FILENO);
		ft_putchar_fd('\n', STDERR_FILENO);
	}
}


void	signal_handler(int signal, siginfo_t *info, void *ucontent)
{
	(void)ucontent;
	(void)info;
	if (signal == SIGINT)
	{
		handle_sig(signal, NULL);
	}
	else if (signal == SIGQUIT)
	{
		handle_sig(signal, NULL);	
	}
	else if (signal == SIGQUIT)
	{
		
	}
}

void	config_signals(void)
{
	struct sigaction	sa_newsig;

	ft_memset(&sa_newsig, 0, sizeof(sa_newsig));
	sa_newsig.sa_sigaction = &signal_handler;
	sa_newsig.sa_flags = SA_SIGINFO;
	sigaction(SIGQUIT, &sa_newsig, NULL);
	sigaction(SIGINT, &sa_newsig, NULL);
} */