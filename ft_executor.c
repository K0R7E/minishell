#include "minishell.h"

void ft_binary(char *path, t_parsing *pars, t_info *info);
int ft_count_pipes(t_parsing *pars);
void handle_pipes(t_parsing *pars);

void ft_executor(t_parsing *pars, t_info *info)
{
	int pipe_count = ft_count_pipes(pars);

	if (strcmp(pars->args[0], "exit") == 0)
		exit(0);
	if (pars->heredoc_delimiter)
		ft_heredoc(pars, info);
	if (pipe_count == 0)
	{
		//ft_builtin(pars);
		ft_binary(pars->cmd_path[0], pars, info);
	}
	else if (pipe_count > 0)
	{
		handle_pipes(pars);

	}
	else
		printf("Error: ft_executor\n");
}




void ft_binary(char *path, t_parsing *pars, t_info *info)
{
    pid_t pid;
    int status;

    pid = fork();
    if (pid == 0) {
        if (pars->fd_in != 0) {
            dup2(pars->fd_in, 0);
            close(pars->fd_in);
        }
        if (pars->fd_out != 1) {
            dup2(pars->fd_out, 1);
            close(pars->fd_out);
        }
        execve(path, pars->args, info->env);
        perror("Execution failed");
        exit(EXIT_FAILURE);
    } else if (pid < 0) {
        perror("Fork failed");
        exit(EXIT_FAILURE);
    } else {
        waitpid(pid, &status, 0);
    }
}

int ft_count_pipes(t_parsing *pars)
{
	int i = 0;
	int pipe_count = 0;

	while (pars->args[i] != NULL) {
		if (strcmp(pars->args[i], "|") == 0) {
			pipe_count++;
		}
		i++;
	}
	return (pipe_count);
}

void handle_pipes(t_parsing *pars)
{
    int i = 0;
    int j = 0;
    int pipe_count = ft_count_pipes(pars);
    int arg_count = 0;

    if (pipe_count > 0) {
        int pipe_fd[2];
        int input_fd = 0;
        j = 0;

        for (i = 0; i < arg_count; i++) {
            if (strcmp(pars->args[i], "|") == 0) {
                pars->args[i] = NULL;
                if (pipe(pipe_fd) == -1) {
                    perror("Pipe failed");
                    exit(EXIT_FAILURE);
                }
                ft_binary(pars->cmd_path[0], pars, NULL);
                close(pipe_fd[1]);
                input_fd = pipe_fd[0];
            }
            j++;
        }

        ft_binary(pars->cmd_path[0], pars, NULL);
    }
}