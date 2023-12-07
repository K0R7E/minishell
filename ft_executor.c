#include "minishell.h"

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

void ft_executor(t_parsing *pars, t_info *info)
{

	if (pars->cmd_builtin && ft_strncmp(pars->cmd_builtin[0], "exit", 4) == 0)
		exit(0);
	if (pars->heredoc_delimiter)
		ft_heredoc(pars, info);
	else if (pars->cmd_builtin)
	{
		//ft_builtin(pars, info);
	}
	else
		ft_binary(pars, info);
}

