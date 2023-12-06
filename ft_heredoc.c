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
            break;
        }
        write(fd[1], line, ft_strlen(line));
        write(fd[1], "\n", 1);
        free(line);
    }
    close(fd[1]);
	pars->fd_in = fd[0];
}
