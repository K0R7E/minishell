/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils2.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 19:30:57 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/06 11:22:49 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	close_fds_from_list(int in, int out, int ft_pip, int fd_in)
{
	if (in != 0 && in != 1)
		close(in);
	if (out != 0 && out != 1)
		close(out);
	close(ft_pip);
	if (fd_in != 0)
		close(fd_in);
}

void	setup_fd_2(int fd_out, int fd_pipe[2])
{
	fd_out = 1;
	close (fd_pipe[1]);
	close (fd_pipe[0]);
}

int	should_move_to_next(t_pars *tmp)
{
	if (!tmp->cmd_args)
	{
		if (tmp->next)
			return (1);
		else
			return (2);
	}
	return (0);
}

void	ft_shit(int tmp_fd_in)
{
	close (tmp_fd_in);
	exit(EXIT_SUCCESS);
}
