/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_exit.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: akortvel <akortvel@student.42vienna.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/07 10:39:06 by akortvel          #+#    #+#             */
/*   Updated: 2024/02/06 11:34:19 by akortvel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	get_value_exit(long long int n)
{
	long long int	i;

	i = 0;
	if (n < 0)
	{
		i = (n * -1) / 256;
		n = n + (256 * (i + 1));
	}
	if (n > 255)
	{
		i = n / 256;
		n = n - (256 * i);
	}
	return (n);
}

int	compare_max_long(char *nptr, int i, int minus, long long int result)
{
	if ((result > 922337203685477580 && nptr[i] != '\0')
		|| (result >= 922337203685477580 && ((nptr[i] > '7' && minus == 1)
				|| (nptr[i] > '8' && minus == -1)))
		|| (result > 1000000000000000000 && nptr[i] != '\0'))
		return (1);
	return (0);
}

int	ft_atoi_exit(char *nptr)
{
	int				i;
	int				minus;
	long long int	result;

	i = 0;
	minus = 1;
	result = 0;
	if (nptr[i] == '-' || nptr[i] == '+')
	{
		if (nptr[i] == '-')
			minus = minus * -1;
		i++;
	}
	if (nptr[i] == '\0')
		return (256);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if (compare_max_long(nptr, i, minus, result) == 1)
			return (256);
		result = result * 10 + (nptr[i++] - '0');
	}
	if (nptr[i] != '\0')
		return (256);
	return ((get_value_exit((long long int)result * minus)));
}

int	ft_exit2(char **input, int exit_value, t_info *info)
{
	(void)info;
	if (exit_value != 256)
	{
		if (input[2] != NULL)
		{
			ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			return (1);
		}
		else
		{
			ft_free_all(*info->pars_ptr, info, 2);
			exit(exit_value);
		}
	}
	else
	{
		ft_putstr_fd("minishell: exit: ", 2);
		ft_putstr_fd(input[1], 2);
		ft_putstr_fd(": numeric argument required\n", 2);
		ft_free_all(*info->pars_ptr, info, 2);
		exit(2);
	}
}

int	ft_exit(t_info *info, char **input)
{
	int	exit_value;

	if (info->command_count == 1)
		printf("exit\n");
	if (input[1] == NULL)
	{
		exit_value = info->exit_code;
		ft_free_all(*info->pars_ptr, info, 2);
		exit(exit_value);
	}
	else
	{
		exit_value = ft_atoi_exit(input[1]);
		return (ft_exit2(input, exit_value, info));
	}
}

/*
int ft_exit(t_info *info, char **input)
{
	int exit_value;

	if (info->command_count == 1)
		printf("exit\n");
	if (input[1] == NULL)
	{
		//ft_free_all(*info->pars_ptr, info, 1);
		exit(info->exit_code);
	}
	else
	{
		exit_value = ft_atoi_exit(input[1]);
		if (exit_value != 256)
		{
			if (input[2] != NULL)
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
				return (1);
			}
			else
			{
				//ft_free_all(*info->pars_ptr, info, 1);
				exit(exit_value);
			}
		}
		else
		{
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(input[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			//ft_free_all(*info->pars_ptr, info, 1);
			exit(2);
		}
	}
}*/