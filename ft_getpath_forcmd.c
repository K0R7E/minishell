#include "minishell.h"

char	*get_path_new(t_pars *pars, char *token, t_info *info)
{
	int		i;
	char	*exec;
	char	**allpath;
	char	*path_part;
	char	**s_cmd;

	i = -1;
	allpath = ft_split(info->path, ':');
	if (allpath == NULL)
	{
		ft_free_node(pars);
		ft_putstr_fd("minishell: malloc error\n", 2);
		ft_free_all(pars, info, 2);
		exit(1);
	}
	s_cmd = ft_split(token, ' ');
	if (s_cmd == NULL)
	{
		ft_free_node(pars);
		ft_putstr_fd("minishell: malloc error\n", 2);
		ft_free_array(allpath);
		ft_free_array(s_cmd);
		ft_free_all(pars, info, 2);
		exit(1);
	}
    while (allpath[++i])
    {
        path_part = ft_strjoin(allpath[i], "/");
		if (path_part == NULL)
		{
			ft_free_node(pars);
			free(path_part);
			ft_putstr_fd("minishell: malloc error\n", 2);
			ft_free_1(allpath);
			ft_free_1(s_cmd);
			ft_free_all(pars, info, 2);
			exit(1);
		}
        exec = ft_strjoin(path_part, s_cmd[0]);
		if (path_part == NULL)
		{
			ft_free_node(pars);
			free(path_part);
			free(exec);
			ft_putstr_fd("minishell: malloc error\n", 2);
			ft_free_1(allpath);
			ft_free_1(s_cmd);
			ft_free_all(pars, info, 2);
			exit(1);
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
}