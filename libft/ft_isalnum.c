/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_isalnum.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:14:46 by akortvel          #+#    #+#             */
/*   Updated: 2023/09/14 17:07:35 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

int	ft_isalnum(int c)
{
	if ((c >= 65 && c <= 90) || (c >= 97 && c <= 122) || (c >= '0' && c <= '9'))
		return (1);
	return (0);
}
/*
int main()
{
    char c;

    c = '5';
    if (ft_isalnum(c) == 1)
        printf("%s", "ok");
    else
        printf("%s", "nem");

    return(0);
}
*/
