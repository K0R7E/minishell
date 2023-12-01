/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 11:31:33 by akortvel          #+#    #+#             */
/*   Updated: 2023/10/30 14:08:15 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static size_t	count_words(char const *s, char c)
{
	size_t	count;

	count = 0;
	while (*s)
	{
		while (*s == c)
			s++;
		if (*s)
			count++;
		while (*s && *s != c)
			s++;
	}
	return (count);
}

static void	*ft_free(char **res, int len)
{
	int	i;

	i = 0;
	while (i < len)
	{
		free (res[i]);
		i++;
	}
	free (res);
	return (NULL);
}

struct s_data {
	size_t	i;
	size_t	j;
	size_t	start;
};

char	**ft_split(char const *s, char c)
{
	struct s_data	data;
	char			**result;

	data.i = 0;
	data.j = 0;
	result = (char **)malloc((count_words(s, c) + 1) * sizeof(char *));
	if (!s || !result)
		return (NULL);
	while (s[data.i])
	{
		while (s[data.i] == c)
			data.i++;
		if (s[data.i])
		{
			data.start = data.i;
			while (s[data.i] && s[data.i] != c)
				data.i++;
			result[data.j++] = ft_substr(s, data.start, data.i - data.start);
			if (!result[data.j - 1])
				return (ft_free(result, data.j));
		}
	}
	result[data.j] = NULL;
	return (result);
}
/*
int main()
{
	char *s = "111111\n1000P1\n101111\n1C00E1\n111111";
	char c = '\n';
	int i;

	i = 0;
	char **result = ft_split(s, c);

	//printf("Original: '%s'\n", s);
	while(result[i] != 0)
	{
    	printf("%s", result[i]);
		i++;
	}
	free(result);
	return(0);
}*/