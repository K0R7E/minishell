#include "minishell.h"

int	ft_redir_heredoc(t_pars *pars, t_info *info, int i, int count)
{
	int		fd;
	char	*line;
	char	*str;
	/* char	*hd_delimiter; */

	(void)info;
	fd = open("/tmp/temp8726343", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", ".tmp");
		info->exit_status = 1;
		return (1);
	}
	g_global.in_hd = 1;
/* 	hd_delimiter = ft_strdup(pars->args[i + 1]);
	if (hd_delimiter == 0)
	{
		free(hd_delimiter);
		ft_error_message(pars, info);
	} */
	if (info->hd_quote == 1)
		pars->args[i + 1] = remove_quotes(pars->args[i + 1]);
	while (!g_global.stop_hd)
	{
		line = readline("> ");
		if (g_global.stop_hd)
		{
        	free(line);
        	break ;
		}
		if (ft_strncmp_12(line, pars->args[i + 1], ft_strlen(pars->args[i + 1])) == 0)
			break ;
		str = ft_strjoin(line, "\n");
		if (str == NULL)
			ft_error_message(pars, info);
		if (info->hd_quote == 0)
			str = replace_dollar_hedoc(str, info);
		write(fd, str, ft_strlen(str));
		free(line);
		free(str);
	}
	close(fd);
	g_global.in_hd = 0;
	if (g_global.stop_hd || !line)
		return (1);
	if (i == count)
	{
		pars->fd_in = open("/tmp/temp8726343", O_RDONLY);
		pars->in_file = ft_strdup("/tmp/temp8726343");
		if (pars->in_file == NULL)
			ft_error_message(pars, info);

	}
	return (0);
}