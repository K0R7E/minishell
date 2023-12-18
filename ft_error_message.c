
#include "minishell.h"

void	ft_error_message(t_pars *pars, t_info *info)		
{
	ft_putstr_fd("minishell: malloc error\n", 1);
	ft_free_all(pars, info, 2);
	exit(1);
}