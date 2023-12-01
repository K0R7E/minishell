/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/17 13:53:43 by akortvel          #+#    #+#             */
/*   Updated: 2023/10/27 15:56:58 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_putchar(int c)
{
	write(1, &c, 1);
	return (1);
}

int	ft_putstr(char *str)
{
	int	i;

	i = 0;
	if (str == NULL)
	{
		write (1, "(null)", 6);
		return (6);
	}
	while (str[i] != '\0')
	{
		write(1, &str[i], 1);
		i++;
	}
	return (i);
}

int	ft_which(va_list ap, const char type)
{
	int	len;

	len = 0;
	if (type == 'c')
		len += ft_putchar(va_arg(ap, int));
	else if (type == 's')
		len += ft_putstr(va_arg(ap, char *));
	else if (type == 'p')
		len += ft_putptr(va_arg(ap, unsigned long long));
	else if (type == 'd')
		len += ft_putnbr_dec(va_arg(ap, int));
	else if (type == 'i')
		len += ft_putnbr_int(va_arg(ap, int));
	else if (type == 'u')
		len += ft_putunsigned(va_arg(ap, unsigned int));
	else if (type == 'x')
		len += ft_putnbr_base_hex_low(va_arg(ap, unsigned int), type);
	else if (type == 'X')
		len += ft_putnbr_base_hex_up(va_arg(ap, unsigned int), type);
	else if (type == '%')
		len += ft_putpercent();
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	ap;
	int		i;
	int		len;

	if (!str)
		return (-1);
	i = 0;
	len = 0;
	va_start (ap, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			len += ft_which(ap, str[i + 1]);
			i++;
		}
		else
			len += ft_putchar(str[i]);
		i++;
	}
	va_end (ap);
	return (len);
}
