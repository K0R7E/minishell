/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fstark <fstark@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/28 18:52:19 by fstark            #+#    #+#             */
/*   Updated: 2023/12/14 19:14:32 by fstark           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

//#include "libft/libft.h"
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


void	ft_new_prompt(t_parsing *list, t_info *info, t_lexer_pos *pos, int start, int type)
{
	t_lexer *new;
	t_lexer *tmp;

	//tmp = malloc(sizeof(t_lexer));
	new = malloc(sizeof(t_lexer));
	new->command = pos->command_number;
	new->type = type;
	new->token = ft_strldup(info->input + start, pos->i - start);
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
	if (list->lexer.command == 0)
	{
		list->lexer = *new;
	}
	else
	{
		tmp = &list->lexer;
		while (tmp->next != NULL)
			tmp = tmp->next;
		tmp->next = new;
	}
}

void	handle_redirect(t_info *info, t_parsing *list, t_lexer_pos *pos)
{
	pos->i++;
	if (info->input[pos->i -1] == '>')
	{
		if (info->input[pos->i] == '>')
		{
			pos->i++;
			ft_new_prompt(list, info, pos, pos->i -2, 4);
		}
		else
			ft_new_prompt(list, info, pos, pos->i -1, 2);
	}
	else if (info->input[pos->i -1] == '<')
	{
		if (info->input[pos->i] == '<')
		{
			pos->i++;
			ft_new_prompt(list, info, pos, pos->i -2, 5);
			pos->hedoc = 1;
		}
		else
			ft_new_prompt(list, info, pos, pos->i -1, 3);
	}
	else if (info->input[pos->i -1] == '|')
	{
		pos->command_number++;
		ft_new_prompt(list, info, pos, pos->i -1, 6);
	}
}

void	handle_prompt(t_info *info, t_parsing *list, t_lexer_pos *pos)
{
	int state;
	int start;

	state = 0;
	start = pos->i;
	//while ((!ft_strchr2(" \t<>|", info->input[pos->i]) && state == 0) || info->input[pos->i] != '\n')
	while (info->input[pos->i] != '\0')
	{
		if (info->input[pos->i] == '\'' || info->input[pos->i] == '\"')
		{
			if (state == 0)
				state = 1;
			else if (state == 1)
				state = 0;
		}
		pos->i++;
		if (state == 0 && ft_strchr2(" \t<>|", info->input[pos->i]))
			break ;
	}
	ft_new_prompt(list, info, pos, start, 1);
}

void	copy_lexer_list(t_parsing *list, t_info *info)
{
	t_lexer *new;
	t_lexer *tmp;
	t_lexer tmp2;
	
	new = malloc(sizeof(t_lexer));
	new->command = list->lexer.command;
	new->type = list->lexer.type;
	new->token = ft_strdup(list->lexer.token);
	new->hd_quote = list->lexer.hd_quote;
	new->next = NULL;
	info->lexer_save = *new;
	tmp = &info->lexer_save;
	tmp2 = list->lexer;
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
	/*
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
	*/
}

void	ft_lexer(t_info *info, t_parsing *list) //input str; env var
{
	t_lexer_pos *pos = malloc(sizeof(t_lexer_pos));
	
	list->lexer.command = 0;
	pos->i = 0;
	pos->command_number = 1;
	pos->hedoc = 0;
	info->input = replace_dollar(info->input, info);
	printf("input: %s\n", info->input);
	while (info->input[pos->i] != '\0')
	{
		if (info->input[pos->i] == ' ' || info->input[pos->i] == '\t')
		{
			pos->i++;
			continue ;
		}
		if (ft_strchr2("><|", info->input[pos->i]))
			handle_redirect(info ,list, pos);
		else
			handle_prompt(info ,list, pos);
	}
	copy_lexer_list(list, info);
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
	printf("token: %s\n", tmp.token);*/
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