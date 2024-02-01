/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 09:45:08 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/01 12:48:55 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_node_files(t_pars *node)
{
	node->heredoc = NULL;
	node->in_file = NULL;
	node->out_file = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
}

void	check_null(t_pars *node, t_pars *pars, t_info *info)
{
	if (node->command == NULL)
	{
		ft_free_node(node);
		ft_error_message(pars, info);
	}
}

void	set_c_p(t_pars *node, t_lexer *tmp, t_pars *pars, t_info *info)
{
	node->command = ft_strdup(tmp->token);
	if (node->command == NULL)
	{
		ft_free_node(node);
		ft_error_message(pars, info);
		return ;
	}
	node->cmd_path = get_path_new(pars, node->command, info);
}

void	init_node(t_pars *node)
{
	node->in_file = NULL;
	node->out_file = NULL;
	node->command = NULL;
	node->args = NULL;
	node->cmd_path = NULL;
	node->cmd_args = NULL;
	node->next = NULL;
	node->fd_in = 0;
	node->fd_out = 1;
}
