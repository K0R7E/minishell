#include "minishell.h"

int	pipe_wait(int *pid, int amount)
{
	int	i;
	int	status;

	i = 0;
	while (i < amount)
	{
		waitpid(pid[i], &status, 0);
		i++;
	}
	waitpid(pid[i], &status, 0);
/* 	if (WIFEXITED(status))
		g_global.error_num = WEXITSTATUS(status); */
	return (EXIT_SUCCESS);
}

/* void ft_fork(t_info *info, int end[2], int fd_in)
{

} */

void ft_executor(t_pars *pars, t_info *info)
{
	t_pars *tmp;
	int		end[2];
	int		fd_in;

	tmp = pars;
	fd_in = STDIN_FILENO;
	while (tmp)
	{
		if (tmp->next)
			pipe(end);
		//send_heredoc();
		//ft_fork();
		close(end[1]);
/* 		if (tmp->prev)
			close(fd_in); */
		//fd_in = check_fd_heredoc(tools, end, tools->simple_cmds);
		if (tmp->next)
			tmp = tmp->next;
		else
			break ;
	}
	pipe_wait(info->pid, info->command_count -1);
	ft_command_execute(tmp, info->command_count, info);

}
