/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_executor.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 18:16:57 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/07 09:38:03 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	handle_execve_error(char *command, char **env)
{
	ft_putstr_fd("Error: command not found: ", STDERR_FILENO);
	ft_putendl_fd(command, STDERR_FILENO);
	ft_free_array(env);
	exit(127);
}

void	handle_child_process(t_pars *tmp, t_info *info, int fd_in, int fd_out)
{
	int		ret;
	int		file_fd;
	char	**env;

	setup_fd(&fd_in, STDIN_FILENO);
	setup_fd(&fd_out, STDOUT_FILENO);
	setup_file_fd(&file_fd, tmp->out_file, tmp->fd_out, STDOUT_FILENO);
	setup_file_fd(&file_fd, tmp->in_file, tmp->fd_in, STDIN_FILENO);
	if (is_builtin(tmp->command, tmp->cmd_args))
	{
		ret = ft_builtin(tmp, info);
		exit(ret);
	}
	else if (is_builtin_2(tmp->command) && info->command_count == 1)
		exit(EXIT_SUCCESS);
	env = env_conversion_back(info);
	if (execve(tmp->cmd_path, tmp->cmd_args, env) == -1)
		handle_execve_error(tmp->command, env);
	ft_free_array(env);
	exit(EXIT_SUCCESS);
}

void	handle_parent_proc(pid_t pid, t_info *info, int fd_in, int fd_out)
{
	int		status;
	t_pars	*tmp;

	tmp = *info->pars_ptr;
	waitpid(pid, &status, 0);
	if (is_builtin_2(tmp->command) && info->command_count == 1)
	{
		if (ft_strncmp(tmp->command, "export", 7) != 0
			|| (ft_strncmp(tmp->command, "export", 7) == 0
				&& tmp->cmd_args[1] != NULL))
			info->exit_code = ft_builtin(tmp, info);
	}
	else
	{
		if (WIFEXITED(status))
			info->exit_code = WEXITSTATUS(status);
		else if (WIFSIGNALED(status))
			info->exit_code = 128 + WTERMSIG(status);
	}
	if (fd_in != 0)
		close(fd_in);
	if (fd_out != 1)
		close(fd_out);
}

void	ft_fork(t_pars *tmp, t_info *info, int fd_in, int fd_out)
{
	pid_t	pid;

	if (tmp->command == NULL || tmp->command[0] == '\0')
		return ;
	pid = fork();
	if (pid == 0)
		handle_child_process(tmp, info, fd_in, fd_out);
	else if (pid < 0)
	{
		ft_putendl_fd("Error: fork failed", STDERR_FILENO);
		exit(EXIT_FAILURE);
	}
	else
		handle_parent_proc(pid, info, fd_in, fd_out);
}

void	ft_executor(t_pars *pars, t_info *info)
{
	t_pars	*tmp;
	int		fd[2];
	int		fd_in;
	int		fd_out;

	fd_in = 0;
	fd_out = 1;
	tmp = pars;
	g_global.in_cmd = 1;
	while (tmp)
	{
		pipe(fd);
		if (tmp->next == NULL)
			fd_out = 1;
		else
			fd_out = fd[1];
		ft_fork(tmp, info, fd_in, fd_out);
		close(fd[1]);
		if (fd_in != 0)
			close(fd_in);
		fd_in = fd[0];
		tmp = tmp->next;
	}
	g_global.in_cmd = 0;
}
