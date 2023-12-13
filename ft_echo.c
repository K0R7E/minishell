/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:50:26 by fstark            #+#    #+#             */
/*   Updated: 2023/12/11 14:26:57 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

void	ft_echo(char **input)
{
	int i;

	i = 1;
	if (ft_strncmp(input[1], "-n", 2) == 0)
		i = 2;
	while (input[i])
	{
		printf("%s", input[i]);
		if (input[i + 1])
			printf(" ");
		i++;
	}
	if (ft_strncmp(input[1], "-n", 2) != 0)
		printf("\n");
	/*
	while (input[i])
	{
		free(input[i]);
		i++;
	}
	free(input);
	*/
}