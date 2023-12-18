/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:16:30 by fstark            #+#    #+#             */
/*   Updated: 2023/12/18 18:53:22 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "libft/libft.h"
#include "minishell.h"

/*
void handle_input(t_info *info)
{
	char *line;
	
	line = readline(">");
	printf ("line: %s\n", line);
	info->input = ft_strjoin2(info->input, line);
}

int	ft_check_input_pipes_redirects(t_info *info)
{
	int i;

	i = 0;
	while (info->input[i] != '\0')
	{
		if (ft_strchr2("><", info->input[i]))
		{
			if (info->input[i] == '>' && info->input[i + 1] == '>')
				i++;
			else if (info->input[i] == '<' && info->input[i + 1] == '<')
				i++;
			i++;
			while (info->input[i] != '\0')
			{
				if (info->input[i] == ' ' || info->input[i] == '\t')
					i++;
				else
					break;
			}
			if (info->input[i] == '\0')
			{
				perror("syntax error near unexpected token `newline'\n");
				free (info->input);
				return (1);
			}
		}
		else if (info->input[i] == '|')
		{
			i++;
			while (info->input[i] != '\0')
			{
				if (info->input[i] == ' ' || info->input[i] == '\t')
					i++;
				else
					break;
			}
			if (info->input[i] == '\0')
			{
				perror("syntax error near unexpected token `newline'\n");
				free (info->input);
				return (1);
			}
		}
		i++;
	}
	return (0);
}*/

int	ft_check_input_quotes(t_info *info)
{
	int i;
	int stateSingle;
	int stateDouble;

	stateSingle = 0;
	stateDouble = 0;
	i = 0;
	while (info->input[i] != '\0')
	{
		if (info->input[i] == '\'' &&  stateDouble == 0)
		{
			if (stateSingle == 0)
				stateSingle = 1;
			else if (stateSingle == 1)
				stateSingle = 0;
		}
		if (info->input[i] == '\"' &&  stateSingle == 0)
		{
			if (stateDouble == 0)
				stateDouble = 1;
			else if (stateDouble == 1)
				stateDouble = 0;
		}
		i++;
	}
	if (stateSingle == 1 || stateDouble == 1)
	{
		//decide if we fail or give prompt to add
		printf("syntax error near unexpected token `newline'\n");
		free (info->input);
		return (1);
	}
	return (0);
}

int	ft_find_last_redirect(t_info *info, int i)
{
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
}

int check_if_allowed(int new, int last, t_info *info, int i) 
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
}

int handle_prompt_syntax(t_info *info, int i)
{
	int stateSingle;
	int stateDouble;

	stateSingle = 0;
	stateDouble = 0;
	while (info->input[i] != '\0')
	{
		if ((info->input[i] == ' ' || info->input[i] == '\t' || info->input[i] == '>' 
			|| info->input[i] == '<' || info->input[i] == '|') && stateDouble == 0 && stateSingle == 0)
			break ;
		if (info->input[i] == '\'' &&  stateDouble == 0)
		{
			if (stateSingle == 0)
				stateSingle = 1;
			else if (stateSingle == 1)
				stateSingle = 0;
		}
		if (info->input[i] == '\"' &&  stateSingle == 0)
		{
			if (stateDouble == 0)
				stateDouble = 1;
			else if (stateDouble == 1)
				stateDouble = 0;
		}
		i++;
	}
	return (i);
}

int	ft_check_input_syntax(t_info *info)
{
	int i;
	int stateSingle;
	int stateDouble;
	int type_last;

	stateSingle = 0;
	stateDouble = 0;
	i = 0;
	type_last = 3;
	while (info->input[i] != '\0')
	{
		if (info->input[i] == ' ' || info->input[i] == '\t')
		{
			i++;
			continue ;
		}
		else if (ft_strchr2("><|", info->input[i]) && stateSingle == 0 && stateDouble == 0)

		{
			if (info->input[i] == '>' && info->input[i + 1] == '>')
				i++;
			else if (info->input[i] == '<' && info->input[i + 1] == '<')
				i++;
			if (info->input[i] == '|')
			{
				if (check_if_allowed(3, type_last, info, i) == 1)
					return (1);
				type_last = 3;
			}
			else
			{
				if (check_if_allowed(2, type_last, info, i) == 1)
					return (1);
				type_last = 2;
			}
			if (info->input[i + 1] == '\0')
			{
				ft_putstr_fd ("syntax error near unexpected token `newline'\n", 2);
				return (1);
			}
			i++;
		}
		else
		{
			i = handle_prompt_syntax(info, i) - 1;
			if (check_if_allowed(1, type_last, info, i) == 1)
				return (1);
			type_last = 1;
		}
		i++;
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
	//if(ft_check_input_pipes_redirects(info) == 1)
		//return (1);
	if(ft_check_input_quotes(info) == 1)
		return (1);
	if(ft_check_input_syntax(info) == 1)
		return (1);
	return (0);
}