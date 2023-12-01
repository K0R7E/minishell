/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strtrim.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 15:44:41 by akortvel          #+#    #+#             */
/*   Updated: 2023/09/14 17:08:24 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strtrim(char const *s1, char const *set)
{
	size_t	i;
	size_t	start;
	char	*result;

	start = 0;
	i = ft_strlen(s1);
	if (!s1 || !set)
		return (0);
	while (s1[start] && ft_strchr(set, s1[start]))
		start++;
	while (i > start && ft_strchr(set, s1[i - 1]))
		i--;
	result = ft_substr(s1, start, (i - start));
	return (result);
}
/*
int main() 
{
    char input[] = "   Hello, World!   "; 
    const char charSet[] = " \t\n\r";
	char *trim = ft_strtrim(input, charSet);
	printf("Original string: '%s'\n", input);
	printf("Trimmed string: '%s'\n", trim);
	free(trim);

    return 0;
}*/
