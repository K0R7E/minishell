/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putunsigned.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 10:24:28 by akortvel          #+#    #+#             */
/*   Updated: 2023/10/26 20:55:32 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_nbr(unsigned int nbr)
{
	int	i;

	i = 0;
	while (nbr != 0)
	{
		i++;
		nbr /= 10;
	}
	return (i);
}

int	ft_putunsigned(unsigned int nbr)
{
	int		len;
	int		i;
	char	*number;

	len = 0;
	if (nbr == 0)
		len += ft_putchar('0');
	else
	{
		i = ft_strlen_nbr(nbr);
		number = (char *)malloc(sizeof(char) * (i + 1));
		if (!nbr)
			return (0);
		number[i] = '\0';
		while (nbr != 0)
		{
			number[i - 1] = nbr % 10 + 48;
			nbr /= 10;
			i--;
		}
		len += ft_putstr(number);
		free (number);
	}
	return (len);
}
