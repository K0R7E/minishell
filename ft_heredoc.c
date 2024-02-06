/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:10:56 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/06 09:19:53 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_delimiter(char *delim, char *line)
{
	if ((ft_strncmp_12hd(line, delim,
				ft_strlen(delim)) == 0))
	{
		free(line);
		return (1);
	}
	return (0);
}

char	*add_line(char *input)
{
	input = readline("> ");
	return (input);
}

char	*remove_newline(char *line, char *input)
{
	line = ft_strtrim(input, "\n");
	free(input);
	return (line);
}

int	hd_loop(t_pars *pars, t_info *info, int i, int fd)
{
	char	*line;
	char	*str;
	char	*input;

	line = NULL;
	ft_check_newline(pars, pars->args[i + 1], i);
	while (!info->stop_hd || g_info == 0)
	{
		input = add_line(input);
		if (ft_check_hd(info, input) == 1)
			break ;
		if (ft_check_empty_line(pars->args[i + 1], input) == 1)
			break ;
		line = remove_newline(line, input);
		if (line == NULL)
			ft_error_message(pars, info);
		if (ft_delimiter(pars->args[i + 1], line) == 1)
			break ;
		str = ft_hd_str_01(pars, info, str, line);
		write(fd, str, ft_strlen(str));
		free_hd(line, str);
	}
	if (ft_check_stop_hd(info, line, fd) == 1)
		return (1);
	return (0);
}

int	ft_redir_heredoc(t_pars *pars, t_info *info, int i, int count)
{
	int		fd;

	info->hd_quote = 0;
	fd = open("/tmp/temp8726343", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (hd_err_ex(fd) == 1)
		return (1);
	pars->heredoc = pars->args[i + 1];
	if (ft_check_qoutes(pars->args[i + 1]) == 1)
		info->hd_quote = 1;
	pars->heredoc = ft_strdup(pars->args[i + 1]);
	pars->args[i + 1] = remove_quotes(pars->args[i + 1]);
	info->in_hd = 1;
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
