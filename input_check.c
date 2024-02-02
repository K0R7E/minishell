/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:16:30 by fstark            #+#    #+#             */
/*   Updated: 2024/02/02 14:26:35 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_input_quotes(t_info *info)
{
	int				i;
	t_quote_state	qs;

	qs.state_d = 0;
	qs.state_s = 0;
	i = 0;
	while (info->input[i] != '\0')
	{
		if (info->input[i] == '\'' && qs.state_d == 0)
			qs.state_s = update_quote_state(qs.state_s);
		if (info->input[i] == '\"' && qs.state_s == 0)
			qs.state_d = update_quote_state(qs.state_d);
		i++;
	}
	if (qs.state_d == 1 || qs.state_s == 1)
	{
		printf("syntax error near unexpected token `newline'\n");
		return (1);
	}
	return (0);
}

/*
int	ft_find_last_redirect(t_info *info, int i)
{
	i--;
	if (info->input[i +1] == '>' && info->input[i] == '>')
		i--;
	else if (info->input[i +1] == '<' && info->input[i] == '<')
		i--;
	while (i >= 0)
	{
		if (info->input[i] == '>' && info->input[i - 1] == '>')
			return (4);
		else if (info->input[i] == '<' && info->input[i - 1] == '<')
			return (3);
		else if (info->input[i] == '>')
			return (2);
		else if (info->input[i] == '<')
			return (1);
		i--;
	}
	return (0);
}*/

/*
int	check_if_allowed(int new, int last, t_info *info, int i)
{
	if (last == 3)
	{
		if (new != 1 && new != 2)
		{
			ft_putstr_fd("syntax error near unexpected token `|'\n", 2);
			return (1);
		}
	}
	if (last == 2)
	{
		if (new != 1)
		{
			ft_putstr_fd("syntax error near unexpected token `", 2);
			if (ft_find_last_redirect(info, i) == 1)
				ft_putstr_fd("<", 2);
			if (ft_find_last_redirect(info, i) == 2)
				ft_putstr_fd(">", 2);
			if (ft_find_last_redirect(info, i) == 3)
				ft_putstr_fd("<<", 2);
			if (ft_find_last_redirect(info, i) == 4)
				ft_putstr_fd(">>", 2);
			ft_putstr_fd("'\n", 2);
			return (1);
		}
	}
	return (0);
}*/

int	handle_prompt_syntax(t_info *info, int i)
{
	t_quote_state	qs;

	qs.state_d = 0;
	qs.state_s = 0;
	while (info->input[i] != '\0')
	{
		if ((info->input[i] == ' ' || info->input[i] == '\t'
				|| info->input[i] == '>' || info->input[i] == '<'
				|| info->input[i] == '|') && qs.state_d == 0 && qs.state_s == 0)
			break ;
		if (info->input[i] == '\'' && qs.state_d == 0)
		{
			qs.state_s = update_quote_state(qs.state_s);
		}
		if (info->input[i] == '\"' && qs.state_s == 0)
		{
			qs.state_d = update_quote_state(qs.state_d);
		}
		i++;
	}
	return (i);
}

int	ft_handle_redirect_syntax(int i, t_info *info, int type_last)
{
	if (info->input[i] == '>' && info->input[i + 1] == '>')
		i++;
	else if (info->input[i] == '<' && info->input[i + 1] == '<')
		i++;
	if (info->input[i] == '|')
	{
		if (check_if_allowed(3, type_last, info, i) == 1)
			return (-1);
		type_last = 3;
	}
	else
	{
		if (check_if_allowed(2, type_last, info, i) == 1)
			return (-1);
		type_last = 2;
	}
	if (info->input[i + 1] == '\0')
	{
		ft_putstr_fd ("syntax error near unexpected token `newline'\n", 2);
		return (-1);
	}
	i++;
	return (type_last);
}

/*
int	ft_handle_redirect_length(t_info *info, int i)
{
	if (info->input[i] == '>' && info->input[i + 1] == '>')
		i++;
	else if (info->input[i] == '<' && info->input[i + 1] == '<')
		i++;
	i++;
	return (i);
}*/

int	ft_check_input_syntax(t_info *info, int type_last, int i)
{
	while (info->input[++i] != '\0')
	{
		if (info->input[i] == ' ' || info->input[i] == '\t')
			continue ;
		else if (ft_strchr_lexer("><|", info->input[i]))
		{
			type_last = ft_handle_redirect_syntax(i, info, type_last);
			if (type_last == -1)
				return (1);
			i = ft_handle_redirect_length(info, i);
		}
		else
		{
			i = handle_prompt_syntax(info, i) - 1;
			if (check_if_allowed(1, type_last, info, i) == 1)
				return (1);
			type_last = 1;
		}
	}
	if (type_last == 2 || type_last == 3)
	{
		ft_putstr_fd ("syntax error near unexpected token `newline'\n", 2);
		return (1);
	}
	return (0);
}

int	ft_check_input(t_info *info)
{
	int	i;
	int	type_last;

	i = -1;
	type_last = 3;
	if (check_empty(info) == 1)
	{
		free(info->input);
		return (1);
	}
	if (ft_check_input_quotes(info) == 1)
	{
		free(info->input);
		info->exit_code = 2;
		return (1);
	}
	if (ft_check_input_syntax(info, type_last, i) == 1)
	{
		free(info->input);
		info->exit_code = 2;
		return (1);
	}
	return (0);
}
