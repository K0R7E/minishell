/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:43:45 by fstark            #+#    #+#             */
/*   Updated: 2024/01/03 18:45:12 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	get_pwd(t_info *info)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], "PWD=", 4))
			info->pwd = ft_substr(info->env[i], 4, ft_strlen(info->env[i]) - 4);
		if (!ft_strncmp(info->env[i], "OLDPWD=", 7))
			info->old_pwd = ft_substr(info->env[i], 7,
					ft_strlen(info->env[i]) - 7);
		if (!ft_strncmp(info->env[i], "HOME=", 5))
			info->home = ft_substr(info->env[i], 5,
					ft_strlen(info->env[i]) - 5);
		if (!ft_strncmp(info->env[i], "PATH=", 5))
			info->path = ft_substr(info->env[i], 5,
					ft_strlen(info->env[i]) - 5);
		i++;
	}
}
