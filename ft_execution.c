#include "libft/libft.h"
#include "minishell.h"

void ft_execute(char *args[], int input_fd, int output_fd);
void ft_heredoc(t_parsing *pars, t_info *info);

void ft_executor(t_parsing *pars, t_info *info)
{
	if (pars->heredoc_delimiter)
		ft_heredoc(pars, info);
	//ft_redir_check(pars, info);
	//ft_execution(pars, info);
}

void ft_heredoc(t_parsing *pars, t_info *info)
{
	int fd[2];
	char *line;

	(void)info;
	pipe(fd);
	while (1)
	{
		line = readline(">");
		if (strcmp(line, pars->heredoc_delimiter) == 0)
		{
			free(line);
			break ;
		}
		write(fd[1], line, ft_strlen(line));
		write(fd[1], "\n", 1);
		free(line);
	}
	close(fd[1]);
	pars->fd_in = fd[0];
}

/* void ft_execute(char *args[], int input_fd, int output_fd)
{
	pid_t pid = fork();

	if (pid < 0) {
		perror("Fork failed");
		exit(EXIT_FAILURE);
	}

	if (pid == 0) {
		// Child process
		if (input_fd != 0) {
			dup2(input_fd, 0);
			close(input_fd);
		}

		if (output_fd != 1) {
			dup2(output_fd, 1);
			close(output_fd);
		}

		execve(args[0], args, NULL);
		perror("Execution failed");
		exit(EXIT_FAILURE);
	} else {
		// Parent process
		wait(NULL);
	}
}

void handle_pipes(char *args[], int arg_count)
{
	int i = 0;
	int j = 0;
	int pipe_count = 0;
	while (i < arg_count)
	{
		if (strcmp(args[i], "|") == 0)
			pipe_count++;
		i++;
	}

	if (pipe_count > 0)
	{
		int pipe_fd[2];
		int input_fd = 0;
		j = 0;
		while  (j < arg_count)
		{
			if (strcmp(args[i], "|") == 0)
			{
				args[i] = NULL;
				if (pipe(pipe_fd) == -1)
				{
					perror("Pipe failed");
					exit(EXIT_FAILURE);
				}
				ft_execute(args + input_fd, input_fd, pipe_fd[1]);
				close(pipe_fd[1]);
				input_fd = pipe_fd[0];
			}
			j++;
		}

		ft_execute(args + input_fd, input_fd, 1);
	}
}

int ft_arrylen(char **pars)
{
	int i;

	i = 0;
	while (pars[i])
	{
		i++;
	}
	return (i);
} */