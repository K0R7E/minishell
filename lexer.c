/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:52:19 by fstark            #+#    #+#             */
/*   Updated: 2023/12/01 18:46:42 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* #include "lexer.h" */

/*
int	count_prompts(char *str)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\'')
		{
			i++;
			while (str[i] != '\'')
				i++;
			count++;
		}
		if (str[i] == '\"')
		{
			i++;
			while (str[i] != '\"')
				i++;
			count++;
		}
		if (str[i] == ' ' || str[i] == '\t')
			count++;
		i++;
	}
	return (count + 1);
}
*/


void	ft_new_prompt(t_parsing *list, t_info *info, t_lexer_pos *pos, int start, int type)
{
	
	
}

void	handle_redirect(t_info *info, t_parsing *list, t_lexer_pos *pos)
{
	if (info->input[pos->i] == '>')
	{
		if (info->input[pos->i + 1] == '>')
		{
			ft_new_prompt(list, info, pos, pos->i, 4);
			pos->i++;
		}
		else
			ft_new_prompt(list, info, pos, pos->i, 2);
	}
	else if (info->input[pos->i] == '<')
	{
		if (info->input[pos->i + 1] == '<')
		{
			ft_new_prompt(list, info, pos, pos->i, 5);
			pos->i++;
		}
		else
			ft_new_prompt(list, info, pos, pos->i, 3);
	}
	else if (info->input[pos->i] == '|')
		ft_new_prompt(list, info, pos, pos->i, 6);
	
	else if (info->input[pos->i] == '|')
		ft_new_prompt(list, info, pos, pos->i, 5);
}

void	handle_prompt(t_info *info, t_parsing *list, t_lexer_pos *pos)
{
	int state;
	int start;

	state = 0;
	start = pos->i;
	while (info->input[pos->i] != ' ' && state == 0 || info->input[pos->i] != '\t' && state == 0 || info->input[pos->i] != '\0')
	{
		if (info->input[pos->i])
		{
			if (state == 0)
				state = 1;
			else if (state == 1)
				state = 0;
		}
		pos->i++;
		ft_new_prompt(list, info, pos, start, 1);
	}

}

void	ft_lexer(t_info *info, t_parsing *list) //input str; env var
{
	t_lexer_pos *pos;
	
	pos->i = 0;;;
	while (info->input[pos->i] != '\0')
	{
		if (info->input[pos->i] == ' ' || info->input[pos->i] == '\t')
		{
			pos->i++;
			continue ;
		}
		else if (info->input[pos->i] == '>' || info->input[pos->i] == '<' || info->input[pos->i] == '|')
			handle_redirect(info ,list, pos); //if | change pos->command_number
		else
			handle_prompt(info ,list, pos);
	}
}
	
	

	//info->args = (char **)malloc(((count_prompts(info->input)) + 1) * sizeof(char *));
	//printf("prompts: %d\n", (count_prompts(input->input_str)));
	/*
	if (!input->input_str)
		return ;
	while (input->input_str[i] != '\0')
	{
		if (input->input_str[i] == ' ' || input->input_str[i] == '\t')
		{
			i++;
			continue ;
		}
		if (input->input_str[i] == '\'')
		{
			length = i;
			i++;
			while (input->input_str[i] != '\'')
			{
				i++;
				if(input->input_str[i] == '\0')
				{
					printf("Error: unclosed quote\n");
					break ;
				}
			}
			while (input->input_str[i] != ' ' || input->input_str[i] != '\0' || input->input_str[i] != '\t')
				i++;
			i++;
			info->args[++pos] = ft_strldup(input->input_str + length, i - length); //change to linked list
		}
		else if (input->input_str[i] == '\"')
		{
			length = i;
			i++;
			while (input->input_str[i] != '\"')
			{
				i++;
				if(input->input_str[i] == '\0')
				{
					printf("Error: unclosed quote\n");
					break ;
				}	
			}
			i++;
			info->args[++pos] = ft_strldup(input->input_str + length, i - length); //change to linked list
		}
		else 
		{
			length = i;
			i++;
			while (input->input_str[i] != '\0')
			{
				if (input->input_str[i] == ' ' || input->input_str[i] == '\t')
					break ;
				if (input->input_str[i] == '\'' || input->input_str[i] == '\"')
					break ;
				i++;
			}
			info->args[++pos] = ft_strldup(input->input_str + length, i - length); //change to linked list
			//info->args[pos++] = ft_strldup(input->input_str + i, j + 1); write own
			//info->args[j++][i - length] = '\0';
		}
		
	}
	info->args[++pos]= NULL;
	*/


/*
void	parser(char* input_str, t_info *info)
{
	t_input *input = malloc(sizeof(t_info));
	
	input->input_str = replace_dollar(input_str, info);//convert variables from env list
	ft_lexer(input, info);
	int i = -1;
	while (input->args[++i] != 0)
	{
		printf("str at pos %d: %s\n", i, input->args[i]);
	}
}
*/