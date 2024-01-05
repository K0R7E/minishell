/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:35:32 by fstark            #+#    #+#             */
/*   Updated: 2024/01/05 12:39:09 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	update_pwd(t_info *info, char *path)
{
	free(info->old_pwd);
	info->old_pwd = ft_strdup(info->pwd);
	if (info->old_pwd == NULL)
		ft_error_message(*info->pars_ptr, info);
	free(info->pwd);
	info->pwd = ft_strdup(path);
	if (info->pwd == NULL)
		ft_error_message(*info->pars_ptr, info);
}
