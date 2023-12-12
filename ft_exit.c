#include "minishell.h"

void	ft_exit(t_info *info, char **input)
{
	int i;

	i = 0;
	if (input[1] != NULL)
	{
		while (input[1][i])
		{
			if (ft_isdigit(input[1][i]) == 0)
			{
				printf("exit\n");
				exit(255);
			}
			i++;
		}
		printf("exit\n");
		exit(ft_atoi(input[1]));
	}
	printf("exit\n");
	exit(0);
}