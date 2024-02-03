/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   change_env_var_utils3.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/03 15:51:50 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/03 16:04:20 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	slash(char *str, t_info *info)
{
	int	i;

	i = 1;
	if (info->i >= 2 && str[info->i] == '$')
	{
		if (str[info->i - 1] == '\\')
		{
			while (str[info->i - i] == '\\')
				i++;
			if ((i % 2) == 0)
				return (0);
			else
				return (1);
		}
	}
	return (1);
}

char	*slash_rem(char *in, t_info *info, char *res)
{
	int		i;
	char	*str2;

	i = -1;
	if (res == NULL)
		str2 = ft_strdup("\0");
	else
		str2 = ft_strdup(res);
	free(res);
	if (str2 == NULL)
		ft_error_message(*info->pars_ptr, info);
	while (in[info->i] == '\\')
	{
		info->i++;
		i++;
	}
	while (i > 0)
	{
		str2 = add_char_to_str(str2, '\\');
		if (str2 == NULL)
			ft_error_message(*info->pars_ptr, info);
		i -= 2;
	}
	return (str2);
}
