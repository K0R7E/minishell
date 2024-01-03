/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/04 11:41:27 by fstark            #+#    #+#             */
/*   Updated: 2024/01/03 12:41:41 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ft_strldup(char *s, size_t len)
{
	char	*sub_str;
	size_t	i;

	i = 0;
	if (!s)
		return (NULL);
	if (len > ft_strlen(s))
		len = ft_strlen(s);
	sub_str = (char *)malloc(len + 1);
	if (sub_str == NULL)
		return (NULL);
	while (i < len && s[i])
	{
		sub_str[i] = s[i];
		i++;
	}
	sub_str[i] = '\0';
	return (sub_str);
}

int	ft_strchr_lexer(char *s, int c)
{
	int	i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}
