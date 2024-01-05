/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cpyarry.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:43:10 by fstark            #+#    #+#             */
/*   Updated: 2024/01/05 12:46:44 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	*ft_free(char **res)
{
	while (res)
	{
		free (res);
		res++;
	}
	free (res);
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
