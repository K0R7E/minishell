/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:50:26 by fstark            #+#    #+#             */
/*   Updated: 2024/02/03 16:18:04 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strncmp3(char *s1, char *s2, int n)
{
	int	i;

	if (s1 == NULL || s2 == NULL)
		return (-1);
	i = 0;
	if (n == 0)
		return (0);
	while (s1[i] == s2[i] && s1[i] != '\0')
	{
		if (i < (n -1))
			i++;
		else
			return (0);
	}
	return ((unsigned char)(s1[i]) - (unsigned char)(s2[i]));
}

int	ft_echo(char **input)
{
	int	i;

	i = 1;
	while (ft_strncmp3(input[i], "-n", 2) == 0
		&& input[1][2] == '\0' && ((ft_strlen(input[i]) == 2)
			|| (input[i][2] == 'n')))
		i++;
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp3(input[1], "-n", 2) == 0 && input[1][2] == '\0')
		return (0);
	else
		printf("\n");
	return (0);
}
