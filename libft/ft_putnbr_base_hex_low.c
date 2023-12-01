/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putnbr_base_hex_low.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/19 08:10:53 by akortvel          #+#    #+#             */
/*   Updated: 2023/10/26 20:55:49 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static	int	ft_strlen_base_hex_low(unsigned int nbr)
{
	int	i;

	i = 0;
	if (nbr == 0)
		return (1);
	while (nbr != 0)
	{
		i++;
		nbr /= 16;
	}
	return (i);
}

static void	ft_putnbr_base_hex_low_rec(unsigned int nbr, const char type)
{
	if (nbr >= 16)
	{
		ft_putnbr_base_hex_low(nbr / 16, type);
		ft_putnbr_base_hex_low(nbr % 16, type);
	}
	else
	{
		if (nbr <= 9)
			ft_putchar_fd((nbr + '0'), 1);
		else
			ft_putchar_fd((nbr - 10 + 'a'), 1);
	}
}

int	ft_putnbr_base_hex_low(unsigned int nbr, const char type)
{
	if (nbr == 0)
		ft_putchar ('0');
	else
		ft_putnbr_base_hex_low_rec(nbr, type);
	return (ft_strlen_base_hex_low(nbr));
}
