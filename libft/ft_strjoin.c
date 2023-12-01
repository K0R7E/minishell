/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strjoin.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/07 13:45:14 by akortvel          #+#    #+#             */
/*   Updated: 2023/10/30 13:36:17 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strjoin(char const *s1, char const *s2)
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
	return (join);
}
/*
int main()
{
	char *s1 = "Hello ";
	char *s2 = "World";
	printf("%s", ft_strjoin(s1, s2));
	printf("\n");
	return(0);
}
*/
