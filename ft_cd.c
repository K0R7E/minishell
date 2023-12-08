#include "libft/libft.h"
#include "minishell.h"

int	chdir_input(char *path)
{
	if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		free(path);
		return (-1);
	}
	return (0);
}

void	update_pwd(t_info *info, char *path)
{
	char *tmp;

	tmp = info->old_pwd;
	info->old_pwd = info->pwd;
	info->pwd = path;
}

char	*convert_path(t_info *info, char *arg)
{
	char *path;
	char *tmp;

	if (arg[0] == '/')
		return (arg);
	else if (arg[0] == '.' && arg[1] == '/')
	{
		path = ft_strjoin(info->pwd, "/");
		tmp = path;
		path = ft_strjoin(path, arg + 2);
		free(tmp);
		return (path);
	}
	else if (arg[0] == '.' && arg[1] == '.' && arg[2] == '/')
	{
		path = ft_strjoin(info->pwd, "/");
		tmp = path;
		path = ft_strjoin(path, arg + 3);
		free(tmp);
		return (path);
	}
	else
	{
		path = ft_strjoin(info->pwd, "/");
		tmp = path;
		path = ft_strjoin(path, arg);
		free(tmp);
		return (path);
	}
}

void	ft_cd(t_info *info, char **args)
{
	char *tmp;
	

	if(args[1] == NULL || ft_strncmp(args[1], "~", 1) == 0)
	{
		if (chdir(info->home) == 0)
		{
			update_pwd(info, info->home);
		}
	}
	else if (args[2] != NULL)
	{
		printf("bash: cd: too many arguments\n");//error massage, shouldn't be redirected
		return ;
	}
	else
	{
		if (strncmp(args[1], "-", 1) == 0)
		{
			if (chdir(info->old_pwd) == 0)
				update_pwd(info, info->old_pwd);
		}
		else
		{
			tmp = convert_path(info, args[1]);
			if (chdir_input(tmp) == 0)
				update_pwd(info, tmp);
			free (tmp);
		}
	}
	
}
