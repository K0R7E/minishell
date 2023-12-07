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

        execve(path, pars->cmd_cmd, info->env);

        // If execve fails, perror will print an error message
        perror("Execution failed");
        exit(EXIT_FAILURE);
    }
    else
    {
        // Parent process
        waitpid(pid, &status, 0);
    }
}

void built_or_exec(t_parsing *pars, t_info *info)
{
    if (pars->cmd_builtin)
    {
        // Implement ft_builtin function to handle built-in commands
        // ft_builtin(pars, info);
    }
    else
    {
        ft_binary(pars, info);
    }
}

void ft_pipes(t_parsing *pars, t_info *info)
{
    pid_t pid;
    int fd[2];
    int i;

    int saved_stdout = dup(1);

    for (i = 0; i < pars->pipes_count; ++i)
    {
        if (pipe(fd) == -1)
        {
            perror("pipe creation failed");
            exit(EXIT_FAILURE);
        }

        pid = fork();
        if (pid == -1)
        {
            perror("fork failed");
            exit(EXIT_FAILURE);
        }

        if (pid == 0)
        {
            // Child process
            if (i < pars->pipes_count - 1)
            {
                if (dup2(fd[1], 1) == -1)
                {
                    perror("dup2 failed for output in child");
                    exit(EXIT_FAILURE);
                }
                close(fd[1]);
            }
            close(fd[0]);

            built_or_exec(pars, info);
            exit(EXIT_SUCCESS);
        }
        else
        {
            // Parent process
            waitpid(pid, NULL, 0);

            if (i < pars->pipes_count - 1)
            {
                if (dup2(fd[0], 0) == -1)
                {
                    perror("dup2 failed for input in parent");
                    exit(EXIT_FAILURE);
                }
                close(fd[1]);
            }
            else
            {
                // If it's the last command, restore stdout
                if (dup2(saved_stdout, 1) == -1)
                {
                    perror("dup2 failed for restoring stdout");
                    exit(EXIT_FAILURE);
                }
            }
        }
    }

    close(saved_stdout);
}

void ft_executor(t_parsing *pars, t_info *info)
{
    int i;

    if (pars->cmd_builtin && strncmp(pars->cmd_builtin[0], "exit", 4) == 0)
        exit(0);
    if (pars->heredoc_delimiter)
        ft_heredoc(pars, info);
    else if (pars->pipes_count > 0)
    {
        for (i = 0; i < pars->pipes_count; ++i)
            ft_pipes(pars, info);
    }
    else
    {
        built_or_exec(pars, info);
    }
}

/* #include "minishell.h"

char	*get_path(t_parsing *pars, t_info *info)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

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
    if (pid == 0)
	{
		if (pars->fd_in != 0)
		{
		    dup2(pars->fd_in, 0);
		    close(pars->fd_in);
		}
		if (pars->fd_out != 1)
		{
		    dup2(pars->fd_out, 1);
		    close(pars->fd_out);
		}
        execve(path, pars->cmd_cmd, info->env);
        perror("Execution failed");
        exit(EXIT_FAILURE);
	} else
	{
        waitpid(pid, &status, 0);
    }
}

void built_or_ecex(t_parsing *pars, t_info *info)
{
	if (pars->cmd_builtin)
	{
		//ft_builtin(pars, info);
	}
	else
		ft_binary(pars, info);
}

void ft_pipes(t_parsing *pars, t_info *info)
{
    pid_t pid;
    int fd[2];
    int i;

    i = -1;
    int saved_stdout = dup(1);  // Save the original standard output

    while (++i < pars->pipes_count)
    {
        if (pipe(fd) == -1)
            exit(0);

        pid = fork();
        if (pid == -1)
            exit(0);

        if (!pid)
        {
            // Child process
            if (i < pars->pipes_count - 1)
            {
                dup2(fd[1], 1);  // Redirect output to the next pipe
                close(fd[1]);   // Close write end in child
            }
            close(fd[0]); // Close unused read end

            built_or_ecex(pars, info);
            exit(0);
        }
        else
        {
            // Parent process
            waitpid(pid, NULL, 0);
            dup2(fd[0], 0); // Redirect input from the previous pipe
            close(fd[1]);  // Close write end in parent
        }
    }

    dup2(saved_stdout, 1);  // Restore the original standard output
    close(saved_stdout);    // Close the duplicated standard output
}



void ft_executor(t_parsing *pars, t_info *info)
{
	int i = -1;

	if (pars->cmd_builtin && ft_strncmp(pars->cmd_builtin[0], "exit", 4) == 0)
		exit(0);
	if (pars->heredoc_delimiter)
		ft_heredoc(pars, info);
	else if (pars->pipes_count > 0)
	{
		//here something with pipes
		while (i++ < pars->pipes_count)
			ft_pipes(pars, info);
	}
	else
	{
		built_or_ecex(pars, info);
	}
} */

