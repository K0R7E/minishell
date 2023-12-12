#include "minishell.h"

void ft_executor_pars(t_pars *pars, t_info *info)
{
	//signal(SIGQUIT, sigquit_handler);
	//g_global.in_cmd = 1;
	(void)pars;
	if (info->command_count == 0)
	{
		//ft_single_command(pars, info);
	}
	else
	{
		info->pid = ft_calloc(sizeof(int), info->command_count + 1);
		if (!info->pid)
			return ; // with error
		//ft_executor(pars, info);
	}
	//g_global.in_cmd = 0;
}