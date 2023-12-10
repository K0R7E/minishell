#include "minishell.h"

int is_builtin (t_pars **pars)
{
	t_pars *tmp;

	tmp = *pars;
	if (strncmp(tmp->command, "pwd", 3) == 0)
		return (1);
	else if (strncmp(tmp->command, "echo", 4) == 0)
		return (1);
	else if (strncmp(tmp->command, "cd", 2) == 0)
		return (1);
	else if (strncmp(tmp->command, "env", 3) == 0)
		return (1);
	else if (strncmp(tmp->command, "export", 6) == 0)
		return (1);
	else if (strncmp(tmp->command, "unset", 5) == 0)
		return (1);
	else if (strncmp(tmp->command, "exit", 4) == 0)
		return (1);
	else
		return (0);
}

void ft_test_bin(t_pars **pars, t_info *info)
{
	t_pars *tmp;
	pid_t pid;

	tmp = *pars;
	pid = fork();
	if (pid == 0)
	{
		if (execve(tmp->cmd_path, &tmp->command, info->env) == -1)
		{
			perror("Error");
			exit(0);
		}
	}
	else if (pid < 0)
	{
		perror("Error");
		exit(0);
	}
	else
		waitpid(pid, &info->exit_status, 0);

}

void ft_test_executor(t_pars **pars, t_info *info)
{
	t_pars *tmp;

	tmp = *pars;
	ft_print_pars(tmp);

	while(tmp != NULL)
	{
		if (tmp->command && strncmp(tmp->command, "exit", 4) == 0)
			exit(0);
		else if (info->command_count == 1)
		{
			if (is_builtin(&tmp) == 1)
			{
				printf("builtin\n");
				//ft_builtin(tmp, info);
			}
			else
			{
				printf("not builtin\n");
				ft_test_bin(&tmp, info);
			}
		}
		else
		{
			//ft_test_pipe(tmp, info);
			ft_test_bin(&tmp, info);
		}
		tmp = tmp->next;	
	}
}