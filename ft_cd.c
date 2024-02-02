/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_cd.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:13:04 by fstark            #+#    #+#             */
/*   Updated: 2024/02/02 14:33:01 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strjoin3(char const *s1, char const *s2)
{
	char	*join;
	size_t	len;
	size_t	i;
	size_t	n;

	i = 0;
	n = 0;
	len = ft_strlen(s1) + ft_strlen(s2);
	join = (char *)malloc(len + 1);
	if (join == 0)
		return (0);
	while (s1[i] != '\0')
	{
		join[i] = s1[i];
		i++;
	}
	while (s2[n] != '\0')
	{
		join[i] = s2[n];
		i++;
		n++;
	}
	join[i] = '\0';
	free ((char *)s1);
	return (join);
}

/*
int	chdir_input(char *path)
{
	if (chdir(path) == -1)
	{
		ft_putstr_fd("minishell: cd: ", 2);
		ft_putstr_fd(path, 2);
		ft_putstr_fd(": No such file or directory\n", 2);
		return (-1);
	}
	return (0);
}*/

/*
void	update_pwd(t_info *info, char *path)
{
	free(info->old_pwd);
	info->old_pwd = ft_strdup(info->pwd);
	free(info->pwd);
	info->pwd = ft_strdup(path);
}*/

char	*convert_path(t_info *info, char *arg)
{
	char	*path;

	if (arg[0] == '/')
	{
		path = ft_strdup(arg);
		if (path == NULL)
			ft_error_message(*info->pars_ptr, info);
	}
	else
	{
		path = ft_strjoin(info->pwd, "/");
		if (path == NULL)
			ft_error_message(*info->pars_ptr, info);
		path = ft_strjoin3(path, arg);
		if (path == NULL)
			ft_error_message(*info->pars_ptr, info);
	}
	if (path[ft_strlen(path) - 1] == '/')
		path[ft_strlen(path) - 1] = '\0';
	return (path);
}

char	*convert_path_back(char *arg, t_info *info)
{
	char	*path;
	int		i;

	i = ft_strlen(arg);
	while (arg[i] != '/')
		i--;
	path = ft_strldup(arg, i);
	if (path == NULL)
		ft_error_message(*info->pars_ptr, info);
	return (path);
}

int	ft_cd_arg(t_info *info, char **args)
{
	char	*tmp;
	int		ret;

	ret = 0;
	if (ft_strncmp(args[1], "..", 3) == 0)
	{
		tmp = convert_path_back(info->pwd, info);
		if (chdir(tmp) == 0)
			update_pwd(info, tmp);
		free(tmp);
	}
	else
	{
		tmp = convert_path(info, args[1]);
		if (chdir(tmp) == 0)
			update_pwd(info, tmp);
		else
		{
			ft_3("minishell: cd: ", tmp,
				": No such file or directory\n");
			ret = 1;
		}
		free (tmp);
	}
	return (ret);
}

int	ft_cd(t_info *info, char **args)
{
	int	ret;

	ret = 0;
	if (args[1] == NULL)
	{
		if (chdir(info->home) == 0)
			update_pwd(info, info->home);
		else
		{
			if (info->home == NULL)
				ft_putstr_fd("minishell: cd: HOME not set\n", 2);
			else
				ft_3("minishell: cd: ", info->home,
					": No such file or directory\n");
			return (1);
		}
	}
	else if (args[2] != NULL)
	{
		ft_putstr_fd("minishell: cd: too many arguments\n", 2);
		return (1);
	}
	else
		ret = ft_cd_arg(info, args);
	return (ret);
}
