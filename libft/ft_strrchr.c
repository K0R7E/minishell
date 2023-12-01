/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:16:46 by akortvel          #+#    #+#             */
/*   Updated: 2023/09/14 17:08:21 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char			*res;
	unsigned char	tar;

	tar = (unsigned char)c;
	res = NULL;
	while (*s)
	{
		if ((unsigned char)(*s) == tar)
			res = ((char *)s);
		s++;
	}
	if ((unsigned char)(*s) == tar)
		return ((char *)s);
	return (res);
}
