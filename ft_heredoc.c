#include "minishell.h"


void	here_doc(t_parsing *pars, int *fd)
{
	char	*line;

	close(fd[0]);
	while (1)
	{
		line = readline(">");
		if (strcmp(line, pars->heredoc_delimiter) == 0)
		{
			free(line);
			break;
		}
		write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
		free(line);
	}
}

void ft_heredoc(t_parsing *pars, t_info *info)
{
/*     int fd[2];
    char *line;

    (void)info;
    pipe(fd);
    while (1)
    {
        line = readline(">");
        if (strcmp(line, pars->heredoc_delimiter) == 0)
        {
            free(line);
            break;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
	pars->fd_in = fd[0]; */
	int		fd[2];
	pid_t	pid;


	(void)info;
	if (pipe(fd) == -1)
		exit(0);
	pid = fork();
	if (pid == -1)
		exit(0);
	if (!pid)
		here_doc(pars, fd);
	else
	{
		close(fd[1]);
		dup2(fd[0], 0);
		wait(NULL);
	}
}
