/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:52:19 by fstark            #+#    #+#             */
/*   Updated: 2023/12/01 16:29:59 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"
/* #include "lexer.h" */
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



void	ft_lexer(t_input *input, t_parsing *info) //inut str; env var
{
	//(void)info;
	/*
	info->args = ft_split(input->input_str, ' ');
	return ;
	*/
	//printf("input_str: %s\n", input->input_str);
	t_lexer_pos *pos;
	
	pos->i = 0;;
	info->args = (char **)malloc(((count_prompts(input->input_str)) + 1) * sizeof(char *));
	while (input->input_str[i] != '\0')
	{
		if (input->input_str[i] == ' ' || input->input_str[i] == '\t')
		{
			i++;
			continue ;
		}
		else if (input->input_str[i] == '>' || input->input_str[i] == '<' || input->input_str[i] == '|')
			handle_redirect();
		else
			handle_prompt();
	
	
	
	
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
}


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