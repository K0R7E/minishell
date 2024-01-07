/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_3.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 09:47:14 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/07 10:47:03 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

t_pars	*allocate_node(t_pars *pars, t_info *info, int arg_size)
{
	t_pars	*node;

	node = malloc(sizeof(t_pars));
	if (!node)
	{
		ft_free_node(node);
		ft_putstr_fd("minishell: malloc error\n", 2);
		ft_free_all(pars, info, 2);
		exit(1);
	}
	init_node(node);
	node->args = malloc(sizeof(char *) * arg_size);
	if (!node->args)
	{
		ft_free_node (node);
		ft_putstr_fd("minishell: malloc error\n", 2);
		ft_free_all(pars, info, 2);
		exit(1);
	}
	return (node);
}

void	hand_all_fail(char **tmp, char **args, t_pars *pars, t_info *info)
{
	ft_free_array(tmp);
	ft_free_array(args);
	ft_free_node(pars);
	ft_error_message(pars, info);
}

char	**ft_add_cmd_args(char **args, t_pars *pars, t_info *info)
{
	int		i;
	int		j;
	char	**tmp;

	i = 0;
	j = 0;
	tmp = calloc_cmd(args, pars, info);
	while (args[i])
	{
		if (args[i] == NULL)
			break ;
		if (should_skip_arg(args[i]))
			i += 2;
		else
		{
			tmp[j] = ft_strdup(args[i]);
			if (tmp[j] == NULL)
				hand_all_fail(tmp, args, pars, info);
			i++;
			j++;
		}
	}
	tmp[j] = NULL;
	return (tmp);
}
