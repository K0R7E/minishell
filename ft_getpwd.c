/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpwd.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:43:45 by fstark            #+#    #+#             */
/*   Updated: 2024/01/07 11:48:02 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	set_env_value(t_info *info, char *env_str, char *key, char **target)
{
	size_t	key_len;

	key_len = ft_strlen(key);
	if (!ft_strncmp(env_str, key, key_len))
	{
		*target = ft_substr(env_str, key_len,
				ft_strlen(env_str) - key_len);
		if (*target == NULL)
			ft_error_message(*info->pars_ptr, info);
	}
}

void	get_pwd(t_info *info)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		set_env_value(info, info->env[i], "PWD=", &info->pwd);
		set_env_value(info, info->env[i], "OLDPWD=", &info->old_pwd);
		set_env_value(info, info->env[i], "HOME=", &info->home);
		set_env_value(info, info->env[i], "PATH=", &info->path);
		i++;
	}
}

/* void	get_pwd(t_info *info)
{
	int	i;

	i = 0;
	while (info->env[i])
	{
		if (!ft_strncmp(info->env[i], "PWD=", 4))
		{
			info->pwd = ft_substr(info->env[i], 4, ft_strlen(info->env[i]) - 4);
			if (info->pwd == NULL)
				ft_error_message(*info->pars_ptr, info);
		}
		if (!ft_strncmp(info->env[i], "OLDPWD=", 7))
		{
			info->old_pwd = ft_substr(info->env[i], 7,
					ft_strlen(info->env[i]) - 7);
			if (info->old_pwd == NULL)
				ft_error_message(*info->pars_ptr, info);
		}
		if (!ft_strncmp(info->env[i], "HOME=", 5))
		{
			info->home = ft_substr(info->env[i], 5,
					ft_strlen(info->env[i]) - 5);
			if (info->home == NULL)
				ft_error_message(*info->pars_ptr, info);
		}
		if (!ft_strncmp(info->env[i], "PATH=", 5))
		{
			info->path = ft_substr(info->env[i], 5,
					ft_strlen(info->env[i]) - 5);
			if (info->path == NULL)
				ft_error_message(*info->pars_ptr, info);
		}
		i++;
	}
} */
