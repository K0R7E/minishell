/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_free_all.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:40:03 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/01 18:53:27 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	free_pars_list(t_pars *head)
{
	t_pars	*current;
	t_pars	*next;

	current = head;
	while (current != NULL)
	{
		next = current->next;
		free(current->cmd_path);
		free(current->command);
		ft_free_array(current->cmd_args);
		ft_free_array(current->args);
		free(current->heredoc);
		free(current->in_file);
		free(current->out_file);
		free(current);
		current = next;
	}
}

void	free_lexer_list(t_info *info)
{
	t_lexer	*current;
	t_lexer	*next;

	current = info->lexer;
	while (current != NULL)
	{
		next = current->next;
		free(current->token);
		free(current);
		current = next;
	}
}

void	ft_free_env(t_env *env)
{
	t_env	*current;
	t_env	*next;

	current = env;
	while (current != NULL)
	{
		next = current->next;
		free(current->var);
		free(current->value);
		free(current);
		current = next;
	}
}

void	free_input(t_info *info)
{
	ft_free_env(info->env_list);
	ft_free_array(info->env);
	if (info->old_pwd)
		free(info->old_pwd);
	if (info->pwd)
		free(info->pwd);
	if (info->path)
		free(info->path);
	if (info->home)
		free(info->home);
	if (info->input)
		free(info->input);
	free(info);
}

void	ft_free_all(t_pars *pars, t_info *info, int flag)
{
	if (info->lexer != NULL)
		free_lexer_list(info);
	if (pars != NULL)
		free_pars_list(pars);
	if (info && flag == 2)
		free_input(info);
}
