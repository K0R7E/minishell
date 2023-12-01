/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strlcat.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:15:53 by akortvel          #+#    #+#             */
/*   Updated: 2023/11/29 13:07:52 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

size_t	ft_strlcat(char *dst, const char *src, size_t size)
{
	size_t	size_dst;
	size_t	i;
	size_t	len_dst;
	size_t	len_src;

	len_dst = ft_strlen(dst);
	len_src = ft_strlen(src);
	size_dst = ft_strlen(dst);
	i = 0;
	if (size <= len_dst)
		return (size + len_src);
	while (src[i] != '\0' && (size_dst + 1) < size)
	{
		dst[size_dst] = src[i];
		size_dst++;
		i++;
	}
	dst[size_dst] = '\0';
	return (len_dst + len_src);
}

/* int main()
{
	char *dst = "Hello World";
	const char *src = "Hello";
	size_t size = 4;

	printf("\n%ld", ft_strlcat(dst, src, size));
	return(0);
	
} */
