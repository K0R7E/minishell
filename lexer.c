/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:49:37 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/07 15:42:31 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_new_prompt_add(t_info *info, t_lexer *new, int type, int command_num)
{
	t_lexer	*tmp;

	new->command = command_num;
	new->type = type;
	if (info->lexer == NULL)
	{
		info->lexer = new;
	}
	else
	{
		tmp = info->lexer;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	ft_new_prompt(t_info *info, t_lexer_pos *pos, int start, int type)
{
	t_lexer	*new;

	new = malloc(sizeof(t_lexer));
	if (new == NULL)
	{
		free(pos);
		ft_error_message(*info->pars_ptr, info);
	}
	new->token = ft_strldup(info->input + start, pos->i - start);
	if (new->token == NULL)
	{
		free(pos);
		free(new);
		ft_error_message(*info->pars_ptr, info);
	}
	new->hd_quote = 0;
	if (pos->hedoc == 1)
	{
		pos->hedoc = 0;
		if (ft_strchr_lexer(new->token, '\'')
			|| ft_strchr_lexer(new->token, '\"'))
			new->hd_quote = 1;
	}
	new->next = NULL;
	ft_new_prompt_add(info, new, type, pos->command_number);
}

void	handle_redirect(t_info *info, t_lexer_pos *pos)
{
	pos->i++;
	if (info->input[pos->i -1] == '>')
	{
		if (info->input[pos->i] == '>')
			ft_new_prompt(info, pos, ++pos->i -2, 4);
		else
			ft_new_prompt(info, pos, pos->i -1, 2);
	}
	else if (info->input[pos->i -1] == '<')
	{
		if (info->input[pos->i] == '<')
		{
			ft_new_prompt(info, pos, ++pos->i -2, 5);
			pos->hedoc = 1;
		}
		else
			ft_new_prompt(info, pos, pos->i -1, 3);
	}
	else if (info->input[pos->i -1] == '|')
	{
		pos->command_number++;
		ft_new_prompt(info, pos, pos->i -1, 6);
	}
}

void	handle_prompt(t_info *info, t_lexer_pos *pos)
{
	int				start;
	t_quote_state	qs;

	qs.state_d = 0;
	qs.state_s = 0;
	start = pos->i;
	while (info->input[pos->i] != '\0')
	{
		if (info->input[pos->i] == '\'' && qs.state_d == 0)
			qs.state_s = update_quote_state(qs.state_s);
		if (info->input[pos->i] == '\"' && qs.state_s == 0)
			qs.state_d = update_quote_state(qs.state_d);
		pos->i++;
		if (qs.state_s == 0 && qs.state_d == 0
			&& ft_strchr_lexer(" \t<>|", info->input[pos->i]))
			break ;
	}
	ft_new_prompt(info, pos, start, 1);
}

void	ft_lexer(t_info *info)
{
	t_lexer_pos	*pos;

	pos = malloc(sizeof(t_lexer_pos));
	if (pos == NULL)
		ft_error_message(*info->pars_ptr, info);
	pos->i = 0;
	pos->command_number = 1;
	pos->hedoc = 0;
	info->input = replace_dollar(info->input, info);
	while (info->input[pos->i] != '\0')
	{
		if (info->input[pos->i] == ' ' || info->input[pos->i] == '\t')
		{
			pos->i++;
			continue ;
		}
		if (ft_strchr_lexer("><|", info->input[pos->i]))
			handle_redirect(info, pos);
		else
			handle_prompt(info, pos);
	}
	free(pos);
}
