/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:50:26 by fstark            #+#    #+#             */
/*   Updated: 2024/02/06 07:58:34 by akortvel         ###   ########.fr       */
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

int	find_flag(char **input)
{
	int	i;
	int	j;
	int	flag;

	flag = 0;
	i = 1;
	while (ft_strncmp3(input[i], "-n", 2) == 0)
	{
		j = 2;
		while (input[i][j] != '\0' && input[i][j] == 'n')
			j++;
		if (input[i][j] != '\0')
			break ;
		i++;
	}
	return (i);
}

int	ft_echo(char **input)
{
	int	i;
	int	flag;

	flag = 0;
	i = find_flag(input);
	if (i > 1)
		flag = 1;
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[i + 1])
			printf(" ");
		i++;
	}
	if (flag == 1)
		return (0);
	else
		printf("\n");
	return (0);
}
