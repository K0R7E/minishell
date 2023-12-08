#include "minishell.h"

char *get_path(t_parsing *pars, t_info *info)
{
    int i;
    char *exec;
    char **allpath;
    char *path_part;
    char **s_cmd;

    i = -1;
    allpath = ft_split(info->path, ':');
    s_cmd = ft_split(pars->cmd_cmd[0], ' ');
    while (allpath[++i])
    {
        path_part = ft_strjoin(allpath[i], "/");
        exec = ft_strjoin(path_part, s_cmd[0]);
        free(path_part);
        if (access(exec, F_OK | X_OK) == 0)
        {
            return (exec);
        }
        free(exec);
    }
    return (pars->cmd_cmd[0]);
}

void ft_binary(t_parsing *pars, t_info *info)
{
	pid_t pid;
	int status;
	char *path;

	path = get_path(pars, info);

	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// Child process
		if (pars->fd_in != 0)
		{
			if (dup2(pars->fd_in, 0) == -1)
			{
				perror("dup2 failed for input");
				exit(EXIT_FAILURE);
			}
			close(pars->fd_in);
		}
		if (pars->fd_out != 1)
		{
			if (dup2(pars->fd_out, 1) == -1)
			{
				perror("dup2 failed for output");
				exit(EXIT_FAILURE);
			}
			close(pars->fd_out);
		}
		if (execve(path, pars->cmd_cmd, info->env) == -1)
		{
			perror("Execution failed");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		// Parent process
		waitpid(pid, &status, 0);
	}
}

void executeCommand(t_parsing *pars, t_info *info)
{
	pid_t pid;

	if (pipe(pars->fd_pipe) == -1)
	{
		perror("pipe failed");
		exit(EXIT_FAILURE);
	}
	pid = fork();
	if (pid == -1)
	{
		perror("fork failed");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		// Child process
		ft_close(pars->fd_pipe[0]);
		dup2(pars->fd_pipe[1], 1);
		ft_binary(pars, info);
	}
	else
	{
		// Parent process
		//waitpid(pid, NULL, WNOHANG); // if -1 is passed as the option, waitpid() will wait for any child process to end
		close(pars->fd_pipe[1]);
		dup2(pars->fd_pipe[0], 0);
	}
}

void ft_executor(t_parsing *pars, t_info *info)
{
	t_lexer *tokens;
	int i;

	tokens = &pars->lexer;
	i = -1;
	if (pars->cmd_builtin && strncmp(pars->cmd_builtin[0], "exit", 4) == 0)
		exit(0);
	if (pars->heredoc_delimiter)
		ft_heredoc(pars, info);
	if (pars->pipes_count == 0)
	{
		if (pars->cmd_builtin)
		{
			//ft_builtin(pars, info);
		}
		else
			ft_binary(pars, info);
	}
	else
	{
		while (++i < pars->pipes_count)
		{
			executeCommand(pars, info);	
		}
		if (pars->cmd_builtin)
		{
			//ft_builtin(pars, info);
		}
		else
			ft_binary(pars, info);
	}
}

