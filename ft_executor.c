#include "minishell.h"

void ft_binary(char *path, t_parsing *pars, t_info *info);

char *ft_check_dir(t_parsing *pars, t_info *info)
{
	char *path;
	char *tmp;
	int i = 0;

	if (pars->args[0][0] != '/')
	{
		path = ft_strjoin("/usr/bin/", pars->args[i]);
		return (path);
	}
	i = 0;
	if (pars->args[0][0] == '/')
	{
		path = ft_strdup(pars->args[0]);
		return (path);
	}
	else
	{
		tmp = ft_strjoin("/", pars->args[0]);
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
	char	*path = ft_check_dir(pars, info);
/* 	printf("path: %s\n", path); */

	if (pars->heredoc_delimiter)
		ft_heredoc(pars, info);
	if (strcmp(pars->args[0], "exit") == 0)
		exit(0);
	else if (strcmp(pars->args[0], "clear") == 0)
		printf("\033[2J\033[1;1H");
	else if (pars->cmd_builtin)
	{
		//ft_builtin(pars, info);
	}
	else
		ft_binary(path, pars, info);
}



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
        execve(path, pars->args, info->env);
        perror("Execution failed");
        exit(EXIT_FAILURE);
	} else
	{
        waitpid(pid, &status, 0);
    }
}

int ft_count_pipes(t_parsing *pars)
{
	int i = 0;
	int pipe_count = 0;

	if (pars->args == NULL)
		return (0);
	while (pars->args[i] != NULL) {
		if (strcmp(pars->args[i], "|") == 0) {
			pipe_count++;
		}
		i++;
	}
	return (pipe_count);
}

