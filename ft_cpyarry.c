#include "minishell.h"

static void	*ft_free(char **res)
{
	int	i;

	i = 0;
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
	char	**rtn;
	size_t	i;

	i = 0;
	while (envp[i] != NULL)
		i++;
	rtn = ft_calloc(sizeof(char *), i + 1);
	if (!rtn)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		rtn[i] = ft_strdup(envp[i]);
		if (rtn[i] == NULL)
		{
			ft_free(rtn);
			return (rtn);
		}
		i++;
	}
	return (rtn);
}