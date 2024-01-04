/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_pwd.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/11 15:59:47 by fstark            #+#    #+#             */
/*   Updated: 2023/12/12 12:57:07 by fstark           ###   ########.fr       */
/*                                                    	                      */
/* ************************************************************************** */

#include "minishell.h"

int	ft_pwd(t_info *info)
{
	printf("%s\n", info->pwd);
	return (0);
}
