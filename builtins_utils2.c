/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils2.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/03 18:35:32 by fstark            #+#    #+#             */
/*   Updated: 2024/01/07 18:12:01 by fstark           ###   ########.fr       */
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

int	update_quote_state2(t_quote_state qs, char c)
{
	int	i;

	i = 0;
	if (c == '\'')
	{
		i = update_quote_state(qs.state_s);
	}
	else if (c == '\"')
	{
		i = update_quote_state(qs.state_d);
	}
	return (i);
}

int	change_one_zero(int i)
{
	if (i == 1)
		i = 0;
	else if (i == 0)
		i = 1;
	return (i);
}
