/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:25:08 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/02 15:44:37 by fstark           ###   ########.fr       */
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

int	ft_check_qoutes(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\'')
			return (1);
		else if (str[i] == '\"')
			return (1);
		i++;
	}
	return (0);
}

static int	hd_loop(t_pars *pars, t_info *info, int i, int fd)
{
	char	*line;
	char	*str;
	char	*input;

	while (!info->stop_hd)
	{
		write(1, "> ", 2);
		input = get_next_line(0);
		if (input == NULL)
			continue ;
		line = ft_strtrim(input, "\n");
		free(input);
		if (line == NULL)
			ft_error_message(pars, info);
		//line = readline("> ");
		if (info->stop_hd)
		{
			free(line);
			break ;
		}
		if (ft_strncmp_12hd(line, pars->args[i + 1],
				ft_strlen(pars->args[i + 1])) == 0)
			break ;
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
/* 	if (fd == -1)
	{
		printf("minishell: %s: No such file or directory\n", ".tmp");
		info->exit_status = 1;
		return (1);
	} */
	pars->heredoc = pars->args[i + 1];
	info->in_hd = 1;
	if (ft_check_qoutes(pars->args[i + 1]) == 1)
		info->hd_quote = 1;
	else
		info->hd_quote = 0;
	pars->args[i + 1] = remove_quotes(pars->args[i + 1]);
	hd_loop(pars, info, i, fd);
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
