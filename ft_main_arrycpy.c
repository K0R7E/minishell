/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_main_arrycpy.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:55:04 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/07 15:58:39 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_free(char **res)
{
	size_t	i;

	i = 0;
	while (res[i] != NULL)
	{
		free(res[i]);
		i++;
	}
	free(res);
	return (NULL);
}

void	ft_free_shit(t_info *info, char **tmp)
{
	ft_free(tmp);
	free(info);
	ft_putstr_fd("minishell: malloc error\n", 1);
	exit (1);
}

char	**ft_arrycpy_main(char **envp, t_info *info)
{
	char	**tmp;
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	tmp = ft_calloc(sizeof(char *), i + 1);
	if (!tmp)
	{
		free(info);
		ft_putstr_fd("minishell: malloc error\n", 1);
		exit (1);
	}
	i = 0;
	while (envp[i] != NULL)
	{
		tmp[i] = ft_strdup(envp[i]);
		if (tmp[i] == NULL)
			ft_free_shit(info, tmp);
		i++;
	}
	return (tmp);
}
