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

    int tmp_fd = open("/tmp/heredoc_temp_file", O_CREAT | O_WRONLY | O_TRUNC, 0644);
    if (tmp_fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    while (1)
    {
        ssize_t bytesRead = read(fd[0], line, BUFFER_SIZE);
        if (bytesRead <= 0)
            break;
        write(tmp_fd, line, bytesRead);
    }

    close(fd[0]);
    close(tmp_fd);

    tmp_fd = open("/tmp/heredoc_temp_file", O_RDONLY);
    if (tmp_fd == -1)
    {
        perror("open");
        exit(EXIT_FAILURE);
    }

    dup2(tmp_fd, STDIN_FILENO);
    close(tmp_fd);

    char buffer[BUFFER_SIZE];
    while (1)
    {
        ssize_t bytesRead = read(STDIN_FILENO, buffer, BUFFER_SIZE);
        if (bytesRead <= 0)
            break;
        write(STDOUT_FILENO, buffer, bytesRead);
    }
}
