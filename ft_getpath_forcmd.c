/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_getpath_forcmd.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 11:00:02 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/06 07:55:21 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

static void	free_path(t_pars *pars, t_info *info, char **allpath)
{
	ft_free_array(allpath);
	ft_error_message(pars, info);
}

/* static char	**get_s_smd(t_pars *pars, t_info *info, 
	char *token, char **allpath)
{
	char	**s_cmd;

	s_cmd = ft_split(token, ' ');
	if (s_cmd == NULL)
	{
		ft_free_array(allpath);
		ft_error_message(pars, info);
	}
	return (s_cmd);
} */

char	*get_path2(t_info *info)
{
	t_env	*tmp;
	char	*path;

	tmp = info->env_list;
	while (tmp)
	{
		if (ft_strncmp2(tmp->var, "PATH", 4) == 0 && ft_strlen(tmp->var) == 4)
		{
			path = ft_strdup(tmp->value);
			if (path == NULL)
				ft_error_message(*info->pars_ptr, info);
			return (path);
		}
		tmp = tmp->next;
	}
	return (NULL);
}

char	**prepare_paths(t_pars *pars, t_info *info)
{
	char	**allpath;
	char	*path;

	path = get_path2(info);
	if (path != NULL)
	{
		allpath = ft_split(path, ':');
		free(path);
		if (allpath == NULL)
			ft_error_message(pars, info);
	}
	else
		return (NULL);
	return (allpath);
}

char	*exec_path(t_pars *pars, t_info *info, char **allpath, char *s_cmd)
{
	int		i;
	char	*path_part;
	char	*exec;

	i = -1;
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		if (path_part == NULL)
			free_path(pars, info, allpath);
		exec = ft_strjoin(path_part, s_cmd);
		free(path_part);
		if (exec == NULL)
		{
			ft_free_array(allpath);
			free(s_cmd);
			ft_error_message(pars, info);
		}
		if (access(exec, F_OK | X_OK) == 0)
			return (exec);
		free(exec);
	}
	return (NULL);
}

char	*get_path_new(t_pars *pars, char *token, t_info *info)
{
	char	**allpath;
	char	*s_cmd;
	char	*exec;

	allpath = prepare_paths(pars, info);
	if (allpath == NULL)
		return (NULL);
	s_cmd = ft_strdup(token);
	if (s_cmd == NULL)
		free_path(pars, info, allpath);
	exec = exec_path(pars, info, allpath, s_cmd);
	ft_free_array(allpath);
	free(s_cmd);
	if (exec)
		return (exec);
	exec = ft_strdup(token);
	if (exec == NULL)
		ft_error_message(pars, info);
	return (exec);
}

/* char	*get_path_new(t_pars *pars, char *token, t_info *info)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(info->path, ':');
	if (allpath == NULL)
		ft_error_message(pars, info);
	s_cmd = get_s_smd(info, token, allpath, s_cmd);
	while (allpath[++i])
	{
		path_part = ft_strjoin(allpath[i], "/");
		if (path_part == NULL)
			free_path(pars, info, allpath, s_cmd);
		exec = ft_strjoin(path_part, s_cmd[0]);
		if (exec == NULL)
		{
			free(path_part);
			ft_free_array(allpath);
			ft_free_array(s_cmd);
			ft_error_message(pars, info);
		}
		free(path_part);
		if (access(exec, F_OK | X_OK) == 0)
		{
			ft_free_array(allpath);
			ft_free_array(s_cmd);
			return (exec);
		}
		free(exec);
	}
	ft_free_array(allpath);
	ft_free_array(s_cmd);
	return (strdup(token));
} */
