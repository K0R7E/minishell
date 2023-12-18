/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/09/05 12:15:15 by akortvel          #+#    #+#             */
/*   Updated: 2023/12/18 13:50:24 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft.h"

char	*ft_strdup(const char *s)
{
	int		i;
	char	*dups;

	i = 0;
	dups = (char *)malloc((ft_strlen(s) +1) * sizeof(*s));
	if (dups == 0)
		return (0);
	if (s == 0)
		return (0);
	while (s[i] != '\0')
	{
		dups[i] = s[i];
		i++;
	}
	dups[i] = '\0';
	return (dups);
}
