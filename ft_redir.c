/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_redir.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:06:10 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/06 18:55:00 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_redir_input(t_pars *pars, t_info *info, int i, int count)
{
	int		fd;
	char    *tmp;

    tmp = ft_strdup(pars->args[i + 1]);
    if (tmp == NULL)
        ft_error_message(pars, info);
    free(pars->args[i + 1]);
    pars->args[i + 1] = remove_quotes(tmp);
	fd = open(pars->args[i + 1], O_RDONLY);
	if (i == count)
	{
		pars->fd_in = fd;
		pars->in_file = ft_strdup(pars->args[i + 1]);
		if (pars->in_file == NULL)
			ft_error_message(pars, info);
	}
}

void	ft_redir_output(t_pars *pars, t_info *info, int i, int count)
{
	int		fd;
	char	*tmp;

    tmp = ft_strdup(pars->args[i + 1]);
    if (tmp == NULL)
        ft_error_message(pars, info);
    free(pars->args[i + 1]);
    pars->args[i + 1] = remove_quotes(tmp);
	fd = open(pars->args[i + 1], O_WRONLY | O_CREAT | O_TRUNC, 0777);
	if (i == count)
	{
		pars->fd_out = fd;
		pars->out_file = ft_strdup(pars->args[i + 1]);
		if (pars->out_file == NULL)
			ft_error_message(pars, info);
	}
}

void	ft_redir_output_app(t_pars *pars, t_info *info, int i, int count)
{
	int		fd;
	char    *tmp;

    tmp = ft_strdup(pars->args[i + 1]);
    if (tmp == NULL)
        ft_error_message(pars, info);
    free(pars->args[i + 1]);
    pars->args[i + 1] = remove_quotes(tmp);
	fd = open(pars->args[i + 1], O_WRONLY | O_CREAT | O_APPEND, 0777);
	if (i == count)
	{
		pars->fd_out = fd;
		pars->out_file = ft_strdup(pars->args[i + 1]);
		if (pars->out_file == NULL)
			ft_error_message(pars, info);
	}
}

int	ft_check_num(char **str, char *c)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i])
	{
		if (ft_strncmp(str[i], c, 1) == 0)
			count = i;
		i++;
	}
	return (count);
}

int	ft_redir(t_pars *pars, t_info *info)
{
	t_pars	*tmp;
	int		i;	

	tmp = pars;
	i = 0;
	while (tmp)
	{
		i = 0;
		while (tmp->args[i])
		{
			if (ft_strncmp(tmp->args[i], "<<", 2) == 0)
			{
				g_global.stop_hd = 0;
				info->hd_quote = 0;
				if ((ft_strncmp(tmp->args[i + 1], "\"", 1) == 0)
					|| (ft_strncmp(tmp->args[i + 1], "\'", 1) == 0))
					info->hd_quote = 1;				
				if (ft_redir_heredoc(tmp, info, i,
						ft_check_num(tmp->args, "<<")) == 1)
					return (1);
			}
			else if (ft_strncmp(tmp->args[i], ">>", 2) == 0)
				ft_redir_output_app(tmp, info, i,
					ft_check_num(tmp->args, ">>"));
			else if (ft_strncmp(tmp->args[i], "<", 1) == 0)
				ft_redir_input(tmp, info, i, ft_check_num(tmp->args, "<"));
			else if (ft_strncmp(tmp->args[i], ">", 1) == 0)
				ft_redir_output(tmp, info, i, ft_check_num(tmp->args, ">"));
			i++;
		}
		tmp = tmp->next;
	}
	return (0);
}