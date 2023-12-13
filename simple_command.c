#include "minishell.h"

int	is_builtin(char *command)
{
	if (ft_strncmp(command, "echo", 4) == 0)
		return (1);
	if (ft_strncmp(command, "cd", 2) == 0)
		return (1);
	if (ft_strncmp(command, "pwd", 3) == 0)
		return (1);
	if (ft_strncmp(command, "export", 6) == 0)
		return (1);
	if (ft_strncmp(command, "unset", 5) == 0)
		return (1);
	if (ft_strncmp(command, "env", 3) == 0)
		return (1);
	if (ft_strncmp(command, "exit", 4) == 0)
		return (1);
	return (0);
}


void ft_command_execute(t_pars *node, int numsimplecommands, t_info *info)
{
	int tmpin=dup(0);
	int tmpout=dup(1);
	int ret;
	int fdout;
	int fdin;
	int i;

	if (node->in_file)
		fdin = node->fd_in;
	else 
		fdin = dup(tmpin);
	for(i = 0; i < numsimplecommands; i++)
	{
 		dup2(fdin, 0);
		close(fdin);
		if (i == numsimplecommands -1)
		{
			// Last simple command 
			if(node->out_file)
			{
				fdout = node->fd_out;
			}
			else 
			{
			// Use default output
			fdout = dup(tmpout);
			}
		}
		else 
		{
			int fdpipe[2];
			pipe(fdpipe);
			fdout=fdpipe[1];
			fdin=fdpipe[0];
		}
		dup2(fdout,1);
		close(fdout);

		// Create child process
		ret=fork();
		if (ret == -1)
		{
			perror("fork");
			exit(1);
		}
		if(ret==0) 
		{
			if (is_builtin(node->command) == 1)
				exit(1);
			else
				execve(node->cmd_path, node->cmd_args, env_conversion_back(info));
			exit(1);
		}
		else {
			// Parent process
			// Wait for child process to finish
			waitpid(ret, 0, 0);
			if (is_builtin(node->command) == 1)
				ft_builtin(node, info);
		}
	} //  for

	//restore in/out defaults
	dup2(tmpin,0);
	dup2(tmpout,1);
	close(tmpin);
	close(tmpout);
}

