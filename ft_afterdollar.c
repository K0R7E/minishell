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
		if (str[i] == c)
			j++;
		str[i] = str[j];
		i++;
		j++;
	}
	i = 0;
	j = 0;
	if (k)
	{
		while (str[i])
		{
			if (str[i] == k)
				j++;
			str[i] = str[j];
			i++;
			j++;
		}
	}
	str[i] = '\0';
	return (str);
}

char *after_dollar(char *str, t_info *info)
{
	int i;
	int j;

	(void)info;
	i = 0;
	j = 1;
	if (str[i] == '$')
	{
		i++;
		if ((str[i] == '\'' && str[ft_strlen(str) - 1] == '\'') || (str[i] == '\"' && str[ft_strlen(str) - 1] == '\"'))
			return (str);
		
		else if(str[i] == '/' || str[i] == '.' || str[i] == '=' || str[i] == '%' || str[i] == ',')
			return (str);
		else if (str[i] == ':')
		{
			//$: >> In Bash, the dollar sign ($) followed by a colon (:) has a specific meaning when used in parameter expansion. It is used for providing default values for variables that may not be set.
		}
		else if (str[i] == '+')
		{
			//used in parameter expansion to check if a variable is set (has a value) and, if so, return an empty string. It's often used in conditional statements to check for the existence of a variable.
		}
		else if (str[i] == '_')
		{
			//represents the last argument of the last command that was executed.
		}
		else if (str[i] == '\\')
		{
			//It looks like there's a misunderstanding in your question. In Bash, the special variable $$ (double dollar sign)
			//represents the process ID (PID) of the current shell. It is used to obtain a unique identifier for the shell process.
			//On the other hand, the character \ (backslash) is an escape character in Bash. It is used to escape special characters, 
			//preventing them from being interpreted in their usual way.
			str = ft_replace(str, '\\', 0);
			return (str);
		}
		else if (str[i] == ';')
		{
			//
			str = ft_strcpy(str, "$");
		}
		else if (str[i] == '@')
		{
			//represents all the positional parameters (arguments) passed to a script or function.
			str = ft_replace(str, '@', '$');
			return (str);
		}
		else if (str[i] == '#')
		{
			//this giv back the number of arguments
		}
		else if (str[i] == '0')
		{
			// represents the name of the script or shell itself. When used in a script, it provides the name of the script being executed.
			str = ft_replace(str, '0', '$');
			str = ft_strjoin("/bin/bash", str);
			return (str);
		}
		else if (ft_isdigit(str[i]))
		{
			//represent command-line arguments passed to a script or a function. first argument is represented by $1, second argument is represented by $2 and so on.
			while ((j != str[i] - '0') && j < 10)
				j++;
		}
		else if (str[i] == '-')
		{
			//represents the current options (flags) that are set for the shell. 
			str = ft_replace(str, '-', '$');
			str = ft_strjoin("himBH", str);
			return (str);
		}
		else if (str[i] == '!')
		{
			//represents the process ID (PID) of the last background command that was executed.
		}
		else if (str[i] == '$')
		{
			//represents the process ID (PID) of the current shell
		}
		else if (str[i] == '?')
		{
			//represents the exit status of the last executed command.
		}
		else if (str[i] == '*')
		{
			//represents all the positional parameters (arguments) passed to a script or function as a single string.
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