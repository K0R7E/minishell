#include "minishell.h"

void	ft_close(int fd)
{
	if (fd > 0)
		close(fd);
}