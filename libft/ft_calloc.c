/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_calloc.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:14:25 by akortvel          #+#    #+#             */
/*   Updated: 2023/09/16 10:41:07 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

void	*ft_calloc(size_t nmemb, size_t size)
{
	size_t	total_size;
	void	*ptr;

	total_size = nmemb * size;
	if (nmemb == 0 || size == 0)
		return (malloc(0));
	if (nmemb > 65535 / size)
		return (NULL);
	ptr = malloc(total_size);
	if (ptr != NULL)
		ft_memset(ptr, 0, total_size);
	return (ptr);
}
/*
int main()
{
	size_t i;
	size_t numelem;
	size_t elemsize;

	i = 0;
	numelem = 5;
	elemsize = sizeof(int);
	int* arr = (int *)ft_calloc(numelem, elemsize);
	if(arr != 0)
	{
		while(i < numelem)
		{
			printf("%d", arr[i]);
			i++;
		}
		printf("\n");
		free(arr);
	}
	else
		printf("Fail.\n");
	return(0);
}*/
