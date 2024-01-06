/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing_right_way.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/06 17:28:20 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/06 18:53:46 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_argsnode(t_pars *node)
{
	int	i;

	i = 0;
	if (node->args != NULL)
	{
		while (node->args[i])
		{
			free(node->args[i]);
			i++;
		}
	}
}

void	free_cmdnode(t_pars *node)
{
	int	i;

	i = 0;
	if (node->cmd_args != NULL)
	{
		i = 0;
		while (node->cmd_args[i])
		{
			free(node->cmd_args[i]);
			i++;
		}
	}
}

void	ft_free_node(t_pars *node)
{
	if (!node)
		return ;
	free_argsnode(node);
	free_cmdnode(node);
	if (node->args != NULL)
		free(node->args);
	if (node->cmd_args != NULL)
		free(node->cmd_args);
	if (node->command != NULL)
		free(node->command);
	if (node->cmd_path != NULL)
		free(node->cmd_path);
	if (node->in_file != NULL)
		free(node->in_file);
	if (node->out_file != NULL)
		free(node->out_file);
	free(node);
}

char	**calloc_cmd(char **args, t_pars *pars, t_info *info)
{
	int		i;
	char	**tmp;

	i = 0;
	while (args[i])
		i++;
	tmp = malloc(sizeof(char *) * (i + 1));
	if (tmp == NULL)
	{
		ft_free_node(pars);
		ft_free_1(args);
		ft_putstr_fd("minishell: malloc error\n", 2);
		ft_free_all(pars, info, 2);
		exit(1);
	}
	return (tmp);
}

int	should_skip_arg(char *arg)
{
	return (arg && (ft_strncmp(arg, ">>", 2) == 0
			|| ft_strncmp(arg, "<<", 2) == 0
			|| ft_strncmp(arg, ">", 1) == 0
			|| ft_strncmp(arg, "<", 1) == 0));
}

void	hand_all_fail(char **tmp, char **args, t_pars *pars, t_info *info)
{
	ft_free_1(tmp);
	ft_free_1(args);
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
	while (is_next_args(tmp1) == 1)
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

void	set_c_p(t_pars *node, t_lexer *tmp, t_pars *pars, t_info *info)
{
	node->command = ft_strdup(tmp->token);
	if (node->command == NULL)
	{
		ft_free_node(node);
		ft_error_message(pars, info);
		return ;
	}
	node->command = remove_quotes(node->command);
	node->cmd_path = get_path_new(pars, node->command, info);
}

void	iterate_lexer_tokens(t_lexer **tmp)
{
	if ((*tmp)->next && (*tmp)->next->next)
	{
		*tmp = (*tmp)->next;
		*tmp = (*tmp)->next;
	}
}

void	proc_spec(t_pars *node, t_pars *pars, t_lexer *tmp, t_info *info)
{
	while (tmp->type != TokenTypePipe)
	{
		iterate_lexer_tokens(&tmp);
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

void	initialize_node_files(t_pars *node)
{
	node->in_file = NULL;
	node->out_file = NULL;
	node->append = -1;
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
