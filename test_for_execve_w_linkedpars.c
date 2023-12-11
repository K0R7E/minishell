#include "minishell.h"
#include <unistd.h>

int is_builtin (t_pars **pars)
{
	t_pars *tmp;

	tmp = *pars;
	if (strncmp(tmp->command, "pwd", 3) == 0)
		return (1);
	else if (strncmp(tmp->command, "echo", 4) == 0)
		return (1);
	else if (strncmp(tmp->command, "cd", 2) == 0)
		return (1);
	else if (strncmp(tmp->command, "env", 3) == 0)
		return (1);
	else if (strncmp(tmp->command, "export", 6) == 0)
		return (1);
	else if (strncmp(tmp->command, "unset", 5) == 0)
		return (1);
	else if (strncmp(tmp->command, "exit", 4) == 0)
		return (1);
	else
		return (0);
}

void ft_test_bin(t_pars **pars, t_info *info)
{
    t_pars *tmp;
    pid_t pid;
    //char *args[4];

    tmp = *pars;
    pid = fork();
    if (pid == 0)
    {
/*      args[0] = "/usr/bin/ls";
        args[1] = "/bin/";
		args[2] = "-l";
		args[3] = NULL; */

        if (execve(tmp->cmd_path, tmp->args, info->env) == -1)
        {
            perror("Error");
            exit(0);
        }
    }
    else if (pid < 0)
    {
        perror("Error");
        exit(0);
    }
    else
        waitpid(pid, &info->exit_status, 0);
}

void ft_test_pipe(t_pars *pars, t_info *info)
{
	t_pars *tmp;
	pid_t pid;

	tmp = pars;
	pipe(tmp->fd_pipe);
	pid = fork();
	if (pid == 0)
	{
		dup2(tmp->fd_pipe[1], STDOUT_FILENO);
		close(tmp->fd_pipe[0]);
		close(tmp->fd_pipe[1]);
		if ((execve(tmp->cmd_path, tmp->args, info->env) == -1))
		{
			perror("Error");
			exit(0);
		}
	}
	else if (pid < 0)
	{
		perror("Error");
		exit(0);
	}
	else
	{
		waitpid(pid, &info->exit_status, 0);
		dup2(tmp->fd_pipe[0], STDIN_FILENO);
		close(tmp->fd_pipe[0]);
		close(tmp->fd_pipe[1]);
	}
}

void ft_test_executor(t_pars **pars, t_info *info)
{
	t_pars *tmp;
	int i;

	tmp = *pars;
	i = info->command_count;
	//ft_print_pars(tmp);
	//printf("command_count: %d\n", info->command_count);
	while (tmp != NULL)
	{
		if (tmp->command && strncmp(tmp->command, "exit", 4) == 0)
			exit(0);
		else if (info->command_count == 1)
		{
			if (is_builtin(&tmp) == 1)
			{
				//printf("builtin\n");
				//ft_builtin(tmp, info);
			}
			else
			{
				//printf("not builtin\n");
				ft_test_bin(&tmp, info);
			}
		}
		else
		{

			ft_test_pipe(tmp, info);
			if (tmp->next && tmp->next->type == TokenTypePipe)
				tmp = tmp->next;
			//ft_test_bin(&tmp, info);
		}
		info->command_count--;
		tmp = tmp->next;
	}
}