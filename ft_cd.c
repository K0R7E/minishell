#include "libft/libft.h"
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

int	chdir_input(char *path)
{
	if (chdir(path) == -1)
	{
		printf("bash: cd: %s: No such file or directory\n", path);
		return (-1);
	}
	return (0);
}

void	update_pwd(t_info *info, char *path)
{
	//char *tmp;

	//tmp = info->old_pwd;
	free(info->old_pwd);
	info->old_pwd = ft_strdup(info->pwd);
	free(info->pwd);
	info->pwd = ft_strdup(path);
}

char	*convert_path(t_info *info, char *arg)
{
	char *path;

	if (arg[0] == '/')
	{
		path = ft_strjoin(info->pwd, arg);
		return (path);
	}
	else if (arg[0] == '.' && arg[1] == '/')
	{
		path = ft_strjoin(info->pwd, "/");
		path = ft_strjoin3(path, arg + 2);
		return (path);
	}
	else if (arg[0] == '.' && arg[1] == '.' && arg[2] == '/')
	{
		path = ft_strjoin(info->pwd, "/");
		path = ft_strjoin3(path, arg + 3);
		return (path);
	}
	else
	{
		path = ft_strjoin(info->pwd, "/");
		path = ft_strjoin3(path, arg);
		return (path);
	}
}

/*
void	update_info(t_info *info)
{
	t_env *tmp;
	char *unset;
	
	free(info->home);
	free(info->pwd);
	free(info->old_pwd);
	tmp = info->env_list;
	unset = strdup("000");
	while (tmp)
	{
		if (ft_strncmp(tmp->var, "HOME", 4) == 0)
		{
			unset[0] = '1';
			info->home = ft_strdup(tmp->value);
		}
		if (ft_strncmp(tmp->var, "OLDPWD", 6) == 0)
		{
			unset[1] = '1';
			info->old_pwd = ft_strdup(tmp->value);
		}
		if (ft_strncmp(tmp->var, "PWD", 3) == 0)
		{
			unset[2] = '1';
			info->pwd = ft_strdup(tmp->value);
		}
		tmp = tmp->next;
	}
	if (unset[0] == '0')
		info->home = ft_strdup("");
	if (unset[1] == '0')
		info->old_pwd = ft_strdup("");
	if (unset[2] == '0')
		info->pwd = ft_strdup("");
}*/

void	ft_cd(t_info *info, char **args)
{
	char *tmp;
	//int i;
	update_info(info);
	//print args 
/* 	int i = 0; */
	if(args[1] == NULL || ft_strncmp(args[1], "~", 1) == 0)
	{
		if (chdir(info->home) == 0)
		{
			update_pwd(info, info->home);
		}
		else 
			printf("bash: cd: %s: No such file or directory\n", info->home);//error message, shouldn't be redirected
	}
	else if (args[2] != NULL)
	{
		printf("bash: cd: too many arguments\n");//error message, shouldn't be redirected
		return ;
	}
	else
	{
		if (strncmp(args[1], "-", 1) == 0 || strncmp(args[1], "..", 2) == 0)
		{
			if (chdir(info->old_pwd) == 0)
			{
				tmp = ft_strdup(info->old_pwd);
				update_pwd(info, ft_strdup(tmp));
				free(tmp);
			}
		}
		else
		{
			tmp = convert_path(info, args[1]);
			if (chdir_input(tmp) == 0)
				update_pwd(info, tmp);
			free (tmp);
		}
	}
	/*
	i = 1;
	while (args[i] != NULL)
	{
		free(args[i]);
		i++;
	}
	free(args);*/
	//printf ("old_pwd:%s\n", info->old_pwd);
	//printf ("pwd:%s\n", info->pwd);
}
