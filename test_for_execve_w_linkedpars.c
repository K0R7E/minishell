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

void ft_proc_no(t_pars **pars, t_info *info, int fd)
{
	t_pars *tmp;
	pid_t pid;

	tmp = *pars;
    pid = fork();
    if (pid < 0)
    {
        perror("Error");
        exit(0);
    }
    if (pid == 0)
    {
        // Child process
		if (fd != -1)
		{
			dup2(fd, STDOUT_FILENO);
        	close(fd);
		}
        if (execve(tmp->cmd_path, tmp->args, info->env) == -1)
        {
            perror("Error");
            exit(0);
        }
    }
    waitpid(pid, &info->exit_status, 0);
	if (fd != -1)
		close(fd);
}




void ft_bin(t_pars **pars, t_info *info)
{
    t_pars *tmp;
    t_pars *exec_node;

    tmp = *pars;
    exec_node = tmp;

    // Find the last node with TokenTypeOutputRedirect
	if (tmp->next && tmp->next->type != TokenTypePipe)
	{
    	while (tmp->next && (tmp->next->type == 2 || tmp->next->type == 4))
    	    tmp = tmp->next;
		ft_proc_no(&exec_node, info, tmp->fd_out);
	}
	else
		ft_proc_no(&exec_node, info, -1);
}

void ft_idk(t_pars *pars, t_info *info, int num)
{
	t_pars *tmp;
	int i = num;
	int fd[2];

	tmp = pars;
	pid_t pid[num];
	pipe(fd);
	while (num > 0 && tmp)
	{
		pid[num] = fork();
		if (pid[num] < 0)
		{
			perror("Error");
			exit(0);
		}
		if (pid[num] == 0)
		{
			// Child process
			dup2(fd[1], STDOUT_FILENO);
			close(fd[1]);
			close(fd[0]);
			ft_bin(&tmp, info);
		}
		else
		{
			// Parent process
			dup2(fd[0], STDIN_FILENO);
			close(fd[0]);
			close(fd[1]);
		}
		num--;
		close(fd[1]);
		if (tmp->next && tmp->next->type == TokenTypePipe)
			tmp = tmp->next;
		tmp = tmp->next;
	}

	while (i > num)
	{
		/* close(fd[1]); */
		close(fd[0]);
		close(fd[1]);
		waitpid(pid[num], &info->exit_status, 0);
		num++;
	}

}

void ft_test_executor(t_pars **pars, t_info *info)
{
	t_pars *tmp;

	tmp = *pars;
	
	if (info->command_count == 0)
		return ;
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
			ft_bin(&tmp, info);
		}
	}
	else
	{
		ft_idk(tmp, info, info->command_count);
		//ft_bin(&tmp, info);
	}
}



/* void ft_test_bin(t_pars **pars, t_info *info)
{
    t_pars *tmp;
    pid_t pid;
    //char *args[4];

    tmp = *pars;
	//dup2(tmp->fd_pipe[1], tmp->fd_pipe[0]);
	//close(tmp->fd_pipe[1]);
    pid = fork();

	if (pid < 0)
    {
        perror("Error");
        exit(0);
    }
    if (pid == 0)
    {
		//close(tmp->fd_pipe[0]);
    	//args[0] = "/usr/bin/ls";
        //args[1] = "/bin/";
		//args[2] = "-l";
		//args[3] = NULL;
		dup2(tmp->fd_pipe[1], STDOUT_FILENO);
		close(tmp->fd_pipe[0]);
		close(tmp->fd_pipe[1]);
        if (execve(tmp->cmd_path, tmp->args, info->env) == -1)
        {
            perror("Error");
            exit(0);
        }
    } else
    	waitpid(pid, &info->exit_status, 0);
		dup2(tmp->fd_pipe[0], STDIN_FILENO);
		close(tmp->fd_pipe[1]);
		close(tmp->fd_pipe[0]);
	//close(tmp->fd_pipe[0]);
}

void ft_test_pipe(t_pars *pars, t_info *info)
{
	t_pars *tmp;
	pid_t pid;
	// int stdin_saved;
	// int stdout_saved;

	tmp = pars;
	pipe(tmp->fd_pipe);
	pid = fork();
	if (pid < 0)
	{
		perror("Error");
		exit(0);
	}
	if (pid == 0)
	{
		close(tmp->fd_pipe[0]);
		//stdout_saved = dup(STDOUT_FILENO);
		dup2(tmp->fd_pipe[1], STDOUT_FILENO);
		close(tmp->fd_pipe[1]);
		if ((execve(tmp->cmd_path, tmp->args, info->env) == -1))
		{
			perror("Error");
			exit(0);
		}
		//dup2(stdout_saved, STDOUT_FILENO);
		//close(stdout_saved);
	}
	else
	{
		waitpid(pid, &info->exit_status, 0);
		dup2(tmp->fd_pipe[0], STDIN_FILENO);
		close(tmp->fd_pipe[1]);
		//stdin_saved = dup(STDIN_FILENO);
		//dup2(tmp->fd_pipe[0], STDIN_FILENO);
		close(tmp->fd_pipe[0]);
		// close(tmp->fd_pipe[0]);
		//dup2(stdin_saved, STDIN_FILENO);
		//close(stdin_saved);
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
		//puts("In the beginning of the loop");
		if (info->command_count == 0)
			break ;
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
				//puts("Here");
				ft_test_bin(&tmp, info);
			}
		}
		else
		{

			ft_test_pipe(tmp, info);
			//if (tmp->next == NULL)
			//	dup2(tmp->fd_pipe[0], STDIN_FILENO);
			if (tmp->next && tmp->next->type == TokenTypePipe)
				tmp = tmp->next;
			//ft_test_bin(&tmp, info);
			close(tmp->fd_pipe[1]);
		}
		info->command_count--;
		tmp = tmp->next;
	}
} */