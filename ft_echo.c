/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_echo.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/07 15:50:26 by fstark            #+#    #+#             */
/*   Updated: 2023/12/07 16:19:58 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_echo(int mode, char **input)
{
	int i;

	i = 1;
	if (mode == 1)
	{
		while (input[i])
		{
			printf("%s", input[i]);
			if (input[i + 1])
				printf(" ");
			i++;
		}
		printf("\n");
	}
	else
	{
		while (input[i])
		{
			printf("%s", input[i]);
			if (input[i + 1])
				printf(" ");
			i++;
			printf("\n");
		}
	}
}