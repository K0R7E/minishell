#include "minishell.h"

char str[100] = "echo hello world";
char hi[100] = "\'echo hello world\'";

char *single_quotes(char *str)
{
	char *tmp;
	if (str == NULL)
		return (NULL);
	if (str[0] == '\'' && str[ft_strlen(str) - 1] == '\'')
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 2);
		free(str);
		str = tmp;
	}
	return (str);
}

char *double_quotes(char *str)
{
	char *tmp;
	if (str == NULL)
		return (NULL);
	if (str[0] == '\"' && str[ft_strlen(str) - 1] == '\"')
	{
		tmp = ft_substr(str, 1, ft_strlen(str) - 2);
		free(str);
		str = tmp;
	}
	return (str);
}

/* int main()
{
	char *tmp;
	tmp = single_quotes(str);
	printf("%s\n", tmp);
	tmp = double_quotes(hi);
	printf("%s\n", tmp);
	return (0);
} */