/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 09:45:08 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/07 12:31:42 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	initialize_node_files(t_pars *node)
{
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

/* int	iterate_lexer_tokens(t_lexer *tmp, t_pars *node)
{
	int	j;

	j = 0;
	if (tmp->next && tmp->next->next)
	{
		tmp = tmp->next;
		tmp = tmp->next;
		j = 1;
	}
	else
	{
		node->command = NULL;
		node->cmd_path = NULL;
		j = 0;
	}
	return (j);
} */

void	set_c_p(t_pars *node, t_lexer *tmp, t_pars *pars, t_info *info)
{
	node->command = ft_strdup(tmp->token);
	if (node->command == NULL)
	{
		ft_free_node(node);
		ft_error_message(pars, info);
		return ;
	}
	//node->command = remove_quotes(node->command);
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
