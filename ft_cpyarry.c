/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyarry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:43:10 by fstark            #+#    #+#             */
/*   Updated: 2024/01/05 15:56:26 by fstark           ###   ########.fr       */
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

char	**ft_arrycpy(char **envp)
{
	char	**tmp;
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	tmp = ft_calloc(sizeof(char *), i + 1);
	if (!tmp)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		tmp[i] = ft_strdup(envp[i]);
		if (tmp[i] == NULL)
		{
			ft_free(tmp);
			return (NULL);
		}
		i++;
	}
	return (tmp);
}
