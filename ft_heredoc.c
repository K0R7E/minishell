/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:10:56 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/03 16:15:33 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_hd(char *line, char *str)
{
	free(line);
	free(str);
}

char	*ft_str_123(t_pars *pars, t_info *info, char *str, char *line)
{
	str = ft_strjoin(line, "\n");
	if (str == NULL)
		ft_error_message(pars, info);
	return (str);
}

static int	hd_loop(t_pars *pars, t_info *info, int i, int fd)
{
	char	*line;
	char	*str;
	char	*input;

	ft_check_newline(pars, pars->args[i + 1], i);
	while (!info->stop_hd)
	{
		write(1, "> ", 2);
		input = get_next_line(0);
		if (info->stop_hd)
		{
			if (input)
				free(input);
			break ;
		}
		if (input == NULL)
		{
			write(1, "\n", 1);
			ft_putstr_fd("minishell: warning: here-documentdelimited by end-of-file (wanted `", 2);
			ft_putstr_fd(pars->args[i + 1], 2);
			ft_putstr_fd("')\n\n", 2);
			break ;
		}
		line = ft_strtrim(input, "\n");
		free(input);
		if (line == NULL)
			ft_error_message(pars, info);
		if ((ft_strncmp_12hd(line, pars->args[i + 1],
					ft_strlen(pars->args[i + 1])) == 0))
		{
			free(line);
			break ;
		}
		str = ft_str_123(pars, info, str, line);
		if (info->hd_quote == 0)
			str = replace_dollar_hedoc(str, info);
		write(fd, str, ft_strlen(str));
		free_hd(line, str);
	}
	info->in_hd = 0;
	if (info->stop_hd || !line)
	{
		info->stop_hd = 0;
		return (1);
	}
	return (0);
}

int	ft_redir_heredoc(t_pars *pars, t_info *info, int i, int count)
{
	int		fd;

	fd = open("/tmp/temp8726343", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	pars->heredoc = pars->args[i + 1];
	info->in_hd = 1;
	if (ft_check_qoutes(pars->args[i + 1]) == 1)
		info->hd_quote = 1;
	else
		info->hd_quote = 0;
	pars->heredoc = ft_strdup(pars->args[i + 1]);
	pars->args[i + 1] = remove_quotes(pars->args[i + 1]);
	if (hd_loop(pars, info, i, fd) == 1)
		return (1);
	if (i == count)
	{
		pars->fd_in = open("/tmp/temp8726343", O_RDONLY);
		pars->in_file = ft_strdup("/tmp/temp8726343");
		if (pars->in_file == NULL)
			ft_error_message(pars, info);
		close (fd);
	}
	else
		close (fd);
	return (0);
}
