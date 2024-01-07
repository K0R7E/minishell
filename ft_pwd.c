/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:59:47 by fstark            #+#    #+#             */
/*   Updated: 2023/12/12 12:57:07 by fstark           ###   ########.fr       */
/*                                                    	                      */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_info *info)
{
	printf("%s\n", info->pwd);
	return (0);
}

int	ft_strcmp_123(const char *s1, const char *s2)
{
	int	i;
	int	j;

	i = 0;
	j = 0;
	while (s1[i] != '\0' && s2[j] != '\0')
	{
		if (s1[i] != s2[j])
			return (s1[i] - s2[j]);
		i++;
		j++;
	}
	if (s1[i] == '\0' && s2[j] != '\0')
		return (s2[j]);
	else if (s1[i] != '\0' && s2[j] == '\0')
		return (s1[i]);
	return (0);
}
