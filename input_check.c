/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   input_check.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/12/05 12:16:30 by fstark            #+#    #+#             */
/*   Updated: 2023/12/05 14:51:08 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void handle_input(t_info *info)
{
	char *line;
	
	line = readline(">");
	printf ("line: %s\n", line);
	info->input = ft_strjoin2(info->input, line);
}

int	ft_check_input(t_info *info)
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
				printf("syntax error near unexpected token `newline'\n");
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
				handle_input(info);
		}
		i++;
	}
	return (0);
}