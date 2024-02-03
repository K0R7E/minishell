/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_heredoc_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 16:13:14 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/03 16:17:55 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

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

int	ft_check_newline(t_pars *pars, char *str, int j)
{
	int		i;
	char	*str2;

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
