/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:28:20 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/02 17:39:04 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	fill_args(t_pars *node, t_lexer *tmp1, t_info *info, t_pars *pars)
{
	int	i;

	i = 1;
	node->args[0] = ft_strdup(tmp1->token);
	if (node->args[0] == NULL)
	{
		ft_free_node(node);
		ft_error_message(pars, info);
	}
	while (tmp1->next && tmp1->next->type != TokenTypePipe)
	{
		node->args[i++] = ft_strdup(tmp1->next->token);
		if (node->args[i - 1] == NULL)
		{
			ft_free_node(node);
			ft_error_message(pars, info);
		}
		tmp1 = tmp1->next;
	}
	node->args[i] = NULL;
}

void	proc_spec(t_pars *node, t_pars *pars, t_lexer *tmp, t_info *info)
{
	while (tmp->type != TokenTypePipe)
	{
		if (tmp->next && tmp->next->next)
		{
			tmp = tmp->next;
			tmp = tmp->next;
		}
		else
		{
			node->command = NULL;
			node->cmd_path = NULL;
			break ;
		}
		if (tmp->type == TokenTypeWord)
		{
			set_c_p(node, tmp, pars, info);
			break ;
		}
		else if (tmp->next == NULL || tmp->type == TokenTypePipe)
		{
			node->command = NULL;
			node->cmd_path = NULL;
			break ;
		}
	}
}

/* void	ft_print_tmp(t_lexer *tmp)
{
	while (tmp)
	{
		printf("hd_quote %d\n", tmp->hd_quote);
		printf("command: %d\n", tmp->command);
		printf("type: %d\n", tmp->type);
		printf("token: %s\n\n", tmp->token);
		tmp = tmp->next;
	}
} */

t_pars	*node_for_word(t_pars *pars, t_lexer *tmp, t_info *info)
{
	t_pars	*node;
	t_lexer	*tmp1;

	tmp1 = tmp;
	node = allocate_node(pars, info, ft_lstsize(tmp) + 2);
	if ((tmp->type == TokenTypeHeredoc || tmp->type == TokenTypeOutputRedirect
			|| tmp->type == TokenTypeOutputAppend
			|| tmp->type == TokenTypeInputRedirect)
		&& tmp->next)
	{
		fill_args(node, tmp1, info, pars);
		proc_spec(node, pars, tmp, info);
		node->cmd_args = ft_add_cmd_args(node->args, pars, info);
	}
	else
	{
		fill_args(node, tmp, info, pars);
		node->command = ft_strdup(tmp->token);
		check_null(node, pars, info);
		node->command = remove_quotes(node->command);
		node->cmd_path = get_path_new(pars, node->command, info);
		node->cmd_args = ft_add_cmd_args(node->args, pars, info);
	}
	initialize_node_files(node);
	return (node);
}

void	add_pars_node(t_pars *pars, t_pars **head, t_lexer *tmp, t_info *info)
{
	t_pars	*new_node;
	t_pars	*last_node;

	last_node = *head;
	new_node = node_for_word(pars, tmp, info);
	new_node->next = NULL;
	if (*head == NULL)
	{
		*head = new_node;
		return ;
	}
	while (last_node->next != NULL)
		last_node = last_node->next;
	last_node->next = new_node;
}

int	ft_parsing(t_pars **pars, t_lexer *tokens, t_info *info)
{
	t_lexer	*tmp;

	info->val = 0;
	tmp = tokens;
	while (tmp)
	{
		tmp->token = convert_to_cmd(tmp->token, info);
		add_pars_node(*pars, pars, tmp, info);
		while (tmp->next && tmp->type != TokenTypePipe)
			tmp = tmp->next;
		tmp = tmp->next;
	}
	if (ft_redir(*pars, info) == 1)
		return (1);
	return (0);
}
