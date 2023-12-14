#include "minishell.h"

/* int	is_builtin(char *command)
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


void ft_command_execute(t_pars *node, int numsimplecommands, t_info *info)
{
	int tmpin=dup(0);
	int tmpout=dup(1);
	int ret;
	int fdout;
	int fdin;
	int i;

	if (node->in_file)
		fdin = node->fd_in;
	else
		fdin = dup(tmpin);
	for(i = 0; i < numsimplecommands; i++)
	{
 		dup2(fdin, 0);
		close(fdin);
		if (i == numsimplecommands -1)
		{
			// Last simple command 
			if(node->out_file)
			{
				fdout = node->fd_out;
			}
			else 
			{
			// Use default output
			fdout = dup(tmpout);
			}
		}
		else 
		{
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}
		dup2(fdout,1);
		close(fdout);

		// Create child process
		ret=fork();
		if(ret==0) 
		{
			if (is_builtin(node->command))
				ft_builtin(node, info);
			else
				execve(node->cmd_path, node->cmd_args, env_conversion_back(info));
			exit(1);
		}
	} //  for

	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);

	// Wait for last command
	waitpid(ret, 0, 0);
} */


void ft_fork(t_pars *tmp, t_info *info, int fd[2])
{
    pid_t pid;
    int status;
	int fdin;
	int fdout;
	int tmpin = dup(STDIN_FILENO);
	int tmpout = dup(STDOUT_FILENO);
	
	if (tmp->in_file)
		fdin = tmp->fd_in;
	else
		fdin = fd[0];
	if (tmp->out_file)
		fdout = tmp->fd_out;
	else
		fdout = fd[1];

	
	
    pid = fork();
    if (pid == 0)
    {
        if (tmp->next != NULL)
        {
            close(fd[0]);
            dup2(fdout, STDOUT_FILENO);
            close(fd[1]);
        }
        if (tmp->prev != NULL)
        {
            close(fd[1]);
            dup2(fdin, STDIN_FILENO);
            close(fd[0]);
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
        if (execve(tmp->cmd_path, tmp->cmd_args, env_conversion_back(info)) == -1)
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
		dup2(tmpin,0);
		dup2(tmpout,1);
		close(tmpin);
		close(tmpout);
        waitpid(pid, &status, 0);
        if (tmp->next != NULL)
            close(fd[1]);
        if (tmp->prev != NULL)
            close(fd[0]);
    }
}

/* void ft_fork(t_pars *tmp, t_info *info, int fd[2])
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0)
    {
        if (tmp->next != NULL)
        {
            close(fd[0]);
            dup2(fd[1], STDOUT_FILENO);
            close(fd[1]);
        }
        if (tmp->prev != NULL)
        {
            close(fd[1]);
            dup2(fd[0], STDIN_FILENO);
            close(fd[0]);
        }
        if (execve(tmp->cmd_path, tmp->cmd_args, env_conversion_back(info)) == -1)
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
        if (tmp->next != NULL)
            close(fd[1]);
        if (tmp->prev != NULL)
            close(fd[0]);
    }
} */

void ft_executor(t_pars *pars, t_info *info)
{
	t_pars *tmp;
	int fd[2];

	tmp = pars;
	while(tmp)
	{
		if (tmp->next != NULL)
			pipe(fd);
		ft_fork(tmp, info, fd);
		tmp = tmp->next;
	}
}

