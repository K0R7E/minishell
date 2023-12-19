/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:52:19 by fstark            #+#    #+#             */
/*   Updated: 2023/12/19 12:14:23 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_strchr2(char *s, int c)
{
	int i;

	i = 0;
	while (s[i] != '\0')
	{
		if (s[i] == c)
			return (1);
		else
			i++;
	}
	return (0);
}


void	ft_new_prompt(t_info *info, t_lexer_pos *pos, int start, int type, t_pars *pars)
{
	t_lexer *new;
	t_lexer *tmp;

	//tmp = malloc(sizeof(t_lexer));
	new = malloc(sizeof(t_lexer));
	if (new == NULL)
	{
		free(pos);
		ft_error_message(pars, info);
	}
	new->command = pos->command_number;
	new->type = type;
	new->token = ft_strldup(info->input + start, pos->i - start);
	if (new->token == NULL)
	{
		free(pos);
		free(new);
		ft_error_message(pars, info);
	}
	if (pos->hedoc == 1)
	{
		pos->hedoc = 0;
		if (ft_strchr2(new->token, '\'') || ft_strchr2(new->token, '\"'))
			new->hd_quote = 1;
		else
			new->hd_quote = 0;
	}
	else
		new->hd_quote = 0;
	new->next = NULL;
	if (info->lexer.command == 0)
	{
		info->lexer = *new;
	}
	else
	{
		tmp = &info->lexer;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_redirect(t_info *info, t_lexer_pos *pos, t_pars *pars)
{
	pos->i++;
	if (info->input[pos->i -1] == '>')
	{
		if (info->input[pos->i] == '>')
		{
			pos->i++;
			ft_new_prompt(info, pos, pos->i -2, 4, pars);
		}
		else
			ft_new_prompt(info, pos, pos->i -1, 2, pars);
	}
	else if (info->input[pos->i -1] == '<')
	{
		if (info->input[pos->i] == '<')
		{
			pos->i++;
			ft_new_prompt(info, pos, pos->i -2, 5, pars);
			pos->hedoc = 1;
		}
		else
			ft_new_prompt(info, pos, pos->i -1, 3, pars);
	}
	else if (info->input[pos->i -1] == '|')
	{
		pos->command_number++;
		ft_new_prompt(info, pos, pos->i -1, 6, pars);
	}
}

void	handle_prompt(t_info *info, t_lexer_pos *pos, t_pars *pars)
{
	int start;

	int stateDouble = 0;
	int stateSingle = 0;
	start = pos->i;
	//while ((!ft_strchr2(" \t<>|", info->input[pos->i]) && state == 0) || info->input[pos->i] != '\n')
	while (info->input[pos->i] != '\0')
	{
		if (info->input[pos->i] == '\'' &&  stateDouble == 0)
		{
			if (stateSingle == 0)
				stateSingle = 1;
			else if (stateSingle == 1)
				stateSingle = 0;
		}
		if (info->input[pos->i] == '\"' &&  stateSingle == 0)
		{
			if (stateDouble == 0)
				stateDouble = 1;
			else if (stateDouble == 1)
				stateDouble = 0;
		}
		pos->i++;
		if (stateSingle == 0 && stateDouble == 0 && ft_strchr2(" \t<>|", info->input[pos->i]))
			break ;
	}
	ft_new_prompt(info, pos, start, 1, pars);
}

/*
void	copy_lexer_list(t_info *info)
{
	t_lexer *new;
	t_lexer *tmp;
	t_lexer tmp2;
	
	new = malloc(sizeof(t_lexer));
	new->command = info->lexer.command;
	new->type = info->lexer.type;
	new->token = ft_strdup(info->lexer.token);
	new->hd_quote = info->lexer.hd_quote;
	new->next = NULL;
	info->lexer_save = *new;
	tmp = &info->lexer_save;
	tmp2 = info->lexer;
	while (tmp2.next != NULL)
	{
		tmp2 = *tmp2.next;
		new = malloc(sizeof(t_lexer));
		new->type = tmp2.type;
		new->token = ft_strdup(tmp2.token);
		new->next = NULL;
		tmp->next = new;
		tmp = tmp->next;
	}
	//print list
	t_lexer tmp3 = info->lexer_save;
	printf("\n");
	while (tmp3.next != NULL)
	{
		printf("type: %d\n", tmp3.type);
		printf("token: %s\n\n", tmp3.token);
		tmp3 = *tmp3.next;
	}
	printf("type: %d\n", tmp3.type);
	printf("token: %s\n", tmp3.token);
}*/

void	ft_lexer(t_info *info, t_pars *pars) //input str; env var
{
	t_lexer_pos *pos;
	
	pos = malloc(sizeof(t_lexer_pos));
	if (pos == NULL)
		ft_error_message(pars, info);
	info->lexer.command = 0;
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
		if (ft_strchr2("><|", info->input[pos->i]))
			handle_redirect(info, pos, pars);
		else
			handle_prompt(info, pos, pars);
	}
	free(pos);
	//print lexer list
	/*
	t_lexer tmp = list->lexer;
	printf("\n");
	while (tmp.next != NULL)
	{
		printf("hd_quote %d\n", tmp.hd_quote);
		printf("command: %d\n", tmp.command);
		printf("type: %d\n", tmp.type);
		printf("token: %s\n\n", tmp.token);
		tmp = *tmp.next;
	}
	printf("hd_quote %d\n", tmp.hd_quote);
	printf("command: %d\n", tmp.command);
	printf("type: %d\n", tmp.type);
	printf("token: %s\n", tmp.token);
	*/
}