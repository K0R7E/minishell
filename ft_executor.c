#include "minishell.h"

char *get_path(char *token, t_info *info)
{
    int i;
    char *exec;
    char **allpath;
    char *path_part;
    char **s_cmd;

    i = -1;
	
    allpath = ft_split(info->path, ':');
    s_cmd = ft_split(token, ' ');
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
    return (token);
}

void ft_binary(char *path, t_parsing *pars, t_info *info)
{
	pid_t pid;
	int status;

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
		free(path);
}

void executeCommand(char *path, t_parsing *pars, t_info *info)
{

    int (*pipes)[2] = malloc(sizeof(int[pars->pipes_count][2]));
    if (pipes == NULL) {
        perror("malloc");
        exit(EXIT_FAILURE);
    }

    pid_t child_pid;

    // Create pipes
    for (int i = 0; i < pars->pipes_count - 1; ++i) {
        if (pipe(pipes[i]) == -1) {
            perror("pipe");
            exit(EXIT_FAILURE);
        }
    }

    // Fork processes
    for (int i = 0; i < pars->pipes_count; ++i) {
        if ((child_pid = fork()) == -1) {
            perror("fork");
            exit(EXIT_FAILURE);
        }

        if (child_pid == 0) { // Child process
            // Redirect input from previous pipe (if not the first stage)
            if (i > 0) {
                dup2(pipes[i - 1][0], STDIN_FILENO);
                close(pipes[i - 1][0]);
                close(pipes[i - 1][1]);
            }

            // Redirect output to next pipe (if not the last stage)
            if (i < pars->pipes_count - 1) {
                dup2(pipes[i][1], STDOUT_FILENO);
                close(pipes[i][0]);
                close(pipes[i][1]);
            }

            // Execute command
			ft_binary(path, pars, info);
			exit(EXIT_SUCCESS);
        }
    }

    // Close all pipes in the parent process
    for (int i = 0; i < pars->pipes_count - 1; ++i) {
        close(pipes[i][0]);
        close(pipes[i][1]);
    }

    // Wait for all child processes to finish
    for (int i = 0; i < pars->pipes_count; ++i) {
        wait(NULL);
    }

    free(pipes); // Free dynamically allocated memory
}

void ft_executor(t_parsing *pars, t_info *info)
{
	t_lexer *tokens;
	int i = -1;

	tokens = &pars->lexer;
	if (pars->cmd_builtin && strncmp(pars->cmd_builtin[0], "exit", 4) == 0)
		exit(0);
	if (pars->heredoc_delimiter)
		ft_heredoc(pars, info);
	if (pars->pipes_count == 0)
	{
		if (pars->cmd_builtin)
		{
			ft_builtin(pars, info);
		}
		else
			ft_binary(pars->cmd_path[0], pars, info);
	}
	else
	{
		while (++i < pars->pipes_count)
		{
			executeCommand(pars->cmd_path[i], pars, info);	
		}
		if (pars->cmd_builtin)
		{
			ft_builtin(pars, info);
		}
		else
			ft_binary(pars->cmd_path[i], pars, info);
	}
}

