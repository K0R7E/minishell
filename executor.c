#include "minishell.h"

char *ft_getenv(t_info *info, t_parsing *pars, const char *token)
{
	int i;
	int j;
	int k;
	int len;

	i = 0;
	j = 0;
	k = 0;
	len = ft_strlen(token);
	while (info->env[i] != NULL)
	{
		if (!ft_strncmp(info->env[i], token, len))
		{
			while (info->env[i][j] != '=')
				j++;
			j++;
			while (info->env[i][j] != '\0')
			{
				pars->args[k] = ft_strdup(&info->env[i][j]);
				j++;
				k++;
			}
			return (pars->args[k]);
		}
		i++;
	}
}

void ft_handle_env(t_info *info, t_parsing *pars, const char *token, int *i)
{
	char *env;
	char *tmp;

	env = ft_getenv(info, pars, token);
	if (env == NULL)
	{
		pars->args[*i] = ft_strdup("");
		(*i)++;
		return ;
	}
	tmp = ft_strjoin(env, &token[ft_strlen(env) + 1]);
	pars->args[*i] = ft_strdup(tmp);
	free(tmp);
	(*i)++;
}

void ft_handle_path(t_parsing *pars, const char *token, int *j)
{
	int i = 0;
}

void ft_handle_argument(t_parsing *pars, const char *token, int *k)
{
	pars->args[*k] = ft_strdup(token);
	(*k)++;
}

void ft_executor(t_info *info, t_parsing *pars)
{
	int i;
	int j;
	int k;

	i = 0;
	j = 0;
	k = 0;
	while (pars->args[i] != NULL)
	{
		if (pars->args[i][0] == '$')
			ft_handle_env(info, pars, pars->args[i], &i);
		else if (pars->args[i][0] == '/')
			ft_handle_path(pars, pars->args[i], &j);
		else
			ft_handle_argument(pars, pars->args[i], &k);
		i++;
	}
	pars->args[i] = NULL;
	pars->args[j] = NULL;
	pars->args[k] = NULL;
}