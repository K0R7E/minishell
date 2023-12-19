#include "libft/libft.h"
#include "minishell.h"

int	get_value_exit(long long int n)
{
	long long int i;

	i = 0;
	//printf("n: %lld\n", n);
	if (n < 0)
	{
		i = (n * -1) / 256;
		//printf("i: %lld\n", i);
		n = n + (256 * (i + 1));
	}
	if (n > 255)
	{
		i = n / 256;
		//printf("i: %lld\n", i);
		n = n - (256 * i);
	}
	//printf("n: %lld\n", n);
	return (n);
}

int	ft_atoi_exit(char *nptr)
{
	int				i;
	int				minus;
	long long int	result;
	int flag;

	flag = 0;
	i = 0;
	minus = 1;
	result = 0;
	if (nptr[i] == '-')
	{
		minus = minus * -1;
		i++;
	}
	if (nptr[i] == '\0')
		return (256);
	while (nptr[i] >= '0' && nptr[i] <= '9')
	{
		if ((result > 922337203685477580 && nptr[i] != '\0') || (result >= 922337203685477580 && ((nptr[i] > '7' && minus == 1) || (nptr[i] > '8' && minus == -1))) || (result > 1000000000000000000 && nptr[i] != '\0'))
		{
			flag = 1;
			break ;
		}
		result = result * 10 + (nptr[i++] - '0');
	}
	if (nptr[i] != '\0')
		return (256);
	if (flag == 1)
		return (256);
	return ((get_value_exit((long long int)result * minus)));
}


void	ft_exit(t_info *info, char **input)
{
	int i;
	int exit_value;

	(void)info;
	i = 0;
	printf("exit\n");
	if (input[1] == NULL)
	{
		//free(input);
		exit(0);
	}

	if (input[1] != NULL)
	{
		exit_value = ft_atoi_exit(input[1]);
		if (exit_value != 256)
		{
			if (input[2] != NULL)
			{
				ft_putstr_fd("minishell: exit: too many arguments\n", 2);
			}
			else
			{
				//free(input);
				exit(exit_value);
			}
		}
		else
		{
			//printf("minishell: exit: %s: numeric argument required\n", input[1]);
			ft_putstr_fd("minishell: exit: ", 2);
			ft_putstr_fd(input[1], 2);
			ft_putstr_fd(": numeric argument required\n", 2);
			//free(input);
			exit(2);
		}
	}
	else
	{
		//free(input);
		exit(0); //value: last exit code;
	}
}