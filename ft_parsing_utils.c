/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 09:50:02 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/03 15:56:09 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	ft_check_word_type(t_pars *pars, t_lexer *tokens, t_info *info)
{
	(void)info;
	(void)pars;
	if (ft_strcmp_123(tokens->token, "pwd") == 0
		|| ft_strcmp_123(tokens->token, "echo") == 0
		|| ft_strcmp_123(tokens->token, "cd") == 0
		|| ft_strcmp_123(tokens->token, "env") == 0
		|| ft_strcmp_123(tokens->token, "export") == 0
		|| ft_strcmp_123(tokens->token, "unset") == 0
		|| ft_strcmp_123(tokens->token, "exit") == 0)
		return (1);
	return (0);
}

int	is_next_args(t_lexer *tokens)
{
	if (tokens->next != NULL && tokens->next->type != TokenTypePipe)
		return (1);
	return (0);
}

int	ft_lstsize(t_lexer *tokens)
{
	int	count;

	count = 0;
	while ((tokens->next != NULL) && (tokens != NULL
			|| tokens->type != TokenTypePipe))
	{
		count++;
		tokens = tokens->next;
	}
	return (count);
}

char	*convert_to_cmd(char *str, t_info *info)
{
	char	*tmp;

	if (ft_strncmp(str, "/usr/bin/", 9) == 0)
	{
		tmp = ft_substr(str, 9, ft_strlen(str) - 9);
		if (tmp == NULL)
			ft_error_message(*info->pars_ptr, info);
		free(str);
		return (tmp);
	}
	else if (ft_strncmp(str, "/bin/", 5) == 0)
	{
		tmp = ft_substr(str, 5, ft_strlen(str) - 5);
		if (tmp == NULL)
			ft_error_message(*info->pars_ptr, info);
		free(str);
		return (tmp);
	}
	else
		return (str);
}

/* void	ft_print_pars(t_pars *pars)
{
	int i = 0;
	int j = 0;
	int k = 0;

	while (pars != NULL)
	{
		printf("Node: %d\n", i);
		printf("----------------------\n");
		printf("Fd_in: %d\n", pars->fd_in);
		printf("Fd_out: %d\n", pars->fd_out);
		printf("In_file: %s\n", pars->in_file);
		printf("Out_file: %s\n", pars->out_file);
		printf("Cmd_path: %s\n", pars->cmd_path);
		printf("Command: %s\n", pars->command);
		printf("heredoc: %s\n", pars->heredoc);
		printf("cmd_args: ");
		if (pars->cmd_args != NULL)
		{
			k = 0;
			while (pars->cmd_args[k])
			{
				printf("%s ", pars->cmd_args[k]);
				k++;
			}
		}
		printf("\n");
		printf("Args: ");
		if (pars->args != NULL)
		{
			j = 0;
			while (pars->args[j])
			{
				printf("%s ", pars->args[j]);
				j++;
			}
		}
		printf("\n");
		printf("----------------------\n");
		pars = pars->next;
		i++;
	}
} */