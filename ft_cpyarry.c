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


char **ft_arrycpy(char **envp)
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
			return (tmp);
		}
		i++;
	}
	return (tmp);
}