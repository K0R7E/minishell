#include "minishell.h"


int	is_builtin_a(char *command)
{
	if (ft_strncmp(command, "echo", 5) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 4) == 0)
		return (1);
	if (ft_strncmp(command, "export", 7) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 6) == 0)
		return (1);
	if (ft_strncmp(command, "env", 4) == 0)
		return (1);
	if (ft_strncmp(command, "exit", 5) == 0)
		return (1);
	return (0);
}

void ft_fork(t_pars *tmp, t_info *info, int fd_in, int fd_out)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (fd_in != 0)
        {
            dup2(fd_in, STDIN_FILENO);
            close(fd_in);
        }
        if (fd_out != 1)
        {
            dup2(fd_out, STDOUT_FILENO);
            close(fd_out);
        }
		if (tmp->out_file)
        {
            int file_fd = tmp->fd_out;
            if (file_fd == -1)
            {
                perror("Error opening output file");
                exit(EXIT_FAILURE);
            }
            dup2(file_fd, STDOUT_FILENO);
            close(file_fd);
        }
		if (tmp->in_file)
        {
            int file_fd = tmp->fd_in;
            if (file_fd == -1)
            {
                perror("Error opening output file");
                exit(EXIT_FAILURE);
            }
            dup2(file_fd, STDIN_FILENO);
            close(file_fd);
        }
		if (is_builtin_a(tmp->command))
		{
			ft_builtin(tmp, info);
		} else if (execve(tmp->cmd_path, tmp->cmd_args, env_conversion_back(info)) == -1)
        {
            ft_putstr_fd("Error: command not found: ", STDERR_FILENO);
            ft_putendl_fd(tmp->command, STDERR_FILENO);
            exit(EXIT_FAILURE);
        }
        exit(EXIT_SUCCESS);
    }
    else if (pid < 0)
    {
        ft_putendl_fd("Error: fork failed", STDERR_FILENO);
        exit(EXIT_FAILURE);
    }
    else
    {
        waitpid(pid, &status, 0);
        if (fd_in != 0) close(fd_in);
        if (fd_out != 1) close(fd_out);
    }
}

void ft_executor(t_pars *pars, t_info *info)
{
    t_pars *tmp;
    int fd[2], fd_in = 0, fd_out = 1;

    tmp = pars;
    while(tmp)
    {
        pipe(fd);
        if (tmp->next == NULL)
        {
            fd_out = 1;
        }
        else
        {
            fd_out = fd[1];
        }
        ft_fork(tmp, info, fd_in, fd_out);
        close(fd[1]);
        if (fd_in != 0) close(fd_in);
        fd_in = fd[0];
        tmp = tmp->next;
    }
}

