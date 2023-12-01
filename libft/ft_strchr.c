/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strchr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:15:21 by akortvel          #+#    #+#             */
/*   Updated: 2023/09/14 17:08:03 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strchr(const char *s, int c)
{
	unsigned char	tar;

	tar = (unsigned char)c;
	while (*s)
	{
		if (tar == (unsigned char)(*s))
			return ((char *)s);
		s++;
	}
	if ((unsigned char)(*s) == tar)
		return ((char *)s);
	return (NULL);
}
