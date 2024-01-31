/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor_utils.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 09:34:55 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/31 14:22:46 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
#include <asm-generic/errno-base.h>
#include <errno.h>

int	is_builtin_1(char *command)
{
	if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	return (0);
}

int	is_builtin_2(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

void	setup_fd(int fd, int std_no)
{
	if (fd != std_no)
	{
		errno = 0;
		dup2(fd, std_no);
		close(fd);
	}
}

int	setup_file_fd(int file_fd, char *file, int fd, int std_no)
{
	if (file)
	{
		file_fd = fd;
		if (file_fd == -1)
		{
			perror("minishell");
			exit(EXIT_FAILURE);
		}
		errno = 0;
		dup2(file_fd, std_no);
		close(file_fd);
	}
	return (std_no);
}

int	is_builtin(char *command, char **cmd_args)
{
	return (is_builtin_1(command)
		|| (ft_strncmp(command, "export", 7) == 0
			&& cmd_args[1] == NULL));
}
