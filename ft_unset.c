#include "minishell.h"

int strlcmp_unset(char *str1, char *str2, int n)
{
	int i;

	i = 0;
	while (str1[i] && str2[i] && i < n)
	{
		if (str1[i] > str2[i])
			return (1);
		if (str1[i] < str2[i])
			return (-1);
		i++;
	}
	if (str2[i] == '\0' && str1[i] == '\0')
		return (0);
	return (1);
}

void remove_element(t_info *info, char *arg)
{
	t_env	*tmp;
	t_env	*tmp2;
	int i;
	int j;

	i = 0;
	j = 0;
	tmp = info->env_list;
	tmp2 = info->env_list;
	while (arg[i] != '=' && arg[i] != '\0')
		i++;
	if (arg[i] != '\0')
		return ;
	while (strlcmp_unset(arg, tmp->var, i) != 0 && tmp->next != NULL)
	{
		tmp = tmp->next;
		j++;
	}	
	//printf("compare: %s with %s for the first %d digits \n output: %d\n",arg, tmp->var, i -1, strlcmp_unset(arg, tmp->var, i));
	if (strlcmp_unset(arg, tmp->var, i) != 0)
	{
		return ;
	}
	else
	{
		
		while (j > 1)
		{
			tmp2 = tmp2->next;
			j--;
		}
		//remove linked lisT node at pos tmp
		tmp2->next = tmp->next;
		free(tmp->var);
		free(tmp->value);
	}
}


void	ft_unset(t_info *info, char **args)
{
	int i;
	
	i = 1;
	if (args[1] == NULL)
		return ;
	else
	{
		while (args[i] != NULL)
			remove_element(info, args[i++]);
	}
	while (args[i])
	{
		free(args[i]);
		i++;
	}
	free(args);
}