/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putptr.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/18 08:02:41 by akortvel          #+#    #+#             */
/*   Updated: 2023/10/27 15:45:22 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	ft_strlen_hex_ptr(uintptr_t nbr)
{
	int	i;

	i = 0;
	while (nbr != 0)
	{
		i++;
		nbr /= 16;
	}
	return (i);
}

static void	ft_make(uintptr_t nbr)
{
	if (nbr >= 16)
	{
		ft_make(nbr / 16);
		ft_make(nbr % 16);
	}
	else
	{
		if (nbr <= 9)
			ft_putchar(nbr + '0');
		else
			ft_putchar((nbr - 10) + 'a');
	}
}

int	ft_putptr(unsigned long long ptr)
{
	int	len;

	len = 0;
	if (ptr == 0)
		len += ft_putstr(PTRNULL);
	else
	{
		len += write (1, "0x", 2);
		ft_make(ptr);
		len += ft_strlen_hex_ptr(ptr);
	}
	return (len);
}
