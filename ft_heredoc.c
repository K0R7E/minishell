/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:25:08 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/01 18:50:21 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
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

int ft_check_newline(t_pars *pars, char *str, int j)
{
	int	i;
	char *str2;

	i = 0;
	while (str[i])
	{
		if (str[i] == '\\' && str[i + 1] == 'n')
		{
			str2 = ft_substr(str, 0, i);
			free(pars->args[j + 1]); 
			pars->args[j + 1] = ft_strdup(str2);
			return (1);
		}
		i++;
	}
	return (0);
}

static int	hd_loop(t_pars *pars, t_info *info, int i, int fd)
{
	char	*line;
	char	*str;
	int		l;
	int		len;

	l = 0;
	if (ft_check_newline(pars, pars->args[i + 1], i) == 1)
		l = 1;
	len = ft_strlen(pars->heredoc) - ft_strlen(pars->args[i + 1]);
	//printf("delim: %s\n", pars->args[i + 1]);
	while (!g_global.stop_hd)
	{
		line = readline("> ");
		if (l == 1)
			rl_replace_line(ft_substr(pars->heredoc, ft_strlen(pars->args[i + 1]), len), 0);
		if (g_global.stop_hd)
		{
			free(line);
			break ;
		}
		if ((ft_strncmp_12hd(line, pars->args[i + 1],
				ft_strlen(pars->args[i + 1])) == 0))
			break ;
		str = ft_str_123(pars, info, str, line);
		if (info->hd_quote == 0)
			str = replace_dollar_hedoc(str, info);
		write(fd, str, ft_strlen(str));
		free_hd(line, str);
	}
	g_global.in_hd = 0;
	if (g_global.stop_hd || !line)
		return (1);
	return (0);
}

int	ft_redir_heredoc(t_pars *pars, t_info *info, int i, int count)
{
	int		fd;

	fd = open("/tmp/temp8726343", O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (fd == -1)		// could be deleted
	{
		printf("minishell: %s: No such file or directory\n", ".tmp");
		info->exit_status = 1;
		return (1);
	}
	g_global.in_hd = 1;
	if (ft_check_qoutes(pars->args[i + 1]) == 1)
		info->hd_quote = 1;
	else
		info->hd_quote = 0;
	pars->heredoc = ft_strdup(pars->args[i + 1]);
	pars->args[i + 1] = remove_quotes(pars->args[i + 1]);
	//pars->args[i + 1] = ft_check_newlinw(pars->args[i + 1]);
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
