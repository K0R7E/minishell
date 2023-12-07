/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 17:16:44 by fstark            #+#    #+#             */
/*   Updated: 2023/12/07 14:24:30 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_env(t_info *info)
{
	int i;

	i = 0;
	while (info->env[i])
	{
		printf("%s\n", info->env[i]);
		i++;
	}
}

