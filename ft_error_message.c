/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_error_message.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:41:35 by fstark            #+#    #+#             */
/*   Updated: 2024/01/03 18:42:24 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_error_message(t_pars *pars, t_info *info)
{
	ft_putstr_fd("minishell: malloc error\n", 1);
	ft_free_all(pars, info, 2);
	exit(1);
}
