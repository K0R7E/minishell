/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_1.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 09:41:34 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/07 10:46:08 by akortvel         ###   ########.fr       */
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
		ft_free_array(args);
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
