#include "minishell.h"

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
} */