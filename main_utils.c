/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 15:58:45 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/04 14:43:41 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ft_1(t_info *info, t_pars *pars)
{
	int	fd_in;
	int	fd_out;

	fd_in = 0;
	fd_out = 1;
	remove_quotes_from_parsing_list(pars, info);
	info->command_count = ft_listsize(pars);
	update_info(info);
	ft_executor(pars, info, fd_in, fd_out);
	signal(SIGQUIT, SIG_IGN);
	free(info->input);
	info->input = NULL;
	ft_free_all(pars, info, 1);
}

void	ft_args(char **argv, int argc)
{
	if (argc != 1 || argv[1])
	{
		printf("Please do not add parameters\n");
		exit (1);
	}
}

void	init_loop(t_pars *pars, t_info *info)
{
	(void)pars;
	info->lexer = NULL;
	info->command_count = 1;
	info->builtin_command_count = 0;
	info->input = NULL;
}
