/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/08 12:53:03 by akortvel          #+#    #+#             */
/*   Updated: 2023/09/14 17:07:41 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

static int	count_digits(int n)
{
	int	count;

	if (n == 0)
		count = 1;
	else
		count = 0;
	while (n != 0)
	{
		n /= 10;
		count++;
	}
	return (count);
}

static int	ft_neg(int n)
{
	if (n < 0)
		return (1);
	return (0);
}

char	*ft_itoa(int n)
{
	int		len;
	char	*res;
	int		neg;

	neg = ft_neg(n);
	if (n == -2147483648)
		return (ft_strdup("-2147483648"));
	len = count_digits(n);
	if (neg)
	{
		len++;
		n = -n;
	}
	res = (char *)malloc((len + 1) * sizeof(char));
	if (!res)
		return (NULL);
	res[len] = '\0';
	while (len-- > 0)
	{
		res[len] = (n % 10) + '0';
		n /= 10;
	}
	if (neg)
		res[0] = '-';
	return (res);
}
/*
int main()
{
	int n = 12345;
	char *res = ft_itoa(n);
	printf("Szám: %d\n", n);
	printf("Szöveg: %s\n", res);
	free(res);
	
	return(0);	
}*/
