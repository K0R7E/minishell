#include "minishell.h"

void ft_execute(char *args[], int input_fd, int output_fd)
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
	int pipe_count = 0;
	for (int i = 0; i < arg_count; i++) {
		if (strcmp(args[i], "|") == 0) {
			pipe_count++;
		}
	}

	if (pipe_count > 0) {
		int pipe_fd[2];
		int input_fd = 0;

		for (int i = 0; i < arg_count; i++) {
			if (strcmp(args[i], "|") == 0) {
				args[i] = NULL;

				if (pipe(pipe_fd) == -1) {
					perror("Pipe failed");
					exit(EXIT_FAILURE);
				}

				ft_execute(args + input_fd, input_fd, pipe_fd[1]);

				close(pipe_fd[1]);
				input_fd = pipe_fd[0];
			}
		}

		ft_execute(args + input_fd, input_fd, 1);
	}
}