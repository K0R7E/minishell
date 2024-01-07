/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 17:48:30 by fstark            #+#    #+#             */
/*   Updated: 2024/01/07 17:48:32 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	check_empty(t_info *info)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	while (info->input[i] != '\0')
	{
		if (info->input[i] != ' ' && info->input[i] != '\t')
			j = 0;
		i++;
	}
	return (j);
}
