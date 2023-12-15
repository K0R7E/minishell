#include "libft/libft.h"
#include "minishell.h"

char *ft_strcpy(char *dest, char *src)
{
	int i;

	i = 0;
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}	
	dest[i] = '\0';
	return (dest);
}

char *ft_replace(char *str, char c, char k)
{
	int i;
	int j;

	i = 0;
	j = 0;
	while (str[i])
	{
		if ((c != 0) && (str[i] == c))
		{
			if ((k != 0) && (str[i + 1] == k))
			{

			}
			j++;
		}
		str[i] = str[j];
		i++;
	}
	return (str);
}

char *after_dollar(char *str, t_info *info)
{
	int i;
	int j;
	char *var;

	(void)info;
	i = 0;
	j = 1;
	var = malloc(sizeof(char) * 100);
	if (str[i] == '$')
	{
		i++;
		if ((str[i] == '\'' && str[ft_strlen(str) - 1] == '\'') || (str[i] == '\"' && str[ft_strlen(str) - 1] == '\"'))
			return (str);
		else if(str[i] == ':' || str[i] == '/' || str[i] == '.' || str[i] == '=' || str[i] == '+' || str[i] == '%' || str[i] == ',')
			return (str);
		else if (str[i] == '_')
		{
			free(str);
			str[0] = '\0';
		}
		else if (str[i] == '\\')
		{
			strcpy(var, "$");
    		strcat(var, str); // - $'\\'
			return (var);
		}
		else if (str[i] == ';')
		{
			str = ft_strcpy(str, "$");
		}
		else if (str[i] == '@')
		{
			
		}
		else if (str[i] == '#')
		{

		}
		else if (str[i] == '0')
		{
			
		}
		else if (ft_isdigit(str[i]))
		{
			while ((j != str[i] - '0') && j < 10)
				j++;
		}
		else if (str[i] == '-')
		{
			
		}
		else if (str[i] == '?')
		{

		}
	}
	return (str);
}

int main()
{
	char *str;

	str = readline(">");
	str = after_dollar(str, NULL);
	printf("str: %s\n", str);
	return (0);
}