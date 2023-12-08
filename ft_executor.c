#include "minishell.h"

void ft_binary(char *path, t_parsing *pars, t_info *info)
{
    pid_t pid;
    int status;

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

char *ft_check_dir(t_parsing *pars, t_info *info)
{
	char *path;
	char *tmp;
	int i = 0;

	if (pars->cmd_cmd[0][0] != '/')
	{
		path = ft_strjoin("/usr/bin/", pars->cmd_cmd[i]);
		return (path);
	}
	i = 0;
	if (pars->cmd_cmd[0][0] == '/')
	{
		path = ft_strdup(pars->cmd_cmd[0]);
		return (path);
	}
	else
	{
		tmp = ft_strjoin("/", pars->cmd_cmd[0]);
		while (info->env[i] != NULL)
		{
			if (ft_strncmp(info->env[i], "PWD=", 4) == 0)
			{
				path = ft_strjoin(info->env[i], tmp);
				free(tmp);
				return (path);
			}
			i++;
		}
	}
	return (NULL);
}

void ft_executor(t_parsing *pars, t_info *info)
{
	char	*path;
	if (!pars->cmd_builtin && !pars->args)
		path = ft_check_dir(pars, info);
	if (pars->heredoc_delimiter)
		ft_heredoc(pars, info);
	if (pars->cmd_builtin && ft_strncmp(pars->cmd_builtin[0], "exit", 4) == 0)
		exit(0);
	else if (pars->cmd_builtin)
	{
		ft_builtin(pars, info);
	}
	else
		ft_binary(path, pars, info);
}

