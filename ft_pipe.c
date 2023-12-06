#include "minishell.h"

void ft_pipe(t_parsing *pars, t_info *info)
{
	pid_t pid;
	int fd[2];

	pipe(fd);
	pid = fork();
	if (pid == 0)
	{
		dup2(fd[1], 1);
		close(fd[0]);
		close(fd[1]);
		ft_executor(pars, info);
	}
	else
	{
		dup2(fd[0], 0);
		close(fd[0]);
		close(fd[1]);
		ft_executor(pars, info);
	}

}