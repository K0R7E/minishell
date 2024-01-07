/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   remove_quotes.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 14:20:23 by akortvel          #+#    #+#             */
/*   Updated: 2024/01/07 14:20:28 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	find_new_length(char *str)
{
	int	in_dbl;
	int	in_sgl;
	int	i;
	int	j;

	if (str == NULL)
		return (0);
	i = 0;
	j = 0;
	in_dbl = 0;
	in_sgl = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\"' && in_sgl == 0)
			in_dbl = !in_dbl;
		if (str[i] == '\'' && in_dbl == 0)
			in_dbl = !in_dbl;
		else
			j++;
		i++;
	}
	return (j);
}

char	*remove_quotes2(char *str, t_quote_state qs, int i, int j)
{
	char			*new_str;

	new_str = malloc(sizeof(char) * find_new_length(str) + 1);
	if (new_str == NULL)
		return (NULL);
	while (str && str[i] != '\0')
	{
		if (str[i] == '\"' && qs.state_s == 0)
		{
			qs.state_d = update_quote_state(qs.state_d);
			i++;
			continue ;
		}
		else if (str[i] == '\'' && qs.state_d == 0)
		{
			qs.state_s = update_quote_state(qs.state_s);
			i++;
			continue ;
		}
		else
			new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free(str);
	return (new_str);
}

char	*remove_quotes(char *str)
{
	int				i;
	int				j;
	t_quote_state	qs;
	char			*new_str;

	qs.state_d = 0;
	qs.state_s = 0;
	i = 0;
	j = 0;
	new_str = remove_quotes2(str, qs, i, j);
	return (new_str);
}

/*
void	remove_quotes_from_lexer_list(t_lexer *lexer)
{
	t_lexer *tmp;
	char *tmp_token;

	tmp = lexer;
	while (tmp != NULL)
	{
		tmp_token = remove_quotes(tmp->token);
		free(tmp->token);
		tmp->token = tmp_token;
		tmp = tmp->next;
	}
}
*/

void	remove_quotes_from_parsing_list(t_pars *pars, t_info *info)
{
	t_pars	*tmp;
	int		i;

	tmp = pars;
	while (tmp != NULL)
	{
		tmp->command = remove_quotes(tmp->command);
		if (tmp->command == NULL)
			ft_error_message(*info->pars_ptr, info);
		i = 0;
		while (tmp->cmd_args[i] != NULL)
		{
			tmp->cmd_args[i] = remove_quotes(tmp->cmd_args[i]);
			if (tmp->cmd_args[i] == NULL)
				ft_error_message(*info->pars_ptr, info);
			i++;
		}
		tmp = tmp->next;
	}
}
